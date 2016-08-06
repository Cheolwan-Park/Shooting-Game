//
// CStage.hpp
//

#ifndef __COMPONENTS_CSTAGE_HPP__
#define __COMPONENTS_CSTAGE_HPP__

#include "../engine/engine.hpp"

class CStage;
const char MAX_LEVEL = 10;
const char STAGE_WIDTH = 10;
const char STAGE_HEIGHT = 4;

class CStage
:public CComponent
{
public:
  // constructor
  explicit CStage();

  // copy constructor
  CStage(const CStage &other);

  // destructor
  ~CStage();

  // copy assignment operator
  CStage &operator=(const CStage &other);

  // update stage
  virtual void update(float delta);

  // get functions
  char getEnermyCount()const
  {
    return _enermyCount;
  }

  char getLevel()const
  {
    return _level;
  }

  // set functions
  void decreaseEnermy()
  {
    --_enermyCount;
  }

  void nextLevel()
  {
    if(_level < MAX_LEVEL)
    {
      ++_level;
    }
  }

  MAKE_COMPONENT_ID_HPP();

protected:
  char _enermyCount;          // count of enermy
  char _level;                // level
  float _nextGenTime;         // next gen time
};


#endif
