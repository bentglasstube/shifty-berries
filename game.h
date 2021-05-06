#pragma once

#include <memory>

#include "audio.h"
#include "graphics.h"
#include "input.h"
#include "screen.h"

class Game {
  public:

    Game();
    ~Game();

    void start();
    bool step();
    void loop();

  private:

    std::unique_ptr<Screen> screen;
    std::unique_ptr<Graphics> graphics;
    Audio audio;
    Input input;

    unsigned int last_update;
};
