#pragma once

#include <memory>

#include "audio.h"
#include "camera.h"
#include "map.h"
#include "parallax_backdrop.h"
#include "player.h"
#include "screen.h"
#include "text.h"

class GameScreen : public Screen {
  public:

    void init();
    bool update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics);

    Screen* next_screen();
    std::string get_music_track() { return ""; }

  private:
    enum Animal { HUMAN, GOAT, BIRD };

    void shapeshift(Animal animal, int duration);

    std::unique_ptr<Player> player;
    std::unique_ptr<ParallaxBackdrop> backdrop;
    std::unique_ptr<Text> text;
    Animal current_form;
    Map map;
    Camera camera;
    int shapeshift_timer;
};
