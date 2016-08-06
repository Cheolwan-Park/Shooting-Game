#include "CInvaderGame.hpp"
#include "CStage.hpp"
#include "CPlayer.hpp"

// CInvaderGame class
MAKE_COMPONENT_ID_CPP(CInvaderGame);

// constructor
CInvaderGame::CInvaderGame()
:CComponent::CComponent(),
_countStarted(false), _firstGenned(false),
_remainToRestart(0.0f), _nextPrintTime(0.0f),
_stage(nullptr), _player(nullptr)
{
  ;
}

// copy constructor
CInvaderGame::CInvaderGame(const CInvaderGame &other)
:CComponent::CComponent(other)
{
  ;
}

// destructor
CInvaderGame::~CInvaderGame()
{
  ;
}

// update CInvader component
void CInvaderGame::update(float delta)
{
  CComponent::update(delta);
  if(false == _firstGenned)
  {
    return;
  }

  if(nullptr == _player)
  {
    if((false == _countStarted)
      &&(nullptr != _stage))
    {
      unsigned int killCount = ((_stage->getLevel()-1)*STAGE_WIDTH*STAGE_HEIGHT)+
                              ((STAGE_WIDTH*STAGE_HEIGHT)-_stage->getEnermyCount());
      system("clear");
      printf("======================================\n");
      printf(" kill : %d\n", killCount);
      printf(" level : %d\n", _stage->getLevel()-1);
      printf(" score : %d\n", (_stage->getLevel()-1)*10000 + killCount*100);
      printf("======================================\n");

      CObject *stageOwner = _stage->getOwner();
      SAFE_DELETE_OBJECT(stageOwner);
      _stage = nullptr;
      _remainToRestart = TIME_TO_RESTART;
      _nextPrintTime = TIME_TO_RESTART;
      printf("press 'R' key to restart\n");
      return;
    }
    else if((false == _countStarted)
          &&(nullptr == _stage)
          &&(CInput::isKeyDown(SDLK_r)))
    {
      system("clear");
      printf("remain time to start : %f\n", TIME_TO_RESTART);
      _nextPrintTime -= PRINT_REMAIN_TIME_INTERVAL;
      _countStarted = true;
    }
    else if((true == _countStarted)
          &&(_remainToRestart <= _nextPrintTime))
    {
      if((_remainToRestart <= 0.0f))
      {
        CObject *playerObject = nullptr;
        CObject *stageObject = nullptr;

        system("clear");
        printf("start game!!!\n");

        playerObject = new CObject(CVector2(0.0f, -150.0f));
        stageObject = new CObject(CVector2(0.0f, 0.0f));
        _player = new CPlayer(this);
        _stage = new CStage();

        playerObject->addComponent(_player);
        playerObject->addComponent(new CSprite(CSize2(32.0f, 22.0f),
                                        "Resources/player.png"));
        playerObject->addComponent(new CCollider(5.0f));

        stageObject->addComponent(_stage);

        getOwner()->addChild(playerObject);
        getOwner()->addChild(stageObject);

        _remainToRestart = 0.0f;
        _nextPrintTime = 0.0f;
        _countStarted = false;
        return;
      }
      printf("remain time to start : %f\n", _nextPrintTime);
      _nextPrintTime -= PRINT_REMAIN_TIME_INTERVAL;
    }
  }
  if(_countStarted)
  {
    _remainToRestart -= delta;
  }
}

// set owner
void CInvaderGame::setOwner(CObject *owner)
{
  CComponent::setOwner(owner);

  CObject *playerObject = nullptr;
  CObject *stageObject = nullptr;

  playerObject = new CObject(CVector2(0.0f, -150.0f));
  stageObject = new CObject(CVector2(0.0f, 0.0f));
  _player = new CPlayer(this);
  _stage = new CStage();

  playerObject->addComponent(_player);
  playerObject->addComponent(new CSprite(CSize2(32.0f, 22.0f),
                                  "Resources/player.png"));
  playerObject->addComponent(new CCollider(5.0f));

  stageObject->addComponent(_stage);

  getOwner()->addChild(playerObject);
  getOwner()->addChild(stageObject);

  _firstGenned = true;
  system("clear");
}

// called when player die
void CInvaderGame::playerDie()
{
  _player = nullptr;
}
