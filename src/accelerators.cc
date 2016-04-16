#include "accelerators.h"

#include <algorithm>

float FrictionAccelerator::update_velocity(float velocity, unsigned int elapsed) {
  return velocity > 0.0f ?
    std::max(0.0f, velocity - friction * elapsed) :
    std::min(0.0f, velocity + friction * elapsed);
}

float ConstAccelerator::update_velocity(float velocity, unsigned int elapsed) {
  if (acceleration < 0.0f) {
    return std::max(velocity + acceleration * elapsed, max_velocity);
  } else {
    return std::min(velocity + acceleration * elapsed, max_velocity);
  }
}
