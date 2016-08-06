//
// CTexture.hpp
//

#ifndef __ENGINE_CTEXTURE_HPP__
#define __ENGINE_CTEXTURE_HPP__

#include "utility.hpp"
#include <GL/gl.h>
#include <string>
#include <unordered_map>

class CTexture;
class CTexCache;
typedef std::unordered_map<std::string, CTexture*> texture_hash;
typedef int Color;        // Color is RGBA value

inline Color makeRGBA(unsigned char r, unsigned g, unsigned b, unsigned a)      // Make RGBA value
{
  int result = (r<<24)|(g<<16)|(b<<16)|(a<<0);
  return result;
}


// CTexture class
// Managing Texture image file
class CTexture
{
  friend CTexCache;
public:
  // copy constructor
  explicit CTexture(const CTexture &other);

  // destructor
  virtual ~CTexture();

  // copy assignment operator
  CTexture &operator=(const CTexture &other);

  // get functions
  inline unsigned int getTexID()const
  {
    return _id;
  }

  inline unsigned int getWidth()const
  {
    return _width;
  }

  inline unsigned int getHeight()const
  {
    return _height;
  }

protected:
  unsigned int _id;
  unsigned int _width;                // width of texture
  unsigned int _height;               // width of texture

  // hide default constructor
  CTexture();
};


class CTexCache
{
public:
  static CTexCache global;

  // default constructor
  explicit CTexCache();

  // copy constructor
  explicit CTexCache(const CTexCache &other);

  // destructor
  virtual ~CTexCache();

  // copy assignment operator
  CTexCache &operator=(const CTexCache &other);

  // load Texture with filename
  CTexture *loadTexture(std::string &filename);
  CTexture *loadTexture(const char *filename);

  // clear _texturecache
  void clear();

private:
  texture_hash _texturecache;
};

#endif
