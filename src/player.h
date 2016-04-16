#pragma once

#include "map.h"
#include "rect.h"
#include "sprite.h"
#include "animated_sprite.h"

class Player {
  public:

    Player();

    void update(unsigned int elapsed, Map map);
    void draw(Graphics& graphics);

    void start_moving_left();
    void start_moving_right();
    void stop_moving();

    void start_jumping();
    void stop_jumping();

    void set_position(float x, float y);

  private:

    enum Facing { LEFT, RIGHT };

    bool on_ground() const;

    void update_x(unsigned int elapsed, Map map);
    void update_y(unsigned int elapsed, Map map);

    Rect box_col_h();
    Rect box_col_v();

    int accel_x;
    float velo_x, velo_y, pos_x, pos_y;
    bool jump;
    Facing facing;

    AnimatedSprite sprite;
};
