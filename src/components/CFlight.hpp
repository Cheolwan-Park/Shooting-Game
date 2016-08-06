//
// CFlight.hpp
//

#ifndef __OBJECTS_CFLIGHT_HPP__
#define __OBJECTS_CFLIGHT_HPP__

#include "../engine/engine.hpp"

class CFlight;


class CFlight
:public CComponent
{
public:
  // constructor
  explicit CFlight(int life);

  // copy constructor
  CFlight(const CFlight &other);

  // destructor
  virtual ~CFlight();

  // copy assignment operator
  virtual CFlight &operator= (const CFlight &other);

  // update flight sprite
  virtual void update(float delta);

  // gen bullets
  virtual void genBullets() = 0;

  // set velocity
  virtual void setVelocity(float delta) = 0;

  // get functions
  int getLife()const
  {
    return _life;
  }

  MAKE_COMPONENT_ID_HPP();

protected:
  int _life;                  // life of player
  CVector2 _velocity;         // velocity of flight
};

#endif
