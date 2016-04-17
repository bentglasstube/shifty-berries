#pragma once

#include <memory>

#include "audio.h"
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
    enum Animal { HUMAN, GOAT, BIRD };

    void shapeshift(Audio& audio, Animal animal);

    std::unique_ptr<Player> player;
    Animal current_form;
    Map map;
    Camera camera;
};
