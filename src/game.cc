#include "game.h"

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#include "title_screen.h"

namespace {
  const unsigned int FPS = 60;
  const unsigned int MSPF = 1000 / FPS;
}

Game::Game() {
  srand(static_cast<unsigned int>(time(NULL)));
  SDL_Init(SDL_INIT_EVERYTHING);
}

Game::~Game() {
  SDL_Quit();
}

void Game::start() {
  graphics.reset(new Graphics(640, 480));

  last_update = SDL_GetTicks();

  screen.reset(new TitleScreen());
  screen->init();
}

bool Game::step() {
  const unsigned int start = SDL_GetTicks();

  if (!audio.music_playing()) audio.play_music(screen->get_music_track());
  if (!screen->process_input(input)) return false;

  const unsigned int update = SDL_GetTicks();
  const unsigned int frame_ticks = update - last_update;
  if (screen->update(input, audio, static_cast<Graphics&>(*graphics), frame_ticks)) {

    graphics->clear();
    screen->draw(static_cast<Graphics&>(*graphics));
    graphics->flip();

  } else {

    screen.reset(screen->next_screen());
    if (!screen) return false;
    screen->init();

    audio.stop_music();
  }

  last_update = update;

  const unsigned int elapsed = SDL_GetTicks() - start;
  if (MSPF > elapsed) SDL_Delay(MSPF - elapsed);

  return true;
}

void Game::loop() {
  start();
  while (step()) {}
}
