#include "CInput.hpp"	// Input class declare in 'input.hpp'

char CInput::_lastIn = 0;
bool CInput::_mouseLButton = false, CInput::_mouseRButton = false;
CVector2 CInput::_mousePosition;
bool CInput::_keyDownbuf[KEYBUF_LENGTH];
bool CInput::_keyPressedbuf[KEYBUF_LENGTH];
std::string CInput::_textIn = "";


// CInput class

// initialie Input object
void CInput::init()
{
	SDL_EnableUNICODE(1);
	memset(_keyDownbuf, false, KEYBUF_LENGTH * sizeof(bool));
	memset(_keyPressedbuf, false, KEYBUF_LENGTH * sizeof(bool));
}

// call when key is pressed
void CInput::keyDown(const SDL_keysym &key)
{
	_keyDownbuf[key.sym] = true;
	_keyPressedbuf[key.sym] = true;

	if(key.unicode <= 256)
	{
		_lastIn = (char)(key.unicode);
		_textIn += _lastIn;
	}
}

// call when key is pulled
void CInput::keyUp(const SDL_keysym &key)
{
	_keyDownbuf[key.sym] = false;
}

// clear input information
void CInput::clear()
{
	_mousePosition.x = 0.0f;
	_mousePosition.y = 0.0f;
	memset(_keyPressedbuf, false, KEYBUF_LENGTH * sizeof(bool));
}

// clear _clastIn, _strtextIn
void CInput::clearText_Char()
{
	_lastIn = 0;
	_textIn.clear();
}

bool CInput::anyKeyPressed()
{
	for(unsigned i=0; i < KEYBUF_LENGTH; i++)
	{
		if(_keyPressedbuf[i])
		{
			return true;
		}
	}
	return false;
}
