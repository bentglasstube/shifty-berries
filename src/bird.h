#pragma once

#include "animated_sprite.h"
#include "player.h"

class Bird : public Player {
  public:
    Bird();

    void start_moving_left();
    void start_moving_right();
    void stop_moving();

    void start_jumping(Audio& audio);
    void stop_jumping();

  private:
    int get_width()  { return 16; }
    int get_height() { return 16; }

    float get_jump_speed()   { return 0.40f; }
    float get_ground_accel() { return 0.00f; }
    float get_air_accel()    { return 0.0005f; }
    float get_max_speed()    { return 0.20f; }

    Sprite* get_sprite();

    AnimatedSprite flying;
    Sprite landed;
};
