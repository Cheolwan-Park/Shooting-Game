#include "CStage.hpp"
#include "CEnermy.hpp"
#include "CStraightMove.hpp"
#include "CReciprocateMove.hpp"

#include <cstdlib>
#include <ctime>

// CStage class
MAKE_COMPONENT_ID_CPP(CStage);

// constructor
CStage::CStage()
:CComponent::CComponent(), _enermyCount(0), _level(0), _nextGenTime(0.0f)
{
  ;
}

// copy constructor
CStage::CStage(const CStage &other)
:CComponent::CComponent(), _enermyCount(other._enermyCount),
_level(other._level), _nextGenTime(other._nextGenTime)
{
  ;
}

// destructor
CStage::~CStage()
{
  ;
}

// copy assignment operator
CStage &CStage::operator=(const CStage &other)
{
  CComponent::operator=(other);
  this->_enermyCount = other._enermyCount;
  this->_level = other._level;
  this->_nextGenTime = other._nextGenTime;
  return (*this);
}

// update stage
void CStage::update(float delta)
{
  CComponent::update(delta);
  if(0 == _enermyCount)
  {
    if(0.0f == _nextGenTime)
    {
      _nextGenTime = _elapseTime + 2.0f;
    }
    else if(_nextGenTime <= _elapseTime)
    {
      nextLevel();

      char width = 0;
      char height = 0;
      float eachX = 0.0f;
      float eachY = 0.0f;
      float enermyNum = 0.0f;
      CObject *newObject = nullptr;
      CSprite *sprite = nullptr;
      CVector2 viewRange = CRender::getViewPort().getSize();
      viewRange *= 0.7;
      CVector2 base = getOwner()->getLocation() - (viewRange/2);
      base.y += 100.0f;

      width = STAGE_WIDTH;
      height = STAGE_HEIGHT;
      eachX = viewRange.x/width;
      eachY = viewRange.y/height;

      srand(clock());
      for(char y=0; y<height; ++y)
      {
        enermyNum = (rand()%7)*35.0f;
        for(char x=0; x<width; ++x)
        {
          newObject = new CObject(base + CVector2(eachX*x, eachY*y), ENERMY_FLIGHT);
          sprite = new CSprite(CSize2(50.0f, 50.0f), "Resources/enermies.png");
          sprite->setDrawRange(CRect(enermyNum, 0.0f, enermyNum + 35.0f, 27.0f));
          newObject->addComponent(sprite);
          newObject->addComponent(new CMoveInfo(CVector2(1.0f, 0.0f), 10.0f));
          newObject->addComponent(new CReciprocateMove(0, 1.0f));
          newObject->addComponent(new CCollider(25.0f));
          newObject->addComponent(new CEnermy(this));
          getOwner()->addChild(newObject);
          newObject = nullptr;
          sprite = nullptr;
        }
      }
      _nextGenTime = 0.0f;
      _enermyCount = width*height;
    }
  }
}
