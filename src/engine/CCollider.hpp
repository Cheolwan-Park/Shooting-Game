//
// CCollider.hpp
//

#ifndef __ENGINE_CCOLLIDER_HPP__
#define __ENGINE_CCOLLIDER_HPP__

#include "CVector2.hpp"
#include "CObject.hpp"
#include "CComponent.hpp"
#include <unordered_map>

class CCollider;
typedef std::unordered_map<CCollider*, CCollider*> collider_hash;


class CCollider
:public CComponent
{
public:
  // default constructor
  explicit CCollider(float radius,
    const CVector2 &relativeLocation = CVector2(0.0f, 0.0f));

  // copy constructor
  CCollider(const CCollider &other);

  // destructor
  virtual ~CCollider();

  // copy assignment operator
  virtual CCollider &operator=(const CCollider &other);

  // check there is collision between this collider and other collider
  virtual bool isCollideWith(const CCollider &other)const;

  // set functions
  inline void setRadius(float radius)
  {
    _radius = radius;
  }

  // relative position is position that relative of owner's position
  inline void setRelativeLocation(const CVector2 &relativeLocation)
  {
    _relativeLocation = relativeLocation;
  }

  // get functions
  inline float getRadius()const
  {
    return _radius;
  }

  inline const CVector2 getLocation()const
  {
    return _owner->getLocation() + _relativeLocation;
  }

  MAKE_COMPONENT_ID_HPP();

protected:
  float _radius;                  // radius of collider (collider's shape is circle)
  CVector2 _relativeLocation;     // relative location of collider
};


class CCollisionChecker
{
public:
  static CCollisionChecker global;

  // constructor
  explicit CCollisionChecker();

  // destructor
  virtual ~CCollisionChecker();

  // update CCollidsionChecker object, check collision,
  // if there is collision, call onColliderEnter() function in _onwenr object
  void update();

  // add collider to _colliderVector, make collider to be updated by CCollisionChecker object
  void addCollider(CCollider *collider);

  // remove collider from _colliderVector, make collider not to be updated by CCollisionChecker object
  // called when collider is removed
  void removeCollider(CCollider *collider);

protected:
  collider_hash _colliderHash;

};


#endif
