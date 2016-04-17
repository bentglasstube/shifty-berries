#pragma once

class Accelerator {
  public:
    virtual ~Accelerator() = 0;
    virtual float update_velocity(float velocity, unsigned int elapsed) const = 0;
};

inline Accelerator::~Accelerator() {}

class ZeroAccelerator : Accelerator {
  public:
    static const ZeroAccelerator kZero;

    ZeroAccelerator() {}
    float update_velocity(float velocity, unsigned int) const { return velocity; }
};

class FrictionAccelerator : Accelerator {
  public:
    FrictionAccelerator(float friction) : friction(friction) {}
    float update_velocity(float velocity, unsigned int elapsed) const;

  private:
    float friction;
};

class ConstAccelerator : Accelerator {
  public:
    static const ConstAccelerator kGravity;

    ConstAccelerator(float acceleration, float max_velocity) : acceleration(acceleration), max_velocity(max_velocity) {}
    float update_velocity(float velocity, unsigned int elapsed) const;

  private:
    float acceleration, max_velocity;
};
