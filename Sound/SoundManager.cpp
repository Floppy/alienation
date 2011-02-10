#include "Sound/SoundManager.h"
#include "config.h"

namespace NSDSound {

   using namespace NSDMath;

   CSoundManager g_oSoundManager;

   CSoundManager::CSoundManager() :
      m_bReady(false),
      m_pMusic(NULL),
      m_vecPosition(0,0,0),
      m_vecUp(0,1,0),
      m_vecRight(1,0,0)
   {
      if (!Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)) {
         m_bReady = true;
         // allocate 16 mixing channels
         Mix_AllocateChannels(16);
      }

   }

   CSoundManager::~CSoundManager()
   {
      if (m_bReady)
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
      if (m_bReady) {
         Mix_Volume(iChannel,static_cast<int>(MIX_MAX_VOLUME*fVolume));
      }
   }

   float CSoundManager::getVolume(int iChannel)
   {
      if (m_bReady) {
         return Mix_Volume(iChannel,-1);
      }
      else return 0;
   }

   int CSoundManager::load(const char* strFilename)
   {
      int id(-1);
      // Create filename
      char strFile[256];
      strcpy(strFile, "Data/Audio/");
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

   void CSoundManager::setPlaybackLocation(CVector3 vecPosition, CVector3 vecUp, CVector3 vecRight)
   {
      // Store arguments
      m_vecPosition = vecPosition; 
      m_vecUp = vecUp;
      m_vecRight = vecRight;
      // Normalise vectors, just in case
      m_vecUp.normalise();
      m_vecRight.normalise();
   }

   bool CSoundManager::setChannelLocation(int iChannel, CVector3 vecPosition) 
   {
      if (m_bReady) {
         // Calculate direction vector
         CVector3 vecDirection = m_vecPosition - vecPosition;
         // Calculate distance
         float fLength = vecDirection.length();
         unsigned char cDistance = (fLength<500) ? (fLength/500) * 255 : 255;
         // Normalise direction vector
         vecDirection /= fLength;
         // Calculate which side the sound is
         int iAngle = (vecDirection.dot(m_vecRight) > 0) ? -1 : 1;
         // Take cross product of sound vector and local up vector
         vecDirection = m_vecUp.cross(vecDirection);
         // Calculate angle between result and local right vector
         iAngle *= RAD_TO_DEG(vecDirection.angle(m_vecRight));
         // Set channel position
         return (Mix_SetPosition(iChannel,iAngle,cDistance) != 0);
      }
      else return false;
   }

}
