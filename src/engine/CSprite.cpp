#include "CSprite.hpp"
#include "CObject.hpp"

// CSprite class

// constructor
CSprite::CSprite(const CSize2 &size, const char *filename, int layer)
:CComponent::CComponent(), _visible(true), _rotation(0.0f),
 _texture(CTexCache::global.loadTexture(filename)), _layer(nullptr),
 _size(size), _drawRange(0.0f, 0.0f, 1.0f, 1.0f)
{
	CRender::addSpriteToLayer(layer, this);
}

// copy constructor
CSprite::CSprite(const CSprite &other)
:CComponent::CComponent(other), _visible(other._visible), _rotation(other._rotation),
 _texture(other._texture), _layer(other._layer), _size(other._size), _drawRange(other._drawRange)
{
	CRender::addSpriteToLayer(_layer->getName(), this);
}

// destructor
CSprite::~CSprite()
{
	_layer->eraseSprite(this);
}

// copy assignment operator
CSprite &CSprite::operator=(const CSprite &other)
{
	CComponent::operator=(other);
	_layer->eraseSprite(this);
	this->_visible = other._visible;
	this->_rotation = other._rotation;
	this->_texture = other._texture;
	this->_layer = other._layer;
	this->_size = other._size;
	this->_drawRange = other._drawRange;
	CRender::addSpriteToLayer(_layer->getName(), this);
	return (*this);
}

// update sprite
void CSprite::update(float delta)
{
	CComponent::update(delta);
}

// render object
void CSprite::render()const
{
	if(!_visible)
	{
		return;
	}
	const CVector2 &location = _owner->getLocation();
	float half_size_x = _size.x/2;
	float half_size_y = _size.y/2;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(_rotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(location.x, location.y, 0.0f);

	glBindTexture(GL_TEXTURE_2D, _texture->getTexID());
	glBegin(GL_QUADS);
	{
		// left bottom
		glTexCoord2f(_drawRange._left_bottom.x, _drawRange._left_bottom.y);
		glVertex2f(-1*half_size_x, -1*half_size_y);

		// left top
		glTexCoord2f(_drawRange._left_bottom.x, _drawRange._right_top.y);
		glVertex2f(-1*half_size_x, half_size_y);

		// right top
		glTexCoord2f(_drawRange._right_top.x, _drawRange._right_top.y);
		glVertex2f(half_size_x, half_size_y);

		// right bottom
		glTexCoord2f(_drawRange._right_top.x, _drawRange._left_bottom.y);
		glVertex2f(half_size_x, -1*half_size_y);
	}
	glEnd();
}
