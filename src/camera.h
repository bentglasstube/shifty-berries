#pragma once

#include "map.h"
#include "player.h"

class Camera {
  public:
    Camera();

    void update(unsigned int elapsed, Player player, Map& map);
    void reset(float x, float y) { ox = x; oy = y; }

    float x_offset() { return ox; }
    float y_offset() { return oy; }

  private:
    float ox, oy;
};
