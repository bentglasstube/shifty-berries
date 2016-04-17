#pragma once

#include "audio.h"
#include "map.h"
#include "rect.h"
#include "sprite.h"

class Player {
  public:

    enum Facing { LEFT, RIGHT };

    Player();

    void update(unsigned int elapsed, Map& map, Audio& audio);
    void draw(Graphics& graphics, int x_offset, int y_offset);

    virtual void move_left();
    virtual void move_right();
    virtual void stop_moving();

    void jump(Audio& audio);
    virtual bool  can_jump() { return on_ground(); }
    virtual void push_crate(Map&, Map::Tile) {};

    void set_position(float x, float y, Facing f = Facing::RIGHT);

    float x_position() { return pos_x; }
    float y_position() { return pos_y; }

    Facing get_facing() { return facing; }

    Rect bounding_box();

  protected:

    virtual Sprite* get_sprite() = 0;

    bool on_ground() const;

    void update_x(unsigned int elapsed, Map& map);
    void update_y(unsigned int elapsed, Map& map, Audio& audio);

    Rect box_col_h();
    Rect box_col_v();

    int width, height;
    float jump_speed, max_speed;
    float ground_accel, air_accel;
    std::string jump_sample;

    int accel_x;
    float velo_x, velo_y, pos_x, pos_y;
    bool jumping;
    Facing facing;
};
