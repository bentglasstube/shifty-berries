#include "goat.h"

Goat::Goat() : Player(),
  pushing(false),
  walking("sprites", 0, 32, 16, 16, 4, 14),
  ramming("sprites", 0, 48, 16, 16, 4, 14),
  standing("sprites", 16, 32, 16, 16)
{
  jump_speed = 0.25f;
  ground_accel = 0.0004f;
  air_accel = 0.0002f;
  max_speed = 0.18f;

  jump_sample = "goat-jump";
}

void Goat::push_crate(Map& map, Map::Tile tile) {
  // only push on the ground when moving slowly
  if (on_ground() && velo_x < 0.1 && velo_x > -0.1) map.push_tile(tile, velo_x);
}

Sprite* Goat::get_sprite() {
  if (jumping || !on_ground()) return &standing;
  else if (pushing) return &ramming;
  else if (velo_x != 0) return &walking;
  else return &standing;
}
