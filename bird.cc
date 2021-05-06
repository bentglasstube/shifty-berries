#include "bird.h"

Bird::Bird() : Player(),
  flying("sprites", 0, 64, 16, 16, 4, 14),
  landed("sprites", 64, 64, 16, 16)
{
  width = 16;
  height = 16;

  jump_speed = 0.40f;
  ground_accel = 0.00f;
  air_accel = 0.0005f;
  max_speed = 0.20f;

  jump_sample = "bird-jump";
}

Sprite* Bird::get_sprite() {
  if (on_ground()) return &landed;
  return &flying;
}

void Bird::move_left() {
  if (!on_ground()) {
    accel_x = -1;
    facing = LEFT;
  }
}

void Bird::move_right() {
  if (!on_ground()) {
    accel_x = 1;
    facing = RIGHT;
  }
}
