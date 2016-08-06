// input.hpp

#ifndef __COREENGINE_INPUT_HPP__
#define __COREENGINE_INPUT_HPP__

#include <SDL/SDL.h>
#include <string>
#include "CVector2.hpp"

const unsigned KEYBUF_LENGTH = 325;


class CInput
{
private:
	static char _lastIn;													// character last typed
	static bool _mouseLButton, _mouseRButton;			// if button was pushed, true
	static CVector2 _mousePosition;								// mouse position
	static bool _keyDownbuf[KEYBUF_LENGTH];				// while key was pressed, true
	static bool _keyPressedbuf[KEYBUF_LENGTH];		// if key pressed, true
	static std::string _textIn;										// string typed

public:

	// initialize Input object
	static void init();

	// call when key is pressed
	static void keyDown(const SDL_keysym &key);

	// call when key is pulled
	static void keyUp(const SDL_keysym &key);

	// clear input information
	static void clear();

	// clear _lastIn, _textIn
	static void clearText_Char();

	// check if any key pressed while current frame
	static bool anyKeyPressed();

	// set functions
	// call when mouse position was changed
	static inline void setMousePos(const CVector2 &newPosition)
	{
		_mousePosition = newPosition;
	}

	// set _mouseLButton
	static inline void setMouseLButtonState(bool state)
	{
		_mouseLButton = state;
	}

	// set _mouseRButton
	static inline void setMouseRButtonState(bool state)
	{
		_mouseRButton = state;
	}

	// get functions
	// check if key was pressed
	static inline bool isKeyDown(const SDLKey &key)
	{
		return _keyDownbuf[key];
	}

	// check if key pressed
	static inline bool isKeyPressed(const SDLKey &key)
	{
		return _keyPressedbuf[key];
	}

	// get _mouseLButton
	static inline bool isMouseLButtonClick()
	{
		return _mouseLButton;
	}

	// get _mouseRButton
	static inline bool isMouseRButtonClick()
	{
		return _mouseRButton;
	}

	// get moust position
	static inline const CVector2 &getMousePosition()
	{
		return _mousePosition;
	}

	// get _lastIn
	static inline char getLastInChar()
	{
		return _lastIn;
	}

	// get _textIn
	static inline const std::string &getTextIn()
	{
		return _textIn;
	}

};



#endif
