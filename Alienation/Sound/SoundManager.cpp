#include "Sound/SoundManager.h"
#include "config.h"

CSoundManager g_oSoundManager;

CSoundManager::CSoundManager() :
   m_bReady(false),
   m_pMusic(NULL),
   m_vecPosition(0,0,0),
   m_vecHeading(0,0,1),
   m_vecUp(0,1,0)
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

void CSoundManager::setVolume(float fVolume, int iChannel) 
{
   Mix_Volume(iChannel,static_cast<int>(MIX_MAX_VOLUME*fVolume));
}

float CSoundManager::getVolume(int iChannel)
{
   return Mix_Volume(iChannel,-1);
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

int CSoundManager::play(int iSample, int iNumRepeats, int iFadeIn, int iCutoff) 
{
   if (m_bReady && iSample >= 0) {
      if (iFadeIn) {
         return Mix_FadeInChannelTimed(-1, m_oSamples[iSample], iNumRepeats, iFadeIn, iCutoff);
      }
      else {
         return Mix_PlayChannelTimed(-1, m_oSamples[iSample], iNumRepeats, iCutoff);
      }
   }
   return -1;
}

void CSoundManager::stop(int iChannel, int iFadeOut) 
{
   if (m_bReady) {
      if (iFadeOut) {
         Mix_FadeOutChannel(iChannel, iFadeOut);
      }
      else {
         Mix_HaltChannel(iChannel);
      }
   }
}

void CSoundManager::setPlaybackLocation(CVector3 vecPosition, CVector3 vecHeading, CVector3 vecUp)
{
   // Store arguments
   m_vecPosition = vecPosition;
   m_vecHeading = vecHeading;
   m_vecUp = vecUp;
}

bool CSoundManager::setChannelLocation(int iChannel, CVector3 vecPosition) 
{
   // Calculate angle
   int iAngle = 0;
   // Calculate distance
   unsigned char cDistance = static_cast<unsigned char>((m_vecPosition - vecPosition).length());
   // Set channel position
   return Mix_SetPosition(iChannel,iAngle,cDistance);
}
