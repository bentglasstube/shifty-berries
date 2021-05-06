#include "finish_screen.h"

#include "game_screen.h"

void FinishScreen::init() {
  backdrop.reset(new Backdrop("finish"));
  text.reset(new Text("text"));
  retry = true;
}

bool FinishScreen::update(Input& input, Audio&, Graphics&, unsigned int) {
  if (input.key_pressed(SDL_SCANCODE_ESCAPE)) {
    retry = false;
    return false;
  }

  if (input.key_pressed(SDL_SCANCODE_SPACE)) {
    retry = true;
    return false;
  }

  return true;
}

void FinishScreen::draw(Graphics& graphics) {
  backdrop->draw(graphics);

  {
    char buffer[30];
    snprintf(buffer, 30, "%d:%02d.%03d", time / 60000, (time / 1000) % 60, time % 1000);
    text->draw(graphics, buffer, graphics.get_width() / 2, 196, Text::CENTER);

    snprintf(buffer, 30, "%d deaths", deaths);
    text->draw(graphics, buffer, graphics.get_width() / 2, 212, Text::CENTER);
  }
}

Screen* FinishScreen::next_screen() {
  return retry ? new GameScreen() : NULL;
}

void FinishScreen::set_results(int _time, int _deaths) {
  time = _time;
  deaths = _deaths;
}
