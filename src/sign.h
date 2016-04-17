#pragma once

#include <memory>
#include <string>

#include "rect.h"
#include "text.h"

class Sign {
  public:
    Sign(int x, int y, std::string message);
    void draw(Graphics& graphics);
    bool collision(Rect box);
    void set_visibility(bool v) { visible = v; }

  private:
    int x, y;
    bool visible;
    std::string message;
    std::unique_ptr<Text> text;
};
