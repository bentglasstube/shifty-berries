#pragma once

#include "animated_sprite.h"
#include "player.h"

class Goat : public Player {
  public:
    Goat();

  private:
    int get_width()  { return 16; }
    int get_height() { return 16; }

    float get_jump_speed()   { return 0.25f; }
    float get_ground_accel() { return 0.0004f; }
    float get_air_accel()    { return 0.0002f; }
    float get_max_speed()    { return 0.18f; }

    Sprite* get_sprite();

    bool pushing;
    AnimatedSprite walking, ramming;
    Sprite standing;
};
