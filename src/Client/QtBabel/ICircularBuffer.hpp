#ifndef __ICIRCULARBUFFER_HPP__
# define __ICIRCULARBUFFER_HPP__

# include "Message.h"
# include <vector>

class ICircularBuffer
{

public:
  virtual ~ICircularBuffer()		{}
  virtual Message*			readInBuffer() = 0;
  virtual bool				writeInBuffer(unsigned char * data, unsigned int size) = 0;
  virtual std::vector<unsigned char>*	readOutBuffer() = 0;
  virtual bool				writeOutBuffer(void * IOHeader, unsigned char * data) = 0;
};

#endif /* !__ICIRCULARBUFFER_HPP__ */
