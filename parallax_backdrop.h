#pragma once

#include <string>

#include "graphics.h"

class ParallaxBackdrop {
  public:
    ParallaxBackdrop(const std::string& file) : file(file) {}
    void draw(Graphics& graphics, float x_offset);

  private:
    std::string file;
};
