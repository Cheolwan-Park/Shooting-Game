//
// CGame.hpp
//

#ifndef __ENGINE_CGAME_HPP__
#define __ENGINE_CGAME_HPP__

#include <SDL/SDL.h>
#include "CRender.hpp"
#include "CInput.hpp"
#include "CSound.hpp"
#include "CCollider.hpp"
#include "CTexture.hpp"

class CGame;

class CGame
{
public:
	// default constructor
	explicit CGame();

	// copy constructor
	CGame(const CGame &other);

	// destructor
	virtual ~CGame();

	// copy assignment operator
	CGame &operator=(const CGame &other);

	// initialie Game object
	// initialie System objects
	// title = caption of window, width = width of window, height = height of window
	void init(const std::string &title, int width, int height);

	// handle SDL_Event
	void handleEventMessage(SDL_Event &event)const;

	// main game loop
	// update program
	void run();

	// update Game object
	void update();

	// change scene
	void changeRoot(CObject *root);

	// add object to game
	CObject *addObject(CObject *object);

private:
	bool _paused;							// if paused, true
	float _frametime;					// framerate
	unsigned _framestart;			// frame start time
	unsigned _frameend;				// frame end time
	unsigned _sleepTime;			// time which cpu has slept
	CObject *_root;						// pointer of root object
};


#endif
