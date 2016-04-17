#include "player.h"

#include "accelerators.h"

Player::Player() :
  width(16), height(16),
  jump_speed(0), max_speed(0),
  ground_accel(0), air_accel(0),
  jump_sample(""),
  accel_x(0), velo_x(0), velo_y(0), pos_x(0), pos_y(0),
  jumping(false), facing(RIGHT) {}

void Player::update(unsigned int elapsed, Map& map, Audio& audio) {
  if (elapsed > 50) elapsed = 50;
  update_x(elapsed, map);
  update_y(elapsed, map, audio);
}

void Player::draw(Graphics& graphics, int x_offset, int y_offset) {
  // Display collision boxes for debugging
  /* Rect bch = box_col_h(); */
  /* graphics.rect( */
  /*     (int)(bch.left - x_offset), */
  /*     (int)(bch.top - y_offset), */
  /*     (int)(bch.right - bch.left), */
  /*     (int)(bch.bottom - bch.top), */
  /*     255, 0, 0); */

  /* Rect bcv = box_col_v(); */
  /* graphics.rect( */
  /*     (int)(bcv.left - x_offset), */
  /*     (int)(bcv.top - y_offset), */
  /*     (int)(bcv.right - bcv.left), */
  /*     (int)(bcv.bottom - bcv.top), */
  /*     0, 0, 255); */

  Graphics::FlipDirection dir = facing == LEFT ? Graphics::FlipDirection::HORIZONTAL : Graphics::FlipDirection::NONE;
  get_sprite()->draw(graphics, pos_x - width / 2 - x_offset, pos_y - height - y_offset, dir);
}

void Player::move_left() {
  accel_x = -1;
  if (on_ground()) facing = LEFT;
}

void Player::move_right() {
  accel_x = 1;
  if (on_ground()) facing = RIGHT;
}

void Player::stop_moving() {
  accel_x = 0;
}

void Player::jump(Audio& audio) {
  if (can_jump()) {
    jumping = true;
    velo_y = -jump_speed;
    audio.play_sample(jump_sample);
  }
}

void Player::set_position(float x, float y, Player::Facing f) {
  pos_x = x;
  pos_y = y;
  facing = f;
}

Rect Player::bounding_box() {
  return Rect(pos_x - width / 2, pos_y - height, pos_x + width / 2, pos_y);
}

bool Player::on_ground() const {
  return velo_y == 0;
}

void Player::update_x(unsigned int elapsed, Map& map) {
  velo_x += accel_x * (on_ground() ? ground_accel : air_accel) * elapsed;

  if (on_ground()) {
    float friction = map.tile_at(pos_x, pos_y + 1).friction;
    velo_x = FrictionAccelerator(friction).update_velocity(velo_x, elapsed);
    if (accel_x != 0) velo_x = ConstAccelerator(accel_x * ground_accel, accel_x * max_speed).update_velocity(velo_x, elapsed);
  } else {
    if (accel_x != 0) velo_x = ConstAccelerator(accel_x * air_accel, accel_x * max_speed).update_velocity(velo_x, elapsed);
  }

  Map::Tile t = map.collision(box_col_h(), velo_x * elapsed, 0);
  if (t.obstruction) {
    if (t.c == 'Z') push_crate(map, t);
    if (velo_x > 0) pos_x = t.left - width / 2;
    else pos_x = t.right + width / 2;
    velo_x = 0;
  } else {
    pos_x += velo_x * elapsed;
  }

  if (pos_x < 0) {
    pos_x = 0;
    if (velo_x < 0) velo_x = 0;
  }
}

void Player::update_y(unsigned int elapsed, Map& map, Audio& audio) {
  velo_y = ConstAccelerator::kGravity.update_velocity(velo_y, elapsed);

  Map::Tile t = map.collision(box_col_v(), 0, velo_y * elapsed);
  if (t.obstruction) {
    if (velo_y > 0){
      pos_y = t.top;
      jumping = false;
      if (velo_y > 0.1) audio.play_sample("bump");
    } else {
      pos_y = t.bottom + height;
    }
    velo_y = 0;
  } else {
    pos_y += velo_y * elapsed;
  }
}

Rect Player::box_col_h() {
  return Rect(
      pos_x - width / 2,
      pos_y - height + 4,
      pos_x + width / 2,
      pos_y - 4);
}

Rect Player::box_col_v() {
  return Rect(
      pos_x - width / 2 + 2,
      pos_y - height,
      pos_x + width / 2 - 2,
      pos_y);
}
