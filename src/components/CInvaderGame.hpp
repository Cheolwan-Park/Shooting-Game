//
// CInvaderGame.hpp
//

#ifndef __COMPONENTS_CINVADERGAME_HPP__
#define __COMPONENTS_CINVADERGAME_HPP__

#include "../engine/engine.hpp"

class CInvaderGame;
class CPlayer;
class CStage;
const float TIME_TO_RESTART=5.0f;
const float PRINT_REMAIN_TIME_INTERVAL=1.0f;

class CInvaderGame
:public CComponent
{
public:
  // constructor
  explicit CInvaderGame();

  // copy constructor
  CInvaderGame(const CInvaderGame &other);

  // destructor
  virtual ~CInvaderGame();

  // update CIvaderGame component
  virtual void update(float delta);

  // set owner
  virtual void setOwner(CObject *owner);

  // called when player die
  void playerDie();

  MAKE_COMPONENT_ID_HPP();

protected:
  bool _countStarted;                 // if count started, true
  bool _firstGenned;                  // if first gen is completed, true
  float _remainToRestart;             // remain time to restart
  float _nextPrintTime;               // next time printing time
  CStage *_stage;                     // pointer of stage
  CPlayer *_player;                   // pointer of player
};


#endif
