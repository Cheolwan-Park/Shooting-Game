#include "CGame.hpp"

const float MAX_FRAME_TIME = 0.016f;		// min framerate time


// CGame class

// default constructor
CGame::CGame()
:_paused(false), _frametime(0),
_framestart(0), _frameend(0),
_sleepTime(0), _root(nullptr)
{
	;
}

// copy constructor
CGame::CGame(const CGame &other)
{
	PRINT_ERROR(CGame::copyConstructor(), "CGame class can't be copied");
}

// destructor
CGame::~CGame()
{
	SAFE_DELETE_PTR(_root);
	CSound::release();
	CRender::release();
	SDL_Quit();
}

// copy assignment operator
CGame &CGame::operator=(const CGame &other)
{
	PRINT_ERROR(CGame::copyOperator(), "CGame class can't be copied");
	return (*this);
}

// initialize Game object
void CGame::init(const std::string &title, int width, int height)
{
	if(0 != SDL_Init(SDL_INIT_EVERYTHING))
	{
		PRINT_ERROR(Game::initialize(), SDL_GetError());
	}
	SDL_WM_SetCaption(title.c_str(), NULL);	// set window caption

	CInput::init();
	CRender::init(width, height);
	CSound::init();
	CRender::setCameraView(CRect(-1*(width/2),-1*(height/2), height/2, width/2));
}

// handle SDL_Event
void CGame::handleEventMessage(SDL_Event &event) const
{
	switch(event.type)
	{
	case SDL_KEYDOWN:
		CInput::keyDown(event.key.keysym);
		break;

	case SDL_KEYUP:
		CInput::keyUp(event.key.keysym);
		break;

	case SDL_MOUSEMOTION:
		CInput::setMousePos(CVector2(event.motion.x, event.motion.y));
		break;

	case SDL_MOUSEBUTTONDOWN:
		if(SDL_BUTTON_LEFT == event.button.button)
		{
			CInput::setMouseLButtonState(true);
		}
		if(SDL_BUTTON_RIGHT == event.button.button)
		{
			CInput::setMouseRButtonState(true);
		}

		CInput::setMousePos(CVector2(event.button.x, event.button.y));
		break;

	case SDL_MOUSEBUTTONUP:
		if(SDL_BUTTON_LEFT == event.button.button)
		{
			CInput::setMouseLButtonState(false);
		}
		if(SDL_BUTTON_RIGHT == event.button.button)
		{
			CInput::setMouseRButtonState(false);
		}

		CInput::setMousePos(CVector2(event.button.x, event.button.y));
		break;

	default: break;

	}
}

// main loop of game
// update program
void CGame::run()
{
	if (false == _paused)	// if game was not paused
	{
		_frameend = SDL_GetTicks();
		// calc frameTime
		_frametime = (float) (_frameend - _framestart) / 1000;

		if (_frametime < MAX_FRAME_TIME)
		{
			_sleepTime = (unsigned) ((MAX_FRAME_TIME - _frametime) * 1000);
			SDL_Delay(_sleepTime);
			_sleepTime = 0.0f;
		}
		_framestart = _frameend;

		// update Game object
		update();
	}
}

// update Game object
void CGame::update()
{
	if (nullptr != _root)
	{
		_root->update(_frametime);
	}

	// update systems
	CCollisionChecker::global.update();
	CRender::render();
	CInput::clear();
}

// change root object
void CGame::changeRoot(CObject *root)
{
	if(nullptr == root)
	{
		PRINT_ERROR(CGame::changeRoot(), "param is nullptr");
		return;
	}
	SAFE_DELETE_PTR(_root);
	_root = root;
}

// add Object to game
CObject *CGame::addObject(CObject *object)
{
	if(nullptr == object)
	{
		PRINT_ERROR(CGame::addObject(), "param is nullptr");
		return nullptr;
	}
	if(_root == nullptr)
	{
		PRINT_ERROR(CGame::addObject(), "there is no root object yet");
		return object;
	}
	_root->addChild(object);
	return object;
}
