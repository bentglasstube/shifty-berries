#include "game_screen.h"

#include "bird.h"
#include "goat.h"
#include "human.h"

void GameScreen::init() {
  current_form = GameScreen::Animal::HUMAN;
  player.reset(new Human());
  player->set_position(32, 432);
  map.load("test");
}

bool GameScreen::update(Input& input, Audio&, Graphics&, unsigned int elapsed) {
  if (input.key_pressed(SDLK_ESCAPE)) return false;

  if (input.key_held(SDLK_a) && input.key_held(SDLK_d)) {
    player->stop_moving();
  } else if (input.key_held(SDLK_a)) {
    player->start_moving_left();
  } else if (input.key_held(SDLK_d)) {
    player->start_moving_right();
  } else {
    player->stop_moving();
  }

  if (input.key_pressed(SDLK_SPACE)) {
    player->start_jumping();
  }

  // TODO remove
  if (input.key_pressed(SDLK_g)) shapeshift(GameScreen::Animal::GOAT);
  if (input.key_pressed(SDLK_h)) shapeshift(GameScreen::Animal::HUMAN);
  if (input.key_pressed(SDLK_b)) shapeshift(GameScreen::Animal::BIRD);

  player->update(elapsed, map);
  camera.update(elapsed, *player, map);

  return true;
}

void GameScreen::draw(Graphics& graphics) {
  map.draw(graphics, camera.x_offset(), camera.y_offset());
  player->draw(graphics, camera.x_offset(), camera.y_offset());
}

Screen* GameScreen::next_screen() {
  return NULL;
}

void GameScreen::shapeshift(GameScreen::Animal animal) {
  if (current_form != animal) {
    current_form = animal;

    float x = player->x_position();
    float y = player->y_position();

    switch (animal) {
      case HUMAN: player.reset(new Human()); break;
      case GOAT:  player.reset(new Goat()); break;
      case BIRD:  player.reset(new Bird()); break;
    }

    player->set_position(x, y);
  }
}
