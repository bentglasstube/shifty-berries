#include "human.h"

Human::Human() : Player(),
  walking("sprites", 0, 0, 16, 32, 4, 14),
  standing("sprites", 0, 0, 16, 32),
  crouching("sprites", 64, 0, 16, 32)
{
  width = 16;
  height = 32;

  jump_speed = 0.35f;
  ground_accel = 0.0005f;
  air_accel = 0.0003f;
  max_speed = 0.15f;

  jump_sample = "human-jump";
}

Sprite* Human::get_sprite() {
  if ((jumping && velo_y < 0)) return &crouching;
  else if (!on_ground()) return &standing;
  else if (velo_x != 0) return &walking;
  else return &standing;
}
