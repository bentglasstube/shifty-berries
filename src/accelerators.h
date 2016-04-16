#pragma once

class Accelerator {
  public:
    virtual ~Accelerator() = 0;
    virtual float update_velocity(float velocity, unsigned int elapsed) = 0;
};

inline Accelerator::~Accelerator() {}

class ZeroAccelerator : Accelerator {
  public:
    ZeroAccelerator() {}
    float update_velocity(float velocity, unsigned int) { return velocity; }
};

class FrictionAccelerator : Accelerator {
  public:
    FrictionAccelerator(float friction) : friction(friction) {}
    float update_velocity(float velocity, unsigned int elapsed);

  private:
    float friction;
};

class ConstAccelerator : Accelerator {
  public:
    ConstAccelerator(float acceleration, float max_velocity) : acceleration(acceleration), max_velocity(max_velocity) {}
    float update_velocity(float velocity, unsigned int elapsed);

  private:
    float acceleration, max_velocity;
};
