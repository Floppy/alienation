#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL/SDL_mixer.h>
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
    * Set master volume.
    * @param fVolume A float between 0 (lowest volume) and 1 (highest volume).
    */
   void setMasterVolume(float fVolume);

   /**
    * Get master volume.
    * @return A float between 0 (lowest volume) and 1 (highest volume).
    */
   float getMasterVolume();

   /**
    * Load a sample from disk
    * @return The sample ID. If the file could not be loaded, -1 is returned.
    */
   int load(const char* strFilename);

   /**
    * Play a sample
    * @param iSample The sample ID to play.
    * @param iNumRepeats How many times to repeat the sample. A value of 1 will play the sample twice.
    */
   void play(int iSample, int iNumRepeats = 0);

   /**
    * Play a sample, looping for a particular time.
    * @param iSample The sample ID to play.
    * @param iTime How many milliseconds to play the sample for.
    */
   void playTime(int iSample, int iTime);

 private:
   
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

};

/**
 * A global instance of the CSoundManager class. 
 * All sound access should be done through this object.
 */
extern CSoundManager g_oSoundManager;

#endif
