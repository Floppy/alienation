#include "Sound/SoundManager.h"
#include "config.h"

CSoundManager g_oSoundManager;

CSoundManager::CSoundManager() :
   m_bReady(false),
   m_pMusic(NULL)
{
   if (!Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)) {
      m_bReady = true;
      // allocate 16 mixing channels
      Mix_AllocateChannels(16);
   }

}

CSoundManager::~CSoundManager()
{
   // Stop playing
   Mix_HaltChannel(-1);
   // Free music file
   if (m_pMusic) 
      Mix_FreeMusic(m_pMusic);
   // Dump all loaded samples
   for (std::vector<Mix_Chunk*>::iterator it(m_oSamples.begin()); it != m_oSamples.end(); it++) {
      Mix_FreeChunk(*it);
   }
   // Close audio device
   Mix_CloseAudio();
}

bool CSoundManager::playMusicFile(const char* strFilename) 
{
   if (m_bReady) {
      // Create filename
      char strFile[256];
      strcpy(strFile, "./Data/Audio/");
      strcat(strFile, strFilename);   
      // Load file
      m_pMusic = Mix_LoadMUS(strFile);
      // Play
      if (m_pMusic) {
         Mix_PlayMusic(m_pMusic,-1);
         return true;
      }
   }
   return false;
}

void CSoundManager::setMasterVolume(float fVolume) 
{
   Mix_Volume(-1,static_cast<int>(MIX_MAX_VOLUME*fVolume));
}

float CSoundManager::getMasterVolume()
{
   return Mix_Volume(-1,-1);
}

int CSoundManager::load(const char* strFilename)
{
   int id(-1);
   // Create filename
   char strFile[256];
   strcpy(strFile, "./Data/Audio/");
   strcat(strFile, strFilename);   
   // Load from file
   Mix_Chunk* pSample = Mix_LoadWAV(strFile);
   if (pSample) {
      // Get ID
      id = m_oSamples.size();
      // Store sample
      m_oSamples.push_back(pSample);
   }
   // Done
   return id;
}

void CSoundManager::play(int iSample, int iNumRepeats) 
{
   if (m_bReady && iSample >= 0)
      Mix_PlayChannel(-1, m_oSamples[iSample], iNumRepeats);
}

void CSoundManager::playTime(int iSample, int iTime)
{
   if (m_bReady && iSample >= 0)
      Mix_PlayChannelTimed(-1, m_oSamples[iSample], -1, iTime);
}
