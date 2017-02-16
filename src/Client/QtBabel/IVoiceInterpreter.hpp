#ifndef _INTERFACE_VOICE_INTERPRETER_HPP_
# define _INTERFACE_VOICE_INTERPRETER_HPP_

class IVoiceInterpreter
{
public:
  virtual ~IVoiceInterpreter() {}

  virtual void				setHostIpAndPort(std::string ip, int port) = 0;
  virtual void				startAudioStream(int ownPort) = 0;
  virtual void				stopAudioStream() = 0;
};



#endif	// _INTERFACE_VOICE_INTERPRETER_HPP__
