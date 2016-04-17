#include "backdrop.h"

void Backdrop::draw(Graphics& graphics) {
  graphics.blit(file, NULL, NULL);
}
