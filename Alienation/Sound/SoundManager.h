#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

/**
 * Sound Manager.
 * Looks after the audio subsystem and handles playing of audio content.
 */
class CSoundManager {
   
 public:
   
   /**
    * Constructor.
    */
   CSoundManager();
    
   /**
    * Is the sound system ready to go?
    * @return true if the sound subsystem has been initialised OK.
    */
   bool ready() {return m_bReady;}
    
   /**
    * Play MP3 from file.
    * Will play the specified MP3 file on a continuous loop.
    * @param strFilename The filename to play.
    * @return true if the file loaded OK.
    */
   bool playLoopedMP3(const char* strFilename);

 private:
   
   /**
    * Is the sound system ready to go?
    */
   bool m_bReady;

};

#endif
