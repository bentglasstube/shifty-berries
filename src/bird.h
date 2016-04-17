#pragma once

#include "animated_sprite.h"
#include "player.h"

class Bird : public Player {
  public:
    Bird();

    void move_left();
    void move_right();

    bool can_jump() { return true; }

  private:
    Sprite* get_sprite();

    AnimatedSprite flying;
    Sprite landed;
};
