#include "map.h"

#include <stdio.h>
// #include <string.h>

Map::Map() : brick("map", 0, 16, 16, 16) {}

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

      switch (tiles[y][x]) {
        case 'X':
          brick.draw(graphics, gx, gy);
          break;
      }
    }
  }
}

bool Map::tile_at(float x, float y) {
  return tiles[(int)y / 16][(int)x / 16] == 'X';
}

bool Map::collision(Rect box, float dx, float dy) {
  if (dx > 0) return tile_at(box.right + dx, box.top    + dy) || tile_at(box.right + dx, box.bottom + dy);
  if (dx < 0) return tile_at(box.left  + dx, box.top    + dy) || tile_at(box.left  + dx, box.bottom + dy);
  if (dy > 0) return tile_at(box.left  + dx, box.bottom + dy) || tile_at(box.right + dx, box.bottom + dy);
  if (dy < 0) return tile_at(box.left  + dx, box.top    + dy) || tile_at(box.right + dx, box.top + dy);

  return false;
}
