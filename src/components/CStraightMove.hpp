//
// CStraightMove.hpp
//

#ifndef __CONTROLLERS_CSTRAIGHT_MOVE_HPP__
#define __CONTROLLERS_CSTRAIGHT_MOVE_HPP__

#include "../engine/engine.hpp"

class CStraightMove;
class CMoveInfo;

class CStraightMove
:public CComponent
{
public:
  // constructor
  explicit CStraightMove();

  // copy constructor
  CStraightMove(const CStraightMove &other);

  // destructor
  virtual ~CStraightMove();

  // copy assignment operator
  virtual CStraightMove &operator=(const CStraightMove &other);

  // funtion that moves bullet
  virtual void update(float delta);

  MAKE_COMPONENT_ID_HPP();

protected:
  CMoveInfo *_moveinfo;
};


class CMoveInfo
:public CComponent
{
public:
  // constructor
  explicit CMoveInfo(const CVector2 &direction, float speed);

  // copy constructor
  CMoveInfo(const CMoveInfo &other);

  // destructor
  ~CMoveInfo();

  // copy assignment operator
  CMoveInfo &operator=(const CMoveInfo &other);

  // get functions
  inline float getSpeed()const
  {
    return _speed;
  }

  inline const CVector2 &getDirection()const
  {
    return _direction;
  }

  // set functions
  inline void setSpeed(float speed)
  {
    _speed = speed;
  }

  inline void setDirection(const CVector2 &direction)
  {
    _direction = direction;
  }

  MAKE_COMPONENT_ID_HPP();

protected:
  float _speed;                   // speed info
  CVector2 _direction;            // direction info
};


#endif
