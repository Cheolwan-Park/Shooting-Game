//
// CSprite.hpp
//

#ifndef __ENGINE_CSPRITE_HPP__
#define __ENGINE_CSPRITE_HPP__

#include <GL/gl.h>
#include "CComponent.hpp"
#include "CTexture.hpp"
#include "CRender.hpp"


class CSprite
:public CComponent
{
	friend CLayer;
public:
	// constructor
	explicit CSprite(const CVector2 &size, const char *filename,
											int layer = DEFAULT_LAYER);

	// copy constructor
	CSprite(const CSprite &other);

	// destructor
	virtual ~CSprite();

	// copy assignment operator
	virtual CSprite &operator=(const CSprite &other);

	// update sprite
	virtual void update(float delta);

	// render object
	virtual void render()const;

	// get functions
	virtual inline bool getVisible()const
	{
		return _visible;
	}

	virtual inline float getRotation()const
	{
		return _rotation;
	}

	virtual inline const CTexture *getTexture()const
	{
		return _texture;
	}

	virtual const CSize2 &getSize()const
	{
		return _size;
	}

	virtual const CRect &getDrawRange()const
	{
		return _drawRange;
	}

	// set functions
	virtual void setVisible(bool visible)
	{
		_visible = visible;
	}

	virtual void setRotation(float rotation)
	{
		_rotation = rotation;
	}

	virtual void setSize(const CSize2 &size)
	{
		_size = size;
	}

	virtual void setDrawRange(const CRect &drawRange)
	{
		_drawRange._left_bottom.x = drawRange._left_bottom.x/_texture->getWidth();
		_drawRange._left_bottom.y = drawRange._left_bottom.y/_texture->getHeight();
		_drawRange._right_top.x = drawRange._right_top.x/_texture->getWidth();
		_drawRange._right_top.y = drawRange._right_top.y/_texture->getHeight();
	}

protected:
	bool _visible;											// if visible, true
	float _rotation;										// rotation of sprite
	CTexture *_texture;									// pointer of texture that is used to render
	CLayer *_layer;											// pointer of layer that this sprite belongs to
	CSize2 _size;												// size of sprite
	CRect _drawRange;										// using range of texture to render
};


#endif
