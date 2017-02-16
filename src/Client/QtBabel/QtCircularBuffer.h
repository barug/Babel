#include <cassert>
#include <deque>
#include "ICircularBuffer.hpp"

#define READ_BUFF_SIZE	4096
#define WRITE_BUFF_SIZE	4096
#define IOHEADER_SIZE	6

class QtCircularBuffer : public ICircularBuffer
{

public:
  QtCircularBuffer();
  virtual ~QtCircularBuffer();

  Message *                         readInBuffer();
  bool                              writeInBuffer(unsigned char * data, unsigned int size);
  std::vector<unsigned char>*       readOutBuffer();
  bool                              writeOutBuffer(void * IOHeader, unsigned char * data);

private:
  std::deque<unsigned char>	_inBuffer;
  std::deque<unsigned char>	_outBuffer;


};
