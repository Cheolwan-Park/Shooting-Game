//
// CReciporateMove.hpp
//

#ifndef __CONTROLLERS_CRECIPROCATE_MOVE_HPP__
#define __CONTROLLERS_CRECIPROCATE_MOVE_HPP__

#include "../engine/engine.hpp"
#include "CStraightMove.hpp"

class CReciprocateMove;

class CReciprocateMove
:public CStraightMove
{
public:
  // constructor
  explicit CReciprocateMove(char repeat, float period);

  // copy constructor
  CReciprocateMove(const CReciprocateMove &other);

  // destructor
  virtual ~CReciprocateMove();

  // copy assignment operator
  virtual CReciprocateMove &operator=(const CReciprocateMove &other);

  // function that moves bullet
  virtual void update(float delta);

  // get functions
  float getPeriod()const
  {
    return _period;
  }

  char getRepeat()const
  {
    return _repeat;
  }

  char getNowRepeat()const
  {
    return _nowRepeat;
  }

  // set functions
  void setPeriod(float period)
  {
    _period = period;
  }

  void setRepeat(char repeat)
  {
    _repeat = repeat;
  }

  MAKE_COMPONENT_ID_HPP();

protected:
  char _repeat;             // repeat time, if _repeat equals 0 repeat forever
  char _nowRepeat;          // now repeat time
  float _period;            // period of recipocation
};



#endif
