#pragma once

#include "map.h"
#include "rect.h"
#include "sprite.h"

class Player {
  public:

    Player();

    void update(unsigned int elapsed, Map map);
    void draw(Graphics& graphics, int x_offset, int y_offset);

    void start_moving_left();
    void start_moving_right();
    void stop_moving();

    void start_jumping();
    void stop_jumping();

    void set_position(float x, float y);

    float x_position();
    float y_position();

  protected:

    enum Facing { LEFT, RIGHT };

    virtual Sprite* get_sprite() = 0;

    virtual int get_width() = 0;
    virtual int get_height() = 0;

    virtual float get_jump_speed() = 0;
    virtual float get_ground_accel() = 0;
    virtual float get_air_accel() = 0;
    virtual float get_max_speed() = 0;

    bool on_ground() const;

    void update_x(unsigned int elapsed, Map map);
    void update_y(unsigned int elapsed, Map map);

    Rect box_col_h();
    Rect box_col_v();

    int accel_x;
    float velo_x, velo_y, pos_x, pos_y;
    bool jump;
    Facing facing;
};
