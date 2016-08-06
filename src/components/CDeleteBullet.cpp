#include "CDeleteBullet.hpp"

// CDeleteBullet class
MAKE_COMPONENT_ID_CPP(CDeleteBullet);

// constructor
CDeleteBullet::CDeleteBullet()
:CComponent::CComponent()
{
  ;
}

// copy constructor
CDeleteBullet::CDeleteBullet(const CDeleteBullet &other)
:CComponent::CComponent(other)
{
  ;
}

// destructor
CDeleteBullet::~CDeleteBullet()
{
  ;
}

// copy assignment operator
CDeleteBullet &CDeleteBullet::operator=(const CDeleteBullet &other)
{
  CComponent::operator=(other);
  return (*this);
}

// update CDeleteBullet component
void CDeleteBullet::update(float delta)
{
  CComponent::update(delta);
  if(!CRender::getViewPort().isOverlaped(getOwner()->getLocation()))
  {
    getOwner()->deleteObject();
  }
}
