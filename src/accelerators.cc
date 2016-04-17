#include "accelerators.h"

#include <algorithm>

const ZeroAccelerator ZeroAccelerator::kZero;
const ConstAccelerator ConstAccelerator::kGravity(0.0012f, 0.5f);

float FrictionAccelerator::update_velocity(float velocity, unsigned int elapsed) const {
  return velocity > 0.0f ?
    std::max(0.0f, velocity - friction * elapsed) :
    std::min(0.0f, velocity + friction * elapsed);
}

float ConstAccelerator::update_velocity(float velocity, unsigned int elapsed) const {
  if (acceleration < 0.0f) {
    return std::max(velocity + acceleration * elapsed, max_velocity);
  } else {
    return std::min(velocity + acceleration * elapsed, max_velocity);
  }
}
