#pragma once

#include "audio.h"
#include "map.h"
#include "rect.h"
#include "sprite.h"

class Player {
  public:

    enum Facing { LEFT, RIGHT };

    Player();

    void update(unsigned int elapsed, Map map, Audio& audio);
    void draw(Graphics& graphics, int x_offset, int y_offset);

    virtual void start_moving_left();
    virtual void start_moving_right();
    virtual void stop_moving();

    virtual void start_jumping(Audio& audio) = 0;
    virtual void stop_jumping();

    void set_position(float x, float y, Facing f = Facing::RIGHT);

    float x_position() { return pos_x; }
    float y_position() { return pos_y; }

    Facing get_facing() { return facing; }

    Rect bounding_box();

  protected:

    virtual Sprite* get_sprite() = 0;

    virtual int get_width() = 0;
    virtual int get_height() = 0;

    virtual float get_jump_speed() = 0;
    virtual float get_ground_accel() = 0;
    virtual float get_air_accel() = 0;
    virtual float get_max_speed() = 0;

    bool on_ground() const;

    void update_x(unsigned int elapsed, Map map);
    void update_y(unsigned int elapsed, Map map, Audio& audio);

    Rect box_col_h();
    Rect box_col_v();

    int accel_x;
    float velo_x, velo_y, pos_x, pos_y;
    bool jump;
    Facing facing;
};
