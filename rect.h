#pragma once

class Rect {
  public:
    Rect(float x1, float y1, float x2, float y2) : top(y1), left(x1), right(x2), bottom(y2) {}
    float top, left, right, bottom;
};
