#include "RingBuffer.hpp"

RingBuffer::RingBuffer()
{

}
RingBuffer::~RingBuffer()
{

}

void			RingBuffer::writeBuffer(float *data, unsigned int dataSize)
{
  unsigned int tmpWriteIndex;

  _writeIndexMutex.lock();
  tmpWriteIndex = _writeIndex;
  _writeIndexMutex.unlock();
  for (unsigned int i = 0; i < dataSize; i++)
    {
      _buffer[tmpWriteIndex] = data[i];
      tmpWriteIndex = (tmpWriteIndex + 1) % B_BUFFER_SIZE;
    }
  _writeIndexMutex.lock();
  _writeIndex = tmpWriteIndex;
  _writeIndexMutex.unlock();  
}

std::vector<float>	RingBuffer::readBuffer()
{
  unsigned int tmpReadIndex;
  unsigned int tmpWriteIndex;
  std::vector<float> data;
  
  _readIndexMutex.lock();
  tmpReadIndex = _readIndex;
  _readIndexMutex.unlock();
  _writeIndexMutex.lock();
  tmpWriteIndex = _writeIndex;
  _writeIndexMutex.unlock();
  
  if (tmpWriteIndex != tmpReadIndex)
    {
      for (unsigned int i = 0; i < FRAMES_PER_BUFFER; i++)
	{
	  data.push_back(_buffer[tmpReadIndex]);
	  tmpReadIndex = (tmpReadIndex + 1) % B_BUFFER_SIZE;
	}
    }
  _readIndexMutex.lock();
  _readIndex = tmpReadIndex;
  _readIndexMutex.unlock();
  return data;
}
