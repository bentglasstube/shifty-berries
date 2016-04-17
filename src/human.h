#pragma once

#include "animated_sprite.h"
#include "player.h"

class Human : public Player {
  public:
    Human();

  private:
    Sprite* get_sprite();

    AnimatedSprite walking;
    Sprite standing, crouching;
};
