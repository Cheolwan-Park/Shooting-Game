//
// CBulletInfo.hpp
//

#ifndef __COMPONENTS_CBULLETINFO_HPP__
#define __COMPONENTS_CBULLETINFO_HPP__

#include "../engine/engine.hpp"

class CBulletInfo;

class CBulletInfo
:public CComponent
{
public:
  // constructor
  explicit CBulletInfo(int damage);

  // copy constructor
  CBulletInfo(const CBulletInfo &other);

  // destructor
  ~CBulletInfo();

  // copy assignment operator
  CBulletInfo &operator=(const CBulletInfo &other);

  // get functions
  int getDamage()const
  {
    return _damage;
  }

  // set functions
  void setDamage(int damage)
  {
    _damage = damage;
  }

  MAKE_COMPONENT_ID_HPP();

protected:
  int _damage;                  // damage of bullet
};


#endif
