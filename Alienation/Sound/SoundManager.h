#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

class CSoundManager {
  
 public:

  CSoundManager();
  //: Constructor

  bool Ready() {return m_bReady;}
  //: Is the sound system ready to go?

  bool PlayLoopedMP3(const char* filename);
  //: Play a looped audio file
  // returns true if successful, false if file could not be played

 private:

  bool m_bReady;
  //: Is the sound system ready to go?


};

#endif
