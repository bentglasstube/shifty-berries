#pragma once

#include <memory>
#include <vector>

#include "graphics.h"
#include "rect.h"
#include "sign.h"
#include "spritemap.h"
#include "text.h"

class Map {
  public:

    struct Tile {
      char c;
      bool obstruction;
      float friction;
      float top, left, right, bottom;
    };

    Map();

    void load(std::string file);
    void draw(Graphics& graphics, int x_offset, int y_offset);
    void update(Rect player);

    void push_tile(Map::Tile tile, float dx);

    Tile tile_at(float x, float y);
    Tile collision(Rect box, float dx, float dy);

    int pixel_width() { return width * 16; }
    int pixel_height() { return height * 16; }

    int player_x() { return start_x * 16 - 8; }
    int player_y() { return start_y * 16 + 16; }

    std::string current_level() { return name; }
    std::string next_level() { return next; }
    std::string background() { return bg; }

  private:
    typedef std::vector<std::shared_ptr<Sign>> SignSet;

    SpriteMap tileset;
    Text text;
    int height, width;
    int start_x, start_y;
    char tiles[128][1024];
    std::string name, next, bg;

    Tile tile(int x, int y);
    Tile check_tile_range(int x1, int x2, int y1, int y2);
    SignSet signs;
};
