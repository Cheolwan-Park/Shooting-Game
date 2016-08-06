#include "CBulletInfo.hpp"

// CBulletInfo class
MAKE_COMPONENT_ID_CPP(CBulletInfo);

// constructor
CBulletInfo::CBulletInfo(int damage)
:CComponent::CComponent(), _damage(damage)
{
  ;
}

// copy constructor
CBulletInfo::CBulletInfo(const CBulletInfo &other)
:CComponent::CComponent(other), _damage(other._damage)
{
  ;
}

// destructor
CBulletInfo::~CBulletInfo()
{
  ;
}

// copy assignment operator
CBulletInfo &CBulletInfo::operator=(const CBulletInfo &other)
{
  CComponent::operator=(other);
  this->_damage = other._damage;
  return (*this);
}
