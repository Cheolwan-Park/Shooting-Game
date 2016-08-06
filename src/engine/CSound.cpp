#include "CSound.hpp"

CSoundCache CSoundCache::global;


// CSound class

// init CSound class
void CSound::init(unsigned int buffersize)
{
  Mix_Init(0);
  if(0 != Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, buffersize))
  {
    PRINT_ERROR(CSound::init(), SDL_GetError());
  }
}

// release CSound object
void CSound::release()
{
  CSoundCache::global.clear();
  Mix_CloseAudio();
  Mix_Quit();
}

// play sound
void CSound::playSound(Sound *sound, int loop)
{
  if(nullptr == sound)
  {
    PRINT_ERROR(CSound::playSound(), "param is nullptr");
    return;
  }

  if(0 > Mix_PlayChannel(-1, sound, loop))
  {
    PRINT_ERROR(CSound::playSound(), SDL_GetError());
  }
}


// CSoundCache class

// default constructor
CSoundCache::CSoundCache()
{
  ;
}

// copy constructor
CSoundCache::CSoundCache(const CSoundCache &other)
{
  PRINT_ERROR(CSoundCache::copyConstructor(), "CSoundCache class can't be copied");
}

// destructor
CSoundCache::~CSoundCache()
{
  clear();
}

// copy assignment operator
CSoundCache &CSoundCache::operator=(const CSoundCache &other)
{
  PRINT_ERROR(CSoundCache::copyOperator(), "CSoundCache class can't be copied");
  return (*this);
}

// load sound
Sound *CSoundCache::loadSound(const std::string &filename)
{
  Sound *result = nullptr;
  auto find = _soundCache.find(filename);
  if(find != _soundCache.end())
  {
    PRINT_ERROR(CSoundCache::loadSound(), "CSoundCache already has same Sound");
    result = find->second;
  }
  else
  {
    result = Mix_LoadWAV(filename.c_str());
    if(nullptr == result)
    {
      PRINT_ERROR(CSoundCache::loadSound(), SDL_GetError());
    }
    _soundCache.insert(sound_hash::value_type(filename, result));
  }
  return result;
}

Sound *CSoundCache::loadSound(const char *const filename)
{
  return loadSound(std::string(filename));
}

// clear sound cache
void CSoundCache::clear()
{
  for(auto iter : _soundCache)
  {
    Mix_FreeChunk(iter.second);
  }
  _soundCache.clear();
}
