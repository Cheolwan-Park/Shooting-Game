//
// CDeleteBullet.hpp
//

#ifndef __COMPONETNS_CDELETEBULLET_HPP__
#define __COMPONETNS_CDELETEBULLET_HPP__

#include "../engine/engine.hpp"

class CDeleteBullet;

class CDeleteBullet
:public CComponent
{
public:
  // constructor
  explicit CDeleteBullet();

  // copy constructor
  CDeleteBullet(const CDeleteBullet &other);

  // destructor
  ~CDeleteBullet();

  // copy assignment operator
  CDeleteBullet &operator=(const CDeleteBullet &other);

  virtual void update(float delta);

  MAKE_COMPONENT_ID_HPP();
  
};



#endif
