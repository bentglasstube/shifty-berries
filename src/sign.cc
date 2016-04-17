#include "sign.h"

Sign::Sign(int x, int y, std::string message) : x(x), y(y), message(message) {
  text.reset(new Text("text"));
}

void Sign::draw(Graphics& graphics) {
  if (visible) {
    // TODO draw a cool text box
    text->draw(graphics, message, graphics.get_width() / 2, 128, Text::CENTER);
  }
}

bool Sign::collision(Rect box) {
  if (box.left > x * 16) return false;
  if (box.right < x * 16 - 16) return false;
  if (box.top > y * 16) return false;
  if (box.bottom < y * 16 - 16) return false;

  return true;
}
