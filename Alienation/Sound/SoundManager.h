#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL_mixer.h>
#include "Math/Vector.h"
#include <vector>

using namespace std;

/**
 * Sound Manager.
 * Looks after the audio subsystem and handles playing of audio content.
 */
class CSoundManager {
   
 public:
   
   /**
    * Constructor.
    * Initialises the sound subsystem.
    */
   CSoundManager();

   /**
    * Destructor.
    * Shuts down the sound subsystem.
    */
   ~CSoundManager();
    
   /**
    * Is the sound system ready to go?
    * @return true if the sound subsystem has been initialised OK.
    */
   bool ready() {return m_bReady;}
    
   /**
    * Play some music from file.
    * Will play the specified file on a continuous loop.
    * @param strFilename The filename to play.
    * @return true if the file loaded OK.
    */
   bool playMusicFile(const char* strFilename);

   /**
    * Set channel volume.
    * @param iChannel The channel to change the volume on, obtained from play(). If -1, all channels are changed.
    * @param fVolume A float between 0 (lowest volume) and 1 (highest volume).
    */
   void setVolume(float fVolume, int iChannel = -1);

   /**
    * Get channel volume.
    * @param iChannel The channel to get the volume from, obtained from play(). If -1, the average volume is returned.
    * @return A float between 0 (lowest volume) and 1 (highest volume).
    */
   float getVolume(int iChannel = -1);

   /**
    * Load a sample from disk
    * @return The sample ID. If the file could not be loaded, -1 is returned.
    */
   int load(const char* strFilename);

   /**
    * Play a sample
    * @param iSample The sample ID to play.
    * @param iNumRepeats How many times to repeat the sample. A value of 1 will play the sample twice. A value of -1 will play forever until stopped.
    * @param iFadeIn The sample will fade in over this many milliseconds.
    * @param iCutoff Playback will be stopped after this many milliseconds.
    * @return A channel ID which can be used to stop the sample playing or change volume.
    */
   int play(int iSample, int iNumRepeats = 0, int iFadeIn = 0, int iCutoff = -1);

   /**
    * Stop sample playback.
    * @param iChannel The channel ID to stop playing, obtained from play().
    * @param iFadeOut Fade out over this many milliseconds.
    */
   void stop(int iChannel, int iFadeOut = 0);

   /**
    * Set playback location.
    * @param vecPosition The position of the final sound output.
    * @param vecUp The local +Y vector at the sound output location.
    * @param vecRight The local +X vector at the sound output location.
    */
   void setPlaybackLocation(CVector3 vecPosition, CVector3 vecUp, CVector3 vecRight);

   /**
    * Set 3D location for a particular channel.
    * @param iChannel The channel ID to spatialise, obtained from play().
    * @param vecPosition The 3D position that the channel should come from.
    * @return false if an error occurred.
    * @bug Does not perform angle calculations yet, as I haven't bothered to work the maths out.
    */
   bool setChannelLocation(int iChannel, CVector3 vecPosition);

 protected:
   
   /**
    * Is the sound system ready to go?
    */
   bool m_bReady;

   /**
    * An array of samples
    */
   vector<Mix_Chunk*> m_oSamples;

   /**
    * Background music
    */
   Mix_Music* m_pMusic;

   /**
    * Playback location
    */
   CVector3 m_vecPosition;

   /**
    * Playback location - up vector.
    */
   CVector3 m_vecUp;

   /**
    * Playback location - right vector.
    */
   CVector3 m_vecRight;

};

/**
 * A global instance of the CSoundManager class. 
 * All sound access should be done through this object.
 */
extern CSoundManager g_oSoundManager;

#endif
