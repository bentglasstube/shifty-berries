#pragma once

#include <string>

#include "graphics.h"

class Backdrop {
  public:
    Backdrop(const std::string& file) : file(file) {}
    void draw(Graphics& graphics);

  private:
    std::string file;
};
