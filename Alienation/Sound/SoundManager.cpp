#include "Sound/SoundManager.h"
#include "config.h"

#include <fmod.h>

CSoundManager::CSoundManager() :
  m_bReady(false)
{
  if (FSOUND_Init(44100, 64, 0))
    m_bReady = true;
}

bool CSoundManager::playLoopedMP3(const char* strFilename) 
{
  FSOUND_STREAM * poMod = NULL;
  // Load file
  poMod = FSOUND_Stream_OpenFile(strFilename, FSOUND_LOOP_NORMAL, 0);
  // Play
  if (poMod)
  {
    FSOUND_Stream_Play(FSOUND_FREE, poMod);
    return true;
  }
  return false;  
}

