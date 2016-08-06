#include "CStraightMove.hpp"

// CStraightBullet class
MAKE_COMPONENT_ID_CPP(CStraightMove);

// constructor
CStraightMove::CStraightMove()
:CComponent::CComponent(), _moveinfo(nullptr)
{
  ;
}

// copy constructor
CStraightMove::CStraightMove(const CStraightMove &other)
:CComponent::CComponent(other), _moveinfo(other._moveinfo)
{
  ;
}

// destructor
CStraightMove::~CStraightMove()
{
  ;
}

// copy assignment operator
CStraightMove &CStraightMove::operator=(const CStraightMove &other)
{
  CComponent::operator=(other);
  _moveinfo = other._moveinfo;
  return (*this);
}

// controll bullet
void CStraightMove::update(float delta)
{
  if(nullptr == _moveinfo)
  {
    _moveinfo = _owner->getComponent<CMoveInfo>();
  }
  CComponent::update(delta);
  _owner->move(_moveinfo->getDirection()*(_moveinfo->getSpeed()*delta));
}


// CMoveInfo class
MAKE_COMPONENT_ID_CPP(CMoveInfo);

// constructor
CMoveInfo::CMoveInfo(const CVector2 &direction, float speed)
:CComponent::CComponent(),  _speed(speed), _direction(direction)
{
  ;
}

// copy constructor
CMoveInfo::CMoveInfo(const CMoveInfo &other)
:CComponent::CComponent(other), _speed(other._speed), _direction(other._direction)
{
  ;
}

// destructor
CMoveInfo::~CMoveInfo()
{
  ;
}

// copy assignment operator
CMoveInfo &CMoveInfo::operator=(const CMoveInfo &other)
{
  CComponent::operator=(other);
  this->_speed = other._speed;
  this->_direction = other._direction;
  return (*this);
}
