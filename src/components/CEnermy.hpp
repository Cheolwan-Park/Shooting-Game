//
// CEnermy.hpp
//

#ifndef __COMPONENTS_CENERMY_HPP__
#define __COMPONENTS_CENERMY_HPP__

#include "../engine/engine.hpp"
#include "CFlight.hpp"

class CEnermy;
class CStage;
const int ENERMY_FLIGHT = -1;
const int ENERMY_BULLET = -2;
const int PLAYER_BULLET = 2;

const float ENERMY_BULLET_GEN_INTERVAL = 0.5f;  // if this constant is big, game becomes easy
const char ENERMY_CIRCLEBULLET_GEN__RATIO = 1;  // if this constant is big, game becomes hard
const char ENERMY_LIFE_RATIO = 1;               // if this constant is big, game becomes hard

class CEnermy
:public CFlight
{
public:
  // constructor
  explicit CEnermy(CStage *stage);

  // copy constructor
  CEnermy(const CEnermy &other);

  // destructor
  ~CEnermy();

  // copy assignment operator
  CEnermy &operator=(const CEnermy &other);

  // gen bullets
  virtual void genBullets();

  // set velocity
  virtual void setVelocity(float delta);

  // on collision
  virtual void onColliderEnter(CObject *other);

  // get functions
  char getCirclePercentage()const
  {
    return _circlePercentage;
  }

  float getBulletGenInterval()const
  {
    return _bulletGenInterval;
  }

  // set functions
  void setCirclePercentage(char circlePercentage)
  {
    _circlePercentage = circlePercentage;
  }

  void setBulletGenInterval(float bulletGenInterval)
  {
    _bulletGenInterval = bulletGenInterval;
  }

  MAKE_COMPONENT_ID_HPP();

protected:
  char _circlePercentage;             // percentage of genning circle bullet (0 ~ 100)
  float _bulletGenInterval;           // interval of genning bullets time
  float _nextBulletGen;               // next bullet gen time
  CStage *_stage;                     // pointer of stage
  CVector2 _moveDirection;            // move direction
};


#endif
