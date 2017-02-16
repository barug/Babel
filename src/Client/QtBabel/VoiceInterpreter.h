#ifndef	_VOICE_INTERPRETER_H_
# define _VOICE_INTERPRETER_H_

#include <thread>
#include <mutex>
#include <iostream>
#include <cmath>
#include <QByteArray>
#include "./include/portaudio/portaudio.h"
#include "IVoiceInterpreter.hpp"
#include "IUdpSocket.hpp"
#include "RingBuffer.hpp"

// #define SAMPLE_RATE         (44100)
#define SAMPLE_RATE         (24000)

#define FRAMES_PER_BUFFER (512)
#define PA_SAMPLE_TYPE (paFloat32)
/* #define PA_SAMPLE_TYPE (float) */

class			VoiceInterpreter : public IVoiceInterpreter
{
public:

  struct AudioBuffers
  {
    RingBuffer	audioBufferIn;
    RingBuffer	audioBufferOut;
  };

  

private:
  IUdpSocket		*_socket;
  AudioBuffers		_audioBuffers;
  std::thread		*_networkAudioThread;
  bool			*_callOnGoing;
  
 public:  
  VoiceInterpreter(IUdpSocket *socket);
  virtual ~VoiceInterpreter();
  
  virtual void				setHostIpAndPort(std::string ip, int port);
  void				        audioStream(int ownPort);
  virtual  void				startAudioStream(int ownPort);
  virtual void				stopAudioStream();
};

int PortAudioStreamCallback( const void *input,
			     void *output,
			     unsigned long frameCount,
			     const PaStreamCallbackTimeInfo* timeInfo,
			     PaStreamCallbackFlags statusFlags,
			     void *audioBuffers ) ;


#endif // _VOICE_INTERPRETER_H_
