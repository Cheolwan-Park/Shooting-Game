#include "CVector2.hpp"

// constructor
CVector2::CVector2(float initx, float inity)
:x(initx), y(inity)
{
  ;
}

// copy constructor
CVector2::CVector2(const CVector2 &other)
:x(other.x), y(other.y)
{
  ;
}

// destructor
CVector2::~CVector2()
{
  ;
}


// CRect class

// constructors
CRect::CRect(float lbx, float lby, float rtx, float rty)
:_left_bottom(lbx, lby), _right_top(rtx, rty)
{
  ;
}

CRect::CRect(const CVector2 &left_bottom, const CVector2 &right_top)
:_left_bottom(left_bottom), _right_top(right_top)
{
  ;
}

// copy constructor
CRect::CRect(const CRect &other)
:_left_bottom(other._left_bottom), _right_top(other._right_top)
{
  ;
}

// destructor
CRect::~CRect()
{
  ;
}

// copy assignment operator
CRect &CRect::operator=(const CRect &other)
{
  this->_left_bottom = other._left_bottom;
  this->_right_top = other._right_top;
  return (*this);
}

// compare operator
bool CRect::operator==(const CRect &other)
{
  if((this->_left_bottom != other._left_bottom)
  ||(this->_right_top != other._right_top))
  {
    return false;
  }
  else
  {
    return true;
  }
}

bool CRect::operator!=(const CRect &other)
{
  if((this->_left_bottom != other._left_bottom)
  ||(this->_right_top != other._right_top))
  {
    return true;
  }
  else
  {
    return false;
  }
}

// check overlap
bool CRect::isOverlaped(const CVector2 &v)const
{
  if((_left_bottom.x > v.x)
  ||(_right_top.x < v.x)
  ||(_left_bottom.y > v.y)
  ||(_right_top.y < v.y))
  {
    return false;
  }
  else
  {
    return true;
  }
}

bool CRect::isOverlaped(const CRect &rect)const
{
  if((_left_bottom.x > rect._right_top.x)
  ||(_right_top.x < rect._left_bottom.x)
  ||(_left_bottom.y > rect._right_top.y)
  ||(_right_top.y < rect._left_bottom.y))
  {
    return false;
  }
  else
  {
    return true;
  }
}

// get size of rect
const CSize2 CRect::getSize()const
{
  return (_right_top-_left_bottom);
}
