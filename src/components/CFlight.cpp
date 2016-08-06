#include "CFlight.hpp"

// CFlight class
MAKE_COMPONENT_ID_CPP(CFlight);

// constructor
CFlight::CFlight(int life)
:CComponent::CComponent(), _life(life)
{
  ;
}

// copy constructor
CFlight::CFlight(const CFlight &other)
:CComponent::CComponent(other), _life(other._life), _velocity(other._velocity)
{
  ;
}

// destructor
CFlight::~CFlight()
{
  ;
}

// copy assignment operator
CFlight &CFlight::operator=(const CFlight &other)
{
  CComponent::operator=(other);
  this->_life = other._life;
  this->_velocity = other._velocity;
  return (*this);
}

// update flight sprite
void CFlight::update(float delta)
{
  CComponent::update(delta);
  _velocity.x = 0.0f;
  _velocity.y = 0.0f;
  setVelocity(delta);
  _owner->move(_velocity);
  genBullets();
}
