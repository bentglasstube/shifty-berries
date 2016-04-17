#include "game_screen.h"

#include "bird.h"
#include "goat.h"
#include "human.h"

void GameScreen::init() {
  current_form = GameScreen::Animal::HUMAN;
  player.reset(new Human());
  text.reset(new Text("text"));
  player->set_position(32, 432);
  map.load("test");
  backdrop.reset(new ParallaxBackdrop("outside-day"));
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
  if (input.key_pressed(SDLK_RSHIFT)) {
    if (current_form == GameScreen::Animal::HUMAN) {
      Map::Tile tile = map.tile_at(player->x_position(), player->y_position() - 4);

      fprintf(stderr, "Interacting with %c\n", tile.c);

      if (tile.c == 'g') {
        shapeshift(GameScreen::Animal::GOAT, 15);
        audio.play_sample("shift");
      } else if (tile.c == 'h') {
        shapeshift(GameScreen::Animal::BIRD, 10);
        audio.play_sample("shift");
      }
    }
  }

  // TODO remove
  if (input.key_pressed(SDLK_g)) shapeshift(GameScreen::Animal::GOAT, 0);
  if (input.key_pressed(SDLK_h)) shapeshift(GameScreen::Animal::HUMAN, 0);
  if (input.key_pressed(SDLK_b)) shapeshift(GameScreen::Animal::BIRD, 0);

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

  return true;
}

void GameScreen::draw(Graphics& graphics) {
  backdrop->draw(graphics, camera.x_offset());
  map.draw(graphics, camera.x_offset(), camera.y_offset());
  player->draw(graphics, camera.x_offset(), camera.y_offset());

  if (shapeshift_timer > 0) {
    char buffer[3];
    snprintf(buffer, 3, "%2d", (shapeshift_timer + 999) / 1000);
    text->draw(graphics, buffer, graphics.get_width() - 16, 16, Text::Alignment::RIGHT);
  }
}

Screen* GameScreen::next_screen() {
  return NULL;
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
