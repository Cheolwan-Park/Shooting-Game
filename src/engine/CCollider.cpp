#include "CCollider.hpp"
#include <algorithm>

CCollisionChecker CCollisionChecker::global;


// CCollider class
MAKE_COMPONENT_ID_CPP(CCollider);

// default constructor
CCollider::CCollider(float radius,
            const CVector2 &relativePosition)
:CComponent::CComponent(), _radius(radius), _relativeLocation(relativePosition)
{
  CCollisionChecker::global.addCollider(this);
}

// copy constructor
CCollider::CCollider(const CCollider &other)
:CComponent::CComponent(other), _radius(other._radius),
_relativeLocation(other._relativeLocation)
{
  CCollisionChecker::global.addCollider(this);
}

// destructor
CCollider::~CCollider()
{
  CCollisionChecker::global.removeCollider(this);
}

// copy assignment operator
CCollider &CCollider::operator=(const CCollider &other)
{
  CComponent::operator=(other);
  this->_radius = other._radius;
  this->_relativeLocation = other._relativeLocation;
  return (*this);
}

// check collision
bool CCollider::isCollideWith(const CCollider &other)const
{
  float distance = CVector2::length(other.getLocation() - this->getLocation());
  if((other.getRadius() + this->getRadius()) > distance)
  {
    return true;
  }
  else
  {
    return false;
  }
}


// CCollisionChecker class

// constructor
CCollisionChecker::CCollisionChecker()
{
  ;
}

// destructor
CCollisionChecker::~CCollisionChecker()
{
  _colliderHash.clear();
}

// update CCollisionChecker class
void CCollisionChecker::update()
{
  for(auto iter0 = _colliderHash.begin();
      iter0 != _colliderHash.end();
      ++iter0)
  {
    for(auto iter1 = std::next(iter0);
        iter1 != _colliderHash.end();
        ++iter1)
    {
      if(iter0->second->isCollideWith(*(iter1->second)))
      {
        iter0->second->getOwner()->onColliderEnter(iter1->second->getOwner());
        iter1->second->getOwner()->onColliderEnter(iter0->second->getOwner());
      }
    }
  }
}

// add collider to _colliderVector
void CCollisionChecker::addCollider(CCollider *collider)
{
  if(nullptr == collider)
  {
    PRINT_ERROR(CCollisionChecker::addCollider(), "param is nullptr");
    return;
  }

  auto find = _colliderHash.find(collider);
  if(_colliderHash.end() != find)
  {
    PRINT_ERROR(CColliderChecker::addCollider(),
    "CCollider Cheker already has same collider in collider hash");
    return;
  }

  _colliderHash.insert(collider_hash::value_type(collider, collider));
}

// remove collider from _colliderVector
void CCollisionChecker::removeCollider(CCollider *collider)
{
  if(nullptr == collider)
  {
    PRINT_ERROR(CCollisionChecker::removeCollider(), "param is nullptr");
    return;
  }

  _colliderHash.erase(collider);
}
