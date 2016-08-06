#include "CRender.hpp"
#include <GL/glut.h>
#include <algorithm>
#include <iostream>
#include "CSprite.hpp"

bool CRender::_layerAdded = false;
SDL_Surface *CRender::_screen = nullptr;
layer_vector CRender::_layerVector;
CRect CRender::_view(0.0f, 0.0f, 0.0f, 0.0f);

// compare sprite's depth
bool compare_depth(const CLayer *layer0, const CLayer *layer1)
{
  return layer0->getDepth() > layer1->getDepth();
}


// CRender class

// initialize Render object
void CRender::init(unsigned int width, unsigned int height)
{
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  _screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);

  glDepthFunc(GL_LEQUAL);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glViewport(0, 0, width, height);

  // add default layer
  makeLayer(DEFAULT_LAYER, 0.0f);
}

// update Render object
void CRender::render()
{
  if(_layerAdded)
  {
    std::sort(_layerVector.begin(), _layerVector.end(), compare_depth);
    _layerAdded = false;
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for(auto iter : _layerVector)
  {
    iter->render();
  }

  SDL_GL_SwapBuffers();
}

// set camera's view
void CRender::setCameraView(const CRect &view)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(view._left_bottom.x, view._right_top.x,
          view._left_bottom.y, view._right_top.y,
          0.0f, 1.0f);
  _view = view;
}

// release CRender singleton object
void CRender::release()
{
  for(auto iter : _layerVector)
  {
    SAFE_DELETE_PTR(iter);
  }
}

// add sprite to layer
bool CRender::addSpriteToLayer(char layername, CSprite *sprite)
{
  if(nullptr == sprite)
  {
    PRINT_ERROR(CRender::addSpriteToLayer(), "param is nullptr");
  }
  // find layer
  auto find = _layerVector.begin();
  while(((*find)->getName() != layername)
        &&(find != _layerVector.end()))
  {
    ++find;
  }

  if(find == _layerVector.end())
  {
    PRINT_ERROR(CRender::addSpriteToLayer(),
    "there is no layer that has same name with param")
    return false;
  }
  else
  {
    (*find)->addSprite(sprite);
    return true;
  }
}

// make layer and add to _layerVector
void CRender::makeLayer(char layername, float depth)
{
  if(_layerVector.empty())
  {
    CLayer *layer = new CLayer(layername, depth);
    _layerVector.push_back(layer);
    _layerAdded = true;
  }
  // find layer
  auto find = _layerVector.begin();
  while(((*find)->getName() != layername)
        &&(find != _layerVector.end()))
  {
    ++find;
  }
  if(find == _layerVector.end())
  {
    CLayer *layer = new CLayer(layername, depth);
    _layerVector.push_back(layer);
    _layerAdded = true;
  }
  else
  {
    PRINT_ERROR(CRender::makeLayer(), "there already is same layer");
    return;
  }
}

// delete layer from _layerVector
void CRender::deleteLayer(char layername)
{
  // find layer
  auto find = _layerVector.begin();
  while(((*find)->getName() != layername)
        &&(find != _layerVector.end()))
  {
    ++find;
  }

  if(find == _layerVector.end())
  {
    PRINT_ERROR(CRender::deleteLayer(),
    "there is no layer that has same name with param")
    return;
  }
  else
  {
    SAFE_DELETE_PTR((*find));
    _layerVector.erase(find);
  }
}



// CLayer class

// constructor
CLayer::CLayer(int layername, float depth)
:_depth(depth), _layername(layername)
{
  ;
}

// copy constructor
CLayer::CLayer(const CLayer &other)
{
  PRINT_ERROR(CLayer::copyConstructor(), "CLayer class can't be copied");
}

// destructor
CLayer::~CLayer()
{
  ;
}

// copy assignment operator
CLayer &CLayer::operator=(const CLayer &other)
{
  PRINT_ERROR(CLayer::copyOperator(), "CLayer class can't be copied");
  return (*this);
}

// render layer
void CLayer::render()const
{
  for(auto iter = _spriteHash.begin();
			iter != _spriteHash.end();)
			{
				const CSprite *sprite = iter->second;
				++iter;
				sprite->render();
			}
}

// add sprite to _spriteHash
void CLayer::addSprite(CSprite *sprite)
{
  if(nullptr == sprite)
  {
    PRINT_ERROR(CLayer::addSprite(), "param is nullptr");
    return;
  }
  auto find = _spriteHash.find(sprite);
  // if _spriteHash already has sprite that has same memory address with param sprite
  if(find != _spriteHash.end())
  {
    return;
  }

  sprite->_layer = this;
  _spriteHash.insert(sprite_hash::value_type(sprite, sprite));
}

// erase sprite from _spriteHash
void CLayer::eraseSprite(const CSprite *sprite)
{
  if(nullptr == sprite)
  {
    PRINT_ERROR(CLayer::eraseSprite(), "param is nullptr");
  }
  _spriteHash.erase(sprite);
}
