//
// CRender.hpp
//

#ifndef __ENGINE_RENDER_HPP__
#define __ENGINE_RENDER_HPP__

#include <SDL/SDL.h>
#include <vector>
#include <string>
#include <unordered_map>
#include "CVector2.hpp"

class CRender;
class CSprite;
class CLayer;
typedef std::unordered_map<const CSprite*, const CSprite*> sprite_hash;
typedef std::vector<CLayer*> layer_vector;
const char DEFAULT_LAYER = 0;


class CRender
{
public:
  // initialie Render objects
  static void init(unsigned int width, unsigned int height);

  // update Render object
  static void render();

  // set camera's view
  static void setCameraView(const CRect &view);

  // release CRender singleton object
  // this function also delete all layer that belongs to CRender
  static void release();

  // add sprite to layer
  // return false, if there is not layer that has name, param layername
  static bool addSpriteToLayer(char layername, CSprite *sprite);

  // make layer and add to _layerVector;
  static void makeLayer(char layername, float depth);

  // delete layer from _layerVector
  // this function call delete function
  static void deleteLayer(char layername);

  // get funtion
  static inline const CRect &getViewPort()
  {
    return _view;
  }

  static inline SDL_Surface *getScreenSurface()
  {
    return _screen;
  }

private:
  static bool _layerAdded;                 // if sprite was added in this frame, true (if value is true, sort _spriteVector)
  static SDL_Surface *_screen;              // screen surface, to display text
  static layer_vector _layerVector;         // vector of sprite that CRender object will display
  static CRect _view;                       // view range

  // singleton
  CRender()
  {
    ;
  }
};


class CLayer
{
public:
  // constructor
  explicit CLayer(int layername, float depth);

  // copy constructor
  CLayer(const CLayer &other);

  // destructor
  virtual ~CLayer();

  // copy assignment operator
  CLayer &operator=(const CLayer &other);

  // render layer
  void render()const;

  // add sprite to _spriteHash
  void addSprite(CSprite *sprite);

  // erase sprite from _spriteHash
  void eraseSprite(const CSprite *sprite);

  // get functions
  inline float getDepth()const
  {
    return _depth;
  }

  inline char getName()const
  {
    return _layername;
  }

protected:
  float _depth;                   // depth of layer
  char _layername;                // name of layer
  sprite_hash _spriteHash;        // sprite hash
};


#endif
