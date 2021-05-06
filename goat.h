#pragma once

#include "animated_sprite.h"
#include "player.h"

class Goat : public Player {
  public:
    Goat();

    void push_crate(Map& map, Map::Tile tile);

  private:
    Sprite* get_sprite();

    bool pushing;
    AnimatedSprite walking, ramming;
    Sprite standing;
};
