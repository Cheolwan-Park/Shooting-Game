#include "CReciprocateMove.hpp"

// CReciprocateBullet class
MAKE_COMPONENT_ID_CPP(CReciprocateMove);

// constructor
CReciprocateMove::CReciprocateMove(char repeat, float period)
:CStraightMove::CStraightMove(), _repeat(repeat),
_nowRepeat(0), _period(period)
{
  ;
}

// copy constructor
CReciprocateMove::CReciprocateMove(const CReciprocateMove &other)
:CStraightMove::CStraightMove(other), _repeat(other._repeat),
_nowRepeat(other._nowRepeat), _period(other._period)
{
  ;
}

// destructor
CReciprocateMove::~CReciprocateMove()
{
  ;
}

// copy assignment operator
CReciprocateMove &CReciprocateMove::operator=(const CReciprocateMove &other)
{
  CStraightMove::operator=(other);
  this->_repeat = other._repeat;
  this->_nowRepeat = other._nowRepeat;
  this->_period = other._period;
  return (*this);
}

// function that moves bullet
void CReciprocateMove::update(float delta)
{
  CStraightMove::update(delta);
  if(_elapseTime > _period)
  {
    _elapseTime = 0.0f;
    ++_nowRepeat;
    if((_repeat==0)||
      (_repeat >= _nowRepeat))
    {
      _moveinfo->setDirection(_moveinfo->getDirection()*-1);
    }
  }
}
