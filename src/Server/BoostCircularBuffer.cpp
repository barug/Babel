//
// BoostCircularBuffer.cpp for Babel in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 20:32:40 2016 Josselin
// Last update Fri Nov 11 19:32:52 2016 Thomas Billot
//

#include "BoostCircularBuffer.hpp"
#include <iostream>
#include <cstring>

BoostCircularBuffer::BoostCircularBuffer(unsigned int readBufferSize, unsigned int writeBufferSize) : _inBuffer(),
												      _outBuffer()
{
  this->_inBuffer = boost::circular_buffer<unsigned char>(readBufferSize);
  this->_outBuffer = boost::circular_buffer<unsigned char>(writeBufferSize);
}

BoostCircularBuffer::~BoostCircularBuffer()	{}

Message				*BoostCircularBuffer::readInBuffer()
{
  std::vector<unsigned char>	*buffer = new std::vector<unsigned char>;
  unsigned int			dataLength = 0;
  unsigned  int			i = 0;
   
  if (buffer == NULL ||
      (this->_inBuffer.size() < IOHEADER_SIZE))
    return NULL;

  unsigned char size[4] = {_inBuffer[2],
			   _inBuffer[3],
			   _inBuffer[4],
			   _inBuffer[5]};
  std::memcpy(&dataLength, size, 4);
  if (dataLength + IOHEADER_SIZE > this->_inBuffer.size())
    return NULL;
  while (i < dataLength + IOHEADER_SIZE)
    {
      buffer->push_back(this->_inBuffer.front());
      this->_inBuffer.pop_front();
      i++;
    }
  return (new Message(buffer));
}

bool		BoostCircularBuffer::writeInBuffer(unsigned char *data, unsigned int size)
{
  if (!data || !size ||
      this->_inBuffer.capacity() - this->_inBuffer.size() < size)
    return false;
  for (unsigned int i = 0; i < size; i++)
    this->_inBuffer.push_back((unsigned char)data[i]);
  return true;
}

std::vector<unsigned char>	*BoostCircularBuffer::readOutBuffer()
{
  std::vector<unsigned char>	*buffer = new std::vector<unsigned char>;
  unsigned int			dataLength = 0;
  unsigned int			i = 0;
  
  if (buffer == NULL ||
      this->_outBuffer.size() < IOHEADER_SIZE)
    return NULL;
  unsigned char size[4] = {_outBuffer[2],
			   _outBuffer[3],
			   _outBuffer[4],
			   _outBuffer[5]};
  std::memcpy(&dataLength, size, 4);
  if (dataLength + IOHEADER_SIZE > this->_outBuffer.size())
    return NULL;
  while (i < dataLength + IOHEADER_SIZE)
    {
      buffer->push_back(this->_outBuffer.front());
      this->_outBuffer.pop_front();
      i++;
    }
  return buffer;
}

bool		BoostCircularBuffer::writeOutBuffer(void *IOHeader, unsigned char *data)
{
  unsigned char	*buffer;
  unsigned int	dataSize = 0;

  if (IOHeader == NULL)
    return false;
  buffer = (unsigned char*)(IOHeader);
  std::memcpy(&dataSize, (unsigned char *)IOHeader + 2, 4);
  if (this->_outBuffer.capacity() - this->_outBuffer.size() < dataSize)
    return false;
  for (unsigned int i = 0; i < IOHEADER_SIZE; i++)
    this->_outBuffer.push_back(buffer[i]);
  for (unsigned int i = 0; i < dataSize; i++)
    this->_outBuffer.push_back(data[i]);
  return true;
}
