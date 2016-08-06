//
// CSound.hpp
//

#ifndef __ENGINE_SOUND_HPP__
#define __ENGINE_SOUND_HPP__

#include "utility.hpp"
#include <SDL/SDL_mixer.h>
#include <string>
#include <unordered_map>

typedef Mix_Chunk Sound;
typedef std::unordered_map<std::string, Sound*> sound_hash;


class CSound
{
public:
  // init CSound singleton object
  // buffersize = size of sound buffer
  static void init(unsigned int buffersize = 4096);

  // release CSound object
  static void release();

  // play sound, loop = repeat times (default = -1 (infinity)), (repeat loop + 1 times)
  static void playSound(Sound *const sound, int loop = -1);
};


class CSoundCache
{
public:
  static CSoundCache global;

  // default constructor
  explicit CSoundCache();

  // copy constructor
  CSoundCache(const CSoundCache &other);

  // destructor
  virtual ~CSoundCache();

  // copy assignment operator
  CSoundCache &operator=(const CSoundCache &other);

  // load sound
  Sound * loadSound(const std::string &filename);
  Sound *loadSound(const char * const filename);

  // clear Sound cache
  void clear();

private:
  sound_hash _soundCache;
};

// set volume of sound (volume = 0 ~ 100)
inline void setSoundVolume(Sound *const sound, unsigned char volume)
{
  if(nullptr == sound)
    return;
  Mix_VolumeChunk(sound, MIX_MAX_VOLUME * (volume/100));
}


#endif
