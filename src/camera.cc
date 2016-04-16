#include "camera.h"

#include <algorithm>

Camera::Camera() : ox(0), oy(0) {}

namespace {
  const int kWidth = 640;
  const int kHeight = 480;
  const float kMaxSpeed = 0.5f;
}

float _window(float min, float max, float focus, float size) {
  float target = focus - size / 2;

  if (target < min) return min;
  if (target > max - size) return max - size;

  return target;
}

void Camera::update(unsigned int elapsed, Player player, Map map) {
  float tx = _window(0, map.pixel_width(), player.x_position(), kWidth);
  if (ox > tx) ox = std::max(ox - kMaxSpeed * elapsed, tx);
  if (ox < tx) ox = std::min(ox + kMaxSpeed * elapsed, tx);

  // TODO only move camera vertically when on ground
  float ty = _window(0, map.pixel_height(), player.y_position(), kHeight);
  if (oy > ty) oy = std::max(oy - kMaxSpeed * elapsed, ty);
  if (oy < ty) oy = std::min(oy + kMaxSpeed * elapsed, ty);
}
