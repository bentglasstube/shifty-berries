#include "map.h"

#include <stdio.h>

Map::Map() : tileset("map", 6, 16, 16) {}

void Map::load(std::string file) {
  const std::string path("content/" + file + ".txt");
  FILE* fd = fopen(path.c_str(), "r");
  char line[1024];

  height = 0;

  fprintf(stderr, "Loading map: %s\n", file.c_str());
  while (fgets(line, sizeof(line), fd)) {
    width = strlen(line) - 1;
    strncpy(tiles[height], line, width);
    height++;
  }

  fprintf(stderr, "Read map as %d x %d\n", width, height);

  fclose(fd);
}

void Map::draw(Graphics& graphics, int x_offset, int y_offset) {
  for (int y = 0; y < height; ++y) {
    int gy = 16 * y - y_offset;
    if (gy < -16) continue;
    if (gy > 480) break;

    for (int x = 0; x < width; ++x) {
      int gx = 16 * x - x_offset;
      if (gx < -16) continue;
      if (gx > 640) break;

      char t = tiles[y][x];
      if (t >= 'A' && t <= 'Z') {
        tileset.draw(graphics, t - 'A', gx, gy);
      } else if (t >= 'a' && t <= 'z') {
        tileset.draw(graphics, t - 'a' + 26, gx, gy);
      }
    }
  }
}

bool Map::tile_at(float x, float y) {
  return tiles[(int)y / 16][(int)x / 16] != '.';
}

bool Map::collision(Rect box, float dx, float dy) {
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

  return false;
}

bool Map::check_tile_range(int x1, int x2, int y1, int y2) {
  for (int y = y1; y <= y2; ++y) {
    for (int x = x1; x <= x2; ++x) {
      if (tiles[y][x] != '.') return true;
    }
  }
  return false;
}
