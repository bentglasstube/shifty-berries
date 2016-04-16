#include "spritemap.h"

SpriteMap::SpriteMap(const std::string& file, int cols, int width, int height) :
  file(file), cols(cols), width(width), height(height) {}

void SpriteMap::draw(Graphics& graphics, int n, int x, int y) {
  SDL_Rect source = { 0, 0, width, height };
  SDL_Rect dest = { x, y, width, height };

  source.x = width * (n % cols);
  source.y = height * (n / cols);

  graphics.blit(file, &source, &dest);
}
