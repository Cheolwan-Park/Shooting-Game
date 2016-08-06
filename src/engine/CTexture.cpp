#include "CTexture.hpp"
#include <FreeImage.h>
#include <GL/gl.h>
#include <cstring>
#include <iostream>

CTexCache CTexCache::global;


// CTexture class

// constructor
CTexture::CTexture()
:_id(0), _width(0), _height(0)
{
  ;
}

// copy constructor
CTexture::CTexture(const CTexture &other)
{
  PRINT_ERROR(CTexture::copyConstructor(), "CTexture class can't be copied");
}

// destructor
CTexture::~CTexture()
{
  glDeleteTextures(1, &_id);
}

// copy assignment operator
CTexture &CTexture::operator=(const CTexture &other)
{
  PRINT_ERROR(CTexture::copyConstructor(), "CTexture class can't be copied");
  return (*this);
}


// CTexCache class

// default constructor
CTexCache::CTexCache()
{
  ;
}

// copy constructor
CTexCache::CTexCache(const CTexCache &other)
{
  PRINT_ERROR(CTexCache::copyConstructor(), "CTexCache class can't be copied");
}

// destructor
CTexCache::~CTexCache()
{
  clear();
}

// copy assignment operator
CTexCache &CTexCache::operator=(const CTexCache &other)
{
  PRINT_ERROR(CTexCache::copyOperator(), "CTexCache class can't be copied");
  return (*this);
}

// load Texture with filename
CTexture *CTexCache::loadTexture(const char *filename)
{
  CTexture *result = nullptr;                   // result pointer
  auto find = _texturecache.find(filename);     // find iterator

  // if there is no cache of file
  if(find == _texturecache.end())
  {
    FREE_IMAGE_FORMAT format = FIF_UNKNOWN;     // image format
    FIBITMAP *image = NULL;                     // image pointer
    FIBITMAP *temp = NULL;                      // image pointer for converting to 32bits image
    unsigned char *pixelbuf = NULL;             // temporary buffer for pixel data
    unsigned int width = 0;                     // width of image
    unsigned int height = 0;                    // height of image

    // get file type
    format = FreeImage_GetFileType(filename);
    // if ther is no file
    if(-1 == format)
    {
      std::cout << "can't open " << filename << std::endl;
      return nullptr;
    }
    // if ther is unknown file format
    else if(FIF_UNKNOWN == format)
    {
      std::cout << "can't read " << filename << std::endl;
      return nullptr;
    }

    // load image
    image = FreeImage_Load(format, filename);
    temp = image;
    image = FreeImage_ConvertTo32Bits(temp);

    if(nullptr == image)
    {
      std::string msg("can't open texture file, filename : "); msg += filename;
      PRINT_ERROR(CTexCache::loadTexture(), msg.c_str());
      return nullptr;
    }

    width = FreeImage_GetWidth(image);
    height = FreeImage_GetHeight(image);
    pixelbuf = (unsigned char*)FreeImage_GetBits(image);

    result = new CTexture;
    result->_width = width;
    result->_height = height;

    glGenTextures(1, &(result->_id));
    glBindTexture(GL_TEXTURE_2D, result->_id);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixelbuf);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    FreeImage_Unload(image);
    FreeImage_Unload(temp);

    _texturecache.insert(texture_hash::value_type(filename, result));
  }
  else
  {
    result = find->second;
  }

  return result;
}

CTexture *CTexCache::loadTexture(std::string &filename)
{
  return loadTexture(filename.c_str());
}

// clear _texturecache
void CTexCache::clear()
{
  for(auto iter : _texturecache)
  {
    SAFE_DELETE_PTR(iter.second);
  }
  _texturecache.clear();
}
