#pragma once

#include "graphics.h"
#include "rect.h"
#include "sprite.h"

class Map {
  public:
    Map();

    void load(std::string file);
    void draw(Graphics& graphics);

    bool tile_at(float x, float y);

    bool collision(Rect box, float dx, float dy);

  private:
    Sprite brick;
    int height, width;
    char tiles[128][1024];
};
