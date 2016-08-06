#include "CPlayer.hpp"
#include "CStraightMove.hpp"
#include "CDeleteBullet.hpp"
#include "CBulletInfo.hpp"
#include "CEnermy.hpp"
#include "CInvaderGame.hpp"

// CPlayer class
MAKE_COMPONENT_ID_CPP(CPlayer);

// constructor
CPlayer::CPlayer(CInvaderGame *invaderGame)
:CFlight::CFlight(LIFE),
_nextGen(0.0f), _invaderGame(invaderGame)
{
  ;
}

// copy constructor
CPlayer::CPlayer(const CPlayer &other)
:CFlight::CFlight(other), _nextGen(other._nextGen),
_invaderGame(other._invaderGame)
{
  ;
}

// destructor
CPlayer::~CPlayer()
{
  _invaderGame->playerDie();
}

// copy assignment operator
CPlayer &CPlayer::operator=(const CPlayer &other)
{
  CFlight::operator=(other);
  this->_nextGen = other._nextGen;
  return (*this);
}

// gen bullets
void CPlayer::genBullets()
{
  if(_nextGen < _elapseTime)
  {
    _nextGen += 0.08f;

    CObject *bullet = new CObject(getOwner()->getLocation(), PLAYER_BULLET);
    bullet->addComponent(new CMoveInfo(CVector2(0.0f, 1.0f), 200.0f));
    bullet->addComponent(new CStraightMove());
    CSprite *sprite = new CSprite(CSize2(10.0f, 10.0f), "Resources/bullets.png");
    sprite->setDrawRange(CRect(0, 64, 30, 94));
    bullet->addComponent(sprite);
    bullet->addComponent(new CDeleteBullet());
    bullet->addComponent(new CBulletInfo(1));
    bullet->addComponent(new CCollider(5.0f));
    getOwner()->getParent()->addChild(bullet);
  }
}

// update CPlayer component
void CPlayer::update(float delta)
{
  CFlight::update(delta);
  if(!CRender::getViewPort().isOverlaped(getOwner()->getLocation()))
  {
    getOwner()->setLocation(_lastLocation);
  }
  _lastLocation = getOwner()->getLocation();
}

// set velocity
void CPlayer::setVelocity(float delta)
{
  float speed = 100.0f*delta;
  if(CInput::isKeyDown(SDLK_LSHIFT))
  {
    speed /= 2.0f;
  }
  if(CInput::isKeyDown(SDLK_UP))
  {
    _velocity.y += speed;
  }
  else if(CInput::isKeyDown(SDLK_DOWN))
  {
    _velocity.y -= speed;
  }
  if(CInput::isKeyDown(SDLK_LEFT))
  {
    _velocity.x -= speed;
  }
  else if(CInput::isKeyDown(SDLK_RIGHT))
  {
    _velocity.x += speed;
  }
}

// called when collision
void CPlayer::onColliderEnter(CObject *other)
{
  CComponent::onColliderEnter(other);
  if(other->getTag() == ENERMY_BULLET)
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
