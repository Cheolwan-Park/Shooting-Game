#include "CEnermy.hpp"
#include "CStage.hpp"
#include "CCircleGenerator.hpp"
#include "CBulletInfo.hpp"
#include "CStraightMove.hpp"
#include "CDeleteBullet.hpp"

#include <cstdlib>
#include <ctime>

// CEnermy class
MAKE_COMPONENT_ID_CPP(CEnermy);

// constructor
CEnermy::CEnermy(CStage *stage)
:CFlight::CFlight(stage->getLevel()*ENERMY_LIFE_RATIO),
_circlePercentage(stage->getLevel()*ENERMY_CIRCLEBULLET_GEN__RATIO),
_bulletGenInterval((MAX_LEVEL - stage->getLevel() + 1)*ENERMY_BULLET_GEN_INTERVAL),
_nextBulletGen(_bulletGenInterval),
_stage(stage), _moveDirection(1.0f, 0.0f)
{
  if(nullptr == stage)
  {
    PRINT_ERROR(CEnermy::constuctor(), "param is nullptr");
  }
}

// copy constructor
CEnermy::CEnermy(const CEnermy &other)
:CFlight::CFlight(other), _circlePercentage(other._circlePercentage),
_bulletGenInterval(other._bulletGenInterval), _nextBulletGen(0.0f),
_stage(other._stage), _moveDirection(other._moveDirection)
{
  ;
}

// destructor
CEnermy::~CEnermy()
{
  if(nullptr != _stage)
  {
    _stage->decreaseEnermy();
  }
}

// copy assignment operator
CEnermy &CEnermy::operator=(const CEnermy &other)
{
  CFlight::operator=(other);
  this->_bulletGenInterval = other._bulletGenInterval;
  this->_nextBulletGen = other._nextBulletGen;
  this->_stage = other._stage;
  this->_moveDirection = other._moveDirection;
  return (*this);
}

// gen bullets
void CEnermy::genBullets()
{
  if(_elapseTime >= _nextBulletGen)
  {
    srand(clock());
    CSprite *sprite = nullptr;
    if((rand()%100)<_circlePercentage)
    {
      CCircleGenerator *circlegenerator = nullptr;
      circlegenerator = new CCircleGenerator(getOwner()->getLocation(), CVector2(0.0f, -1.0f),
                                            CMath::deg2rad(360.0f), 0.0f, 36,
                                            100.0f, ENERMY_BULLET);
      sprite = new CSprite(CSize2(10.0f, 10.0f), "Resources/bullets.png");
      sprite->setDrawRange(CRect(0, 64, 34, 94));
      circlegenerator->addComponentToAll(sprite);
      circlegenerator->addComponentToAll(new CBulletInfo(1));
      circlegenerator->addComponentToAll(new CStraightMove());
      circlegenerator->addComponentToAll(new CCollider(5.0f));
      circlegenerator->addComponentToAll(new CDeleteBullet());
      _stage->getOwner()->addChild(circlegenerator);
    }
    else
    {
      CObject *newbullet = nullptr;
      newbullet = new CObject(getOwner()->getLocation(), ENERMY_BULLET);
      sprite = new CSprite(CSize2(10.0f, 10.0f), "Resources/bullets.png");
      sprite->setDrawRange(CRect(0, 64, 34, 94));
      newbullet->addComponent(sprite);
      newbullet->addComponent(new CMoveInfo(CVector2(0.0f, -1.0f), 100.0f));
      newbullet->addComponent(new CStraightMove());
      newbullet->addComponent(new CBulletInfo(1));
      newbullet->addComponent(new CCollider(5.0f));
      newbullet->addComponent(new CDeleteBullet());
      _stage->getOwner()->addChild(newbullet);
    }
    _nextBulletGen += _bulletGenInterval;
  }
}

// set velocity
void CEnermy::setVelocity(float delta)
{
  ;
}

// on collision
void CEnermy::onColliderEnter(CObject *other)
{
  CComponent::onColliderEnter(other);
  if(other->getTag() == PLAYER_BULLET)
  {
    CBulletInfo *bulletInfo = other->getComponent<CBulletInfo>();
    if(nullptr == bulletInfo)
    {
      return;
    }
    _life -= bulletInfo->getDamage();
    if(_life <= 0)
    {
      getOwner()->deleteObject();
    }
    other->deleteObject();
  }
}
