//
// CPlayer.hpp
//

#ifndef __COMPONENTS_CPLAYER_HPP__
#define __COMPONENTS_CPLAYER_HPP__

#include "../engine/engine.hpp"
#include "CFlight.hpp"

class CPlayer;
class CInvaderGame;
const unsigned int LIFE=5;

class CPlayer : public CFlight
{
public:
  // constructor
  explicit CPlayer(CInvaderGame *invaderGame);

  // copy constructor
  CPlayer(const CPlayer &other);

  // destructor
  ~CPlayer();

  // copy assignment operator
  CPlayer &operator=(const CPlayer &other);

  // get bullets
  virtual void genBullets();

  // update CPlayer component
  virtual void update(float delta);

  // set velocity
  virtual void setVelocity(float delta);

  // called when collision
  virtual void onColliderEnter(CObject *other);

  MAKE_COMPONENT_ID_HPP();
protected:
  float _nextGen;
  CInvaderGame *_invaderGame;
  CVector2 _lastLocation;
};


#endif
