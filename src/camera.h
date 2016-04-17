#pragma once

#include "map.h"
#include "player.h"

class Camera {
  public:
    Camera();

    void update(unsigned int elapsed, Player player, Map& map);

    float x_offset() { return ox; }
    float y_offset() { return oy; }

  private:
    float ox, oy;
};
