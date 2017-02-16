#include "QtCircularBuffer.h"
#include <cstring>
#include <iostream>

QtCircularBuffer::QtCircularBuffer()
{
}

QtCircularBuffer::~QtCircularBuffer()
{
}

Message				*QtCircularBuffer::readInBuffer()
{
  std::vector<unsigned char>	*buffer;
  unsigned int			dataLength = 0;
  unsigned int			i = 0;
  
  if (this->_inBuffer.size() < IOHEADER_SIZE)
    return nullptr;
  unsigned char size[4] = {_inBuffer[2],
			   _inBuffer[3],
			   _inBuffer[4],
			   _inBuffer[5]};
  std::memcpy(&dataLength, size, 4);
  if (dataLength + IOHEADER_SIZE > this->_inBuffer.size())
    return NULL;
  buffer = new std::vector<unsigned char>;
  while (i < dataLength + IOHEADER_SIZE)
    {
      buffer->push_back(this->_inBuffer.front());
      this->_inBuffer.pop_front();
      i++;
    }
  return new Message(buffer);
}

bool				QtCircularBuffer::writeInBuffer(unsigned char *data, unsigned int size)
{
  if (!data || !size || 4096 - this->_inBuffer.size() < size)
    return false;
  for (unsigned int i = 0; i < size; i++)
    this->_inBuffer.push_back((unsigned char)data[i]);
  return true;
}
 
std::vector<unsigned char>	*QtCircularBuffer::readOutBuffer()
{
  std::vector<unsigned char>	*buffer;
  unsigned int			dataLength = 0;
  unsigned int			i = 0;

  if (this->_outBuffer.size() < IOHEADER_SIZE)
    return NULL;
  std::cout << "trying to read" << std::endl;
  unsigned char  size[4] = {_outBuffer[2],
			    _outBuffer[3],
			    _outBuffer[4],
			    _outBuffer[5]};
  std::memcpy(&dataLength, size, 4);
  if (dataLength + IOHEADER_SIZE > this->_outBuffer.size())
    {
      std::cout << "invalid size" << std::endl;
      return NULL;
    }
  buffer = new std::vector<unsigned char>;
  while (i < dataLength + IOHEADER_SIZE)
    {
      buffer->push_back(this->_outBuffer.front());
      this->_outBuffer.pop_front();
      i++;
    }
  return buffer;
}

bool				QtCircularBuffer::writeOutBuffer(void *IOHeader, unsigned char *data)
{
  unsigned char     *buffer;
  unsigned int      dataSize = 0;

  if (IOHeader == nullptr)
    return false;
  buffer = (unsigned char*)(IOHeader);
  std::memcpy(&dataSize, (unsigned char *)IOHeader + 2, 4);
  if (4096 - this->_outBuffer.size() < dataSize)
    return false;
  std::cout << "writing to out buffer" << std::endl;
  std::cout << "data size: " << dataSize << std::endl;
  for (unsigned int i = 0; i < IOHEADER_SIZE; i++)
    {
      std::cout << "[" << buffer[i] << "]";
      this->_outBuffer.push_back(buffer[i]);
    }
  for (unsigned int i = 0; i < dataSize; i++)
    {
      std::cout << "[" << data[i] << "]";
      this->_outBuffer.push_back(data[i]);
    }
  std::cout << std::endl;
  std::cout << "wrote out buffer" << std::endl;
  std::cout << "out buffer size: " << _outBuffer.size() << std::endl;
  return true;
}
