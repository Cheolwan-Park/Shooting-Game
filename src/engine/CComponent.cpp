#include "CComponent.hpp"
#include "CObject.hpp"

// CController class
MAKE_COMPONENT_ID_CPP(CComponent);

// constructor
CComponent::CComponent()
:_elapseTime(0.0f), _owner(nullptr)
{
  ;
}

// copy constructor
CComponent::CComponent(const CComponent &other)
:_elapseTime(other._elapseTime), _owner(other._owner)
{
  ;
}

// destructor
CComponent::~CComponent()
{
  ;
}

// copy assignment operator
CComponent &CComponent::operator=(const CComponent &other)
{
  this->_elapseTime = other._elapseTime;
  this->_owner = other._owner;
  return (*this);
}

// update controller
void CComponent::update(float delta)
{
  _elapseTime += delta;
}

// called when owner object has collision
void CComponent::onColliderEnter(CObject *other)
{
  if(nullptr == other)
  {
    PRINT_ERROR(CComponent::onColliderEnter(), "param is nullptr");
    return;
  }
}
