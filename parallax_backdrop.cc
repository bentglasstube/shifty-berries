#include "parallax_backdrop.h"

void ParallaxBackdrop::draw(Graphics& graphics, float x_offset) {
  SDL_Rect src = { (int) x_offset / 2, 0, graphics.get_width(), graphics.get_height() };
  graphics.blit(file, &src, NULL);
}
