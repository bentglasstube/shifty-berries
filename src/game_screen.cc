#include "game_screen.h"
#include "human.h"

void GameScreen::init() {
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
