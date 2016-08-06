//
// CMath.hpp
//

#ifndef __ENGINE_CMATH_HPP__
#define __ENGINE_CMATH_HPP__

#include <cmath>


class CMath
{
public:
  static inline float sin(float angle)
  {
    return sinf(angle);
  }

  static inline float cos(float angle)
  {
    return cosf(angle);
  }

  static inline float tan(float angle)
  {
    return tanf(angle);
  }

  static inline float asin(float angle)
  {
    return asinf(angle);
  }

  static inline float acos(float angle)
  {
    return acosf(angle);
  }

  static inline float atan(float angle)
  {
    return atanf(angle);
  }

  static inline float abs(float value)
  {
    return (value >= 0 ? value : (-1*value));
  }

  static inline int abs(int value)
  {
    return (value >= 0 ? value : (-1*value));
  }

  static inline float deg2rad(float angle)
  {
    return (3.141592f/180*angle);
  }

  static inline float rad2deg(float angle)
  {
    return (180/3.141592f*angle);
  }

  // linear interpolation, return x + s(y - x)
  static inline float lerp(float x, float y, float s)
  {
    return (x+s*(y-x));
  }

  static inline float pow(float n, float exponent)
  {
    return powf(n, exponent);
  }

  static inline float square(float value)
  {
    return (value*value);
  }

  static inline float sqrt(float value)
  {
    return sqrtf(value);
  }

};


#endif
