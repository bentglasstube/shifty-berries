#pragma once

#include "animated_sprite.h"
#include "player.h"

class Human : public Player {
  public:
    Human();

  private:
    int get_width()  { return 16; }
    int get_height() { return 32; }

    float get_jump_speed()   { return 0.35f; }
    float get_ground_accel() { return 0.0005f; }
    float get_air_accel()    { return 0.0003f; }
    float get_max_speed()    { return 0.15f; }

    Sprite* get_sprite();

    AnimatedSprite walking;
    Sprite standing, crouching;
};
