#include "bird.h"

Bird::Bird() : Player(),
  flying("sprites", 0, 64, 16, 16, 4, 14),
  landed("sprites", 64, 64, 16, 16) {}

Sprite* Bird::get_sprite() {
  if (on_ground()) return &landed;
  return &flying;
}

void Bird::start_moving_left() {
  if (!on_ground()) {
    accel_x = -1;
    facing = LEFT;
  }
}

void Bird::start_moving_right() {
  if (!on_ground()) {
    accel_x = 1;
    facing = RIGHT;
  }
}

void Bird::stop_moving() {
  accel_x = 0;
}

void Bird::start_jumping(Audio& audio) {
  if (velo_y >= 0.0f) {
    velo_y = -get_jump_speed();
    audio.play_sample("bird-jump");
  }
}

void Bird::stop_jumping() {
  accel_x = 0;
}
