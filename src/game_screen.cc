#include "game_screen.h"

#include "bird.h"
#include "finish_screen.h"
#include "goat.h"
#include "human.h"

void GameScreen::init() {
  current_form = GameScreen::Animal::HUMAN;
  player.reset(new Human());
  text.reset(new Text("text"));
  load_level("level1");

  shapeshift_timer = run_timer = death_count = 0;
  finished = false;
}

bool GameScreen::update(Input& input, Audio& audio, Graphics&, unsigned int elapsed) {
  if (input.key_pressed(SDL_SCANCODE_ESCAPE)) return false;

  if (input.key_held(SDL_SCANCODE_A) && input.key_held(SDL_SCANCODE_D)) {
    player->stop_moving();
  } else if (input.key_held(SDL_SCANCODE_A)) {
    player->move_left();
  } else if (input.key_held(SDL_SCANCODE_D)) {
    player->move_right();
  } else {
    player->stop_moving();
  }

  if (input.key_pressed(SDL_SCANCODE_SPACE)) player->jump(audio);

  // TODO put this somewhere sane
  if (input.key_pressed(SDL_SCANCODE_J)) {
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
  /* if (input.key_pressed(SDL_SCANCODE_G)) shapeshift(GameScreen::Animal::GOAT, 0); */
  /* if (input.key_pressed(SDL_SCANCODE_H)) shapeshift(GameScreen::Animal::HUMAN, 0); */
  /* if (input.key_pressed(SDL_SCANCODE_B)) shapeshift(GameScreen::Animal::BIRD, 0); */
  /* if (input.key_pressed(SDL_SCANCODE_N)) player->set_position(10000, 0); */

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
    death_count++;
  }

  if (player->x_position() > map.pixel_width() + 8) {
    shapeshift(GameScreen::Animal::HUMAN, 0);
    audio.play_sample("next");
    if (map.next_level() == "DONE") {
      finished = true;
      return false;
    } else {
      load_level(map.next_level());
    }
    // hack to reset the camera instantly
    camera.update(10000, *player, map);
  }

  run_timer += elapsed;

  return true;
}

void GameScreen::draw(Graphics& graphics) {
  backdrop->draw(graphics, camera.x_offset());
  map.draw(graphics, camera.x_offset(), camera.y_offset());
  player->draw(graphics, camera.x_offset(), camera.y_offset());

  if (shapeshift_timer > 0) {
    char buffer[8];
    sprintf(buffer, "%2d", (shapeshift_timer + 999) / 1000);
    text->draw(graphics, buffer, graphics.get_width() / 2, graphics.get_height() - 32, Text::Alignment::CENTER);
  }

  {
    char buffer[50];
    snprintf(buffer, 50, "%d", death_count);
    text->draw(graphics, buffer, 8, 8);

    snprintf(buffer, 50, "%d:%02d.%03d", run_timer / 60000, (run_timer / 1000) % 60, run_timer % 1000);
    text->draw(graphics, buffer, graphics.get_width() - 8, 8, Text::Alignment::RIGHT);
  }
}

Screen* GameScreen::next_screen() {
  if (finished) {
    FinishScreen* finish = new FinishScreen();
    finish->set_results(run_timer, death_count);
    return finish;
  } else {
    return NULL;
  }
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
