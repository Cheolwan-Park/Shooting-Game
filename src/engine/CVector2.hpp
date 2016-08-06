//
// CVector2.hpp
//

#ifndef __ENGINE_CVECTOR2_HPP__
#define __ENGINE_CVECTOR2_HPP__

#include "CMath.hpp"

class CVector2;
typedef CVector2 CSize2;


class CVector2
{
public:
  // constructor
  explicit CVector2(float initx = 0.0f, float inity = 0.0f);

  // copy constructor
  CVector2(const CVector2 &other);

  // destructor
  virtual ~CVector2();

  // operator overrides
  const CVector2 &operator=(const CVector2 &other)
  {
    this->x = other.x;
    this->y = other.y;
    return (*this);
  }

  const inline CVector2 operator+(const CVector2 &other)const
  {
    return CVector2(this->x+other.x, this->y+other.y);
  }

  const inline CVector2 operator-(const CVector2 &other)const
  {
    return CVector2(this->x-other.x, this->y-other.y);
  }

  // vector * scalar, dot product is declared as static function
  const inline CVector2 operator*(float scalar)const
  {
    return CVector2(this->x*scalar, this->y*scalar);
  }

  const inline CVector2 operator/(float scalar)const
  {
    return CVector2(this->x/scalar, this->y/scalar);;
  }

  const inline CVector2 &operator+=(const CVector2 &other)
  {
    this->x += other.x;
    this->y += other.y;
    return (*this);
  }

  const inline CVector2 &operator-=(const CVector2 &other)
  {
    this->x -= other.x;
    this->y -= other.y;
    return (*this);
  }

  const inline CVector2 &operator*=(float scalar)
  {
    this->x *= scalar;
    this->y *= scalar;
    return (*this);
  }

  const inline CVector2 &operator/=(float scalar)
  {
    this->x /= scalar;
    this->y /= scalar;
    return (*this);
  }

  bool operator==(const CVector2 &other)
  {
    if((this->x == other.x)
      &&(this->y == other.y))
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  bool operator !=(const CVector2 &other)
  {
    if((this->x != other.x)
      ||(this->y != other.y))
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  // static functions
  static inline float dot(const CVector2 &v1, const CVector2 &v2)
  {
    return (v1.x*v2.x+v1.y*v2.y);
  }

  static inline float length(const CVector2 &v)
  {
    return (CMath::sqrt(CMath::square(v.x)+CMath::square(v.y)));
  }

  static float angle(const CVector2 &v1, const CVector2 &v2)
  {
    float result = CMath::acos(CVector2::dot(v1, v2)/(CVector2::length(v1)*CVector2::length(v2)));
    result = result < (3.141592f-result) ? result : (3.141592-result);
    return result;
  }

  static inline const CVector2 &normalize(CVector2 &v)
  {
    v /= CVector2::length(v);
    return v;
  }

  static inline const CVector2 normalize(const CVector2 &v)
  {
    return v/CVector2::length(v);
  }

  // this funtion rotates vector anticlockwise
  // parameter angle must be radian value
  static inline CVector2 rotate(const CVector2 &v, float angle)
  {
    return CVector2(v.x*CMath::cos(angle)-v.y*CMath::sin(angle),
    v.y*CMath::cos(angle)+v.x*CMath::sin(angle));
  }

  float x;
  float y;
};


class CRect
{
public:
  // constructors
  CRect(float lbx, float lby, float rtx, float rty);

  CRect(const CVector2 &left_bottom, const CVector2 &right_top);

  // copy constructor
  CRect(const CRect &other);

  // destructor
  ~CRect();

  // copy assignment operator
  CRect &operator=(const CRect &other);

  // compare operator
  bool operator==(const CRect &other);
  bool operator!=(const CRect &other);

  // check overlap
  bool isOverlaped(const CVector2 &v)const;

  bool isOverlaped(const CRect &rect)const;

  // get size of rect (width and height)
  const CSize2 getSize()const;

  // fields
  CVector2 _left_bottom;
  CVector2 _right_top;
};


#endif
