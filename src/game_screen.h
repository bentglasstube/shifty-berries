#pragma once

#include "camera.h"
#include "map.h"
#include "player.h"
#include "screen.h"

class GameScreen : public Screen {
  public:

    void init();
    bool update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics);

    Screen* next_screen();
    std::string get_music_track() { return ""; }

  private:
    Player player;
    Map map;
    Camera camera;
};
