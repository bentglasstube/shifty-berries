#include "map.h"

#include <stdio.h>

namespace {
  const Map::Tile kNullTile {};
}

Map::Map() : tileset("map", 6, 16, 16), text("text") {}

void Map::load(std::string file) {
  const std::string path("content/" + file + ".txt");
  FILE* fd = fopen(path.c_str(), "r");

  name = file;

  fprintf(stderr, "Loading level %s\n", file.c_str());

  {
    char a[32], b[32];
    fscanf(fd, "%d %d %d %32s %32s\n", &start_x, &start_y, &height, a, b);
    next = a;
    bg = b;
  }

  for (int y = 0; y < height; ++y) fgets(tiles[y], sizeof(tiles[y]), fd);
  width = strlen(tiles[0]) - 1;

  signs.clear();
  {
    int x, y;
    char t[100];
    while (fscanf(fd, "%d %d %100[^\n]\n", &x, &y, t) != EOF) {
      signs.push_back(std::shared_ptr<Sign>(new Sign(x, y, t)));
    }
  }

  fclose(fd);
}

void Map::draw(Graphics& graphics, int x_offset, int y_offset) {
  for (int y = 0; y < height; ++y) {
    int gy = 16 * y - y_offset;
    if (gy < -16) continue;
    if (gy > graphics.get_height()) break;

    for (int x = 0; x < width; ++x) {
      int gx = 16 * x - x_offset;
      if (gx < -16) continue;
      if (gx > graphics.get_width()) break;

      char t = tiles[y][x];
      if (t >= 'A' && t <= 'Z') {
        tileset.draw(graphics, t - 'A', gx, gy);
      } else if (t >= 'a' && t <= 'z') {
        tileset.draw(graphics, t - 'a' + 26, gx, gy);
      }

      // Draw map data for debugging
      /* char buffer[2]; */
      /* snprintf(buffer, 2, "%c", t); */
      /* text.draw(graphics, buffer, gx, gy); */
    }
  }

  for (SignSet::iterator i = signs.begin(); i != signs.end(); ++i) {
    std::shared_ptr<Sign> sign = *i;
    sign->draw(graphics);
  }
}

void Map::update(Rect player) {
  for (SignSet::iterator i = signs.begin(); i != signs.end(); ++i) {
    std::shared_ptr<Sign> sign = *i;
    sign->set_visibility(sign->collision(player));
  }
}

void Map::push_tile(Map::Tile tile, float dx) {
  int tx = (int) (tile.left + tile.right) / 32;
  int ty = (int) (tile.top + tile.bottom) / 32;

  int nx = dx < 0 ? tx - 1 : tx + 1;

  if (tiles[ty][nx] == '.') {
    tiles[ty][nx] = tiles[ty][tx];
    tiles[ty][tx] = '.';
  }
}

Map::Tile Map::tile_at(float x, float y) {
  return tile((int)x / 16, (int)y / 16);
}

Map::Tile Map::collision(Rect box, float dx, float dy) {
  if (dx != 0) {
    int x = (int) ((dx < 0 ? box.left : box.right) + dx) / 16;
    int top = (int) box.top / 16;
    int bottom = (int) box.bottom / 16;
    return check_tile_range(x, x, top, bottom);
  }

  if (dy != 0) {
    int y = (int) ((dy < 0 ? box.top : box.bottom) + dy) / 16;
    int left = (int) box.left / 16;
    int right = (int) box.right / 16;
    return check_tile_range(left, right, y, y);
  }

  return kNullTile;
}

Map::Tile Map::tile(int x, int y) {
  char t = tiles[y][x];

  Tile tile;
  tile.c = t;

  if (t >= 'A' && t <= 'Z') {
    tile.obstruction = true;
    tile.friction = 0.0005f;
    if (t >= 'S' && t <= 'X') tile.friction = 0.0001f;
  } else {
    tile.obstruction = false;
  }

  tile.top = y * 16;
  tile.bottom = tile.top + 16;

  tile.left = x * 16;
  tile.right = tile.left + 16;

  return tile;
}

Map::Tile Map::check_tile_range(int x1, int x2, int y1, int y2) {
  for (int y = y1; y <= y2; ++y) {
    for (int x = x1; x <= x2; ++x) {
      Tile t = tile(x, y);
      if (t.obstruction) return t;
    }
  }

  return kNullTile;
}
