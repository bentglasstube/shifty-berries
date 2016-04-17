#include "human.h"

Human::Human() : Player(),
  walking("sprites", 0, 0, 16, 32, 4, 14),
  standing("sprites", 0, 0, 16, 32),
  crouching("sprites", 64, 0, 16, 32) {}

void Human::start_jumping(Audio& audio) {
  if (on_ground()) {
    jump = true;
    velo_y = -get_jump_speed();
    audio.play_sample("human-jump");
  }
}

Sprite* Human::get_sprite() {
  if ((jump && velo_y < 0)) return &crouching;
  else if (!on_ground()) return &standing;
  else if (velo_x != 0) return &walking;
  else return &standing;
}
