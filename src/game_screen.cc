#include "game_screen.h"

#include "bird.h"
#include "goat.h"
#include "human.h"

void GameScreen::init() {
  current_form = GameScreen::Animal::HUMAN;
  player.reset(new Human());
  text.reset(new Text("text"));
  load_level("level1");
}

bool GameScreen::update(Input& input, Audio& audio, Graphics&, unsigned int elapsed) {
  if (input.key_pressed(SDLK_ESCAPE)) return false;

  if (input.key_held(SDLK_a) && input.key_held(SDLK_d)) {
    player->stop_moving();
  } else if (input.key_held(SDLK_a)) {
    player->move_left();
  } else if (input.key_held(SDLK_d)) {
    player->move_right();
  } else {
    player->stop_moving();
  }

  if (input.key_pressed(SDLK_SPACE)) player->jump(audio);

  // TODO put this somewhere sane
  if (input.key_pressed(SDLK_j)) {
    if (current_form == GameScreen::Animal::HUMAN) {
      Map::Tile tile = map.tile_at(player->x_position(), player->y_position() - 4);

      fprintf(stderr, "Interacting with %c\n", tile.c);

      if (tile.c == 'g') {
        shapeshift(GameScreen::Animal::GOAT, 15);
        audio.play_sample("shift");
      } else if (tile.c == 'h') {
        shapeshift(GameScreen::Animal::BIRD, 5);
        audio.play_sample("shift");
      }
    }
  }

  /* cheating keys */
  /* if (input.key_pressed(SDLK_g)) shapeshift(GameScreen::Animal::GOAT, 0); */
  /* if (input.key_pressed(SDLK_h)) shapeshift(GameScreen::Animal::HUMAN, 0); */
  /* if (input.key_pressed(SDLK_b)) shapeshift(GameScreen::Animal::BIRD, 0); */
  /* if (input.key_pressed(SDLK_n)) player->set_position(10000, 0); */

  player->update(elapsed, map, audio);
  camera.update(elapsed, *player, map);

  map.update(player->bounding_box());

  if (shapeshift_timer > 0) {
    shapeshift_timer -= elapsed;
    if (shapeshift_timer <= 0) {
      audio.play_sample("unshift");
      shapeshift(GameScreen::Animal::HUMAN, 0);
    }
  }

  if (player->y_position() > map.pixel_height() + 50) {
    shapeshift(GameScreen::Animal::HUMAN, 0);
    audio.play_sample("death");
    load_level(map.current_level());
  }

  if (player->x_position() > map.pixel_width() + 8) {
    shapeshift(GameScreen::Animal::HUMAN, 0);
    audio.play_sample("next");
    load_level(map.next_level());
    // hack to reset the camera instantly
    camera.update(10000, *player, map);
  }

  return true;
}

void GameScreen::draw(Graphics& graphics) {
  backdrop->draw(graphics, camera.x_offset());
  map.draw(graphics, camera.x_offset(), camera.y_offset());
  player->draw(graphics, camera.x_offset(), camera.y_offset());

  if (shapeshift_timer > 0) {
    char buffer[3];
    snprintf(buffer, 3, "%2d", (shapeshift_timer + 999) / 1000);
    text->draw(graphics, buffer, graphics.get_width() / 2, graphics.get_height() - 32, Text::Alignment::CENTER);
  }
}

Screen* GameScreen::next_screen() {
  return NULL;
}

void GameScreen::load_level(std::string level) {
  map.load(level);
  player->set_position(map.player_x(), map.player_y());
  backdrop.reset(new ParallaxBackdrop(map.background()));
}

void GameScreen::shapeshift(GameScreen::Animal animal, int duration) {
  if (current_form != animal) {
    shapeshift_timer = 1000 * duration;

    current_form = animal;

    float x = player->x_position();
    float y = player->y_position();
    Player::Facing facing = player->get_facing();

    switch (animal) {
      case HUMAN: player.reset(new Human()); break;
      case GOAT:  player.reset(new Goat()); break;
      case BIRD:  player.reset(new Bird()); break;
    }

    player->set_position(x, y, facing);
  }
}
