#pragma once

#include "graphics.h"

class SpriteMap {
  public:
    SpriteMap(const std::string& file, int cols, int width, int height);
    void draw(Graphics& graphics, int n, int x, int y);

  private:
    std::string file;
    int cols, width, height;
};
