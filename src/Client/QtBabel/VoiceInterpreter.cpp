#include "VoiceInterpreter.h"

#include <cstring>

VoiceInterpreter::VoiceInterpreter(IUdpSocket *socket)
  : _socket(socket),
    _audioBuffers{},
    _callOnGoing(new bool(false))
{
}

VoiceInterpreter::~VoiceInterpreter()
{
}

int	        PortAudioStreamCallback(const void *inputBuffer,
					void *outputBuffer,
					unsigned long frameCount,
					const PaStreamCallbackTimeInfo* timeInfo,
					PaStreamCallbackFlags statusFlags,
					void *audioBuff)
{
  (void) timeInfo;
  (void) statusFlags;
  float *input = (float*) inputBuffer;
  float *output = (float*) outputBuffer;
  std::vector<float> outData;
  VoiceInterpreter::AudioBuffers *audioBuffers = (VoiceInterpreter::AudioBuffers*) audioBuff;

  outData = audioBuffers->audioBufferOut.readBuffer();

  if (outData.size() > 0)
    {
      for (unsigned int i = 0; i < frameCount; i++)
	{
	  output[i] = outData[i];
	}
    }
  if (input)
    {
      audioBuffers->audioBufferIn.writeBuffer(input, frameCount);
    }
  return paContinue;
}

void		VoiceInterpreter::setHostIpAndPort(std::string ip, int port)
{
  _socket->setHostIp(ip);
  _socket->setHostPort(port);
}

void		VoiceInterpreter::audioStream(int ownPort)
{
  PaStreamParameters inputParameters, outputParameters;
  PaStream *stream;
  PaError err;
  
  err = Pa_Initialize();
  if( err != paNoError )
    std::cout << Pa_GetErrorText( err ) << std::endl;

  inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
  if (inputParameters.device == paNoDevice) {
    std::cout << "Error: No default input device." << std::endl;
  }
  inputParameters.channelCount = 1;       /* stereo input */
  inputParameters.sampleFormat = PA_SAMPLE_TYPE;
  inputParameters.suggestedLatency =
    Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
  inputParameters.hostApiSpecificStreamInfo = NULL;
  
  outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
  if (outputParameters.device == paNoDevice) {
    std::cout << "Error: No default output device." << std::endl;
  }
  outputParameters.channelCount = 1;       /* stereo output */
  outputParameters.sampleFormat = PA_SAMPLE_TYPE;
  outputParameters.suggestedLatency =
    Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;

  err = Pa_OpenStream(&stream,
		      &inputParameters,
		      &outputParameters,
		      SAMPLE_RATE,
		      FRAMES_PER_BUFFER,
		      0,
		      PortAudioStreamCallback,
		      &_audioBuffers);
 if( err != paNoError )
    std::cout << Pa_GetErrorText( err ) << std::endl;

 err = Pa_StartStream( stream );
 if( err != paNoError )
   std::cout << Pa_GetErrorText( err ) << std::endl;
 
 _socket->bindUdp(ownPort);
 
 QByteArray datagram;
 std::vector<float> inData;
 while(*_callOnGoing)
   {
     inData = _audioBuffers.audioBufferIn.readBuffer();
     if (inData.size() > 0)
       {
	 _socket->sendData(inData.data());
       }
     datagram = _socket->waitForRead();
     if (datagram.size() > 0)
       {
	 _audioBuffers.audioBufferOut.writeBuffer((float*) datagram.data(),
						  datagram.size() / sizeof(float));
       }
   }
 err = Pa_CloseStream( stream );
  if( err != paNoError )
   std::cout << Pa_GetErrorText( err ) << std::endl;
 err = Pa_Terminate();
 if( err != paNoError )
   std::cout << Pa_GetErrorText( err ) << std::endl;
 std::cout << "terminate call" << std::endl;
}

void		VoiceInterpreter::startAudioStream(int ownPort)
{
  *_callOnGoing = true;
  _networkAudioThread = new std::thread([this, ownPort](){this->audioStream(ownPort);});
}

void		VoiceInterpreter::stopAudioStream()
{
  *_callOnGoing = false;
}

