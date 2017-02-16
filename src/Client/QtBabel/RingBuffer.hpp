#ifndef B_RING_BUFFER
# define B_RING_BUFFER

# define B_BUFFER_SIZE  (20 * 4096)
#define FRAMES_PER_BUFFER (512)

#include <vector>
#include <mutex>

class RingBuffer
{
  float			_buffer[B_BUFFER_SIZE];
  unsigned int		_readIndex;
  unsigned int		_writeIndex;
  unsigned int		_availableData;
  std::mutex		_readIndexMutex;
  std::mutex		_writeIndexMutex;
  
 public:
  RingBuffer();
  ~RingBuffer();

  void			writeBuffer(float *data, unsigned int dataSize);
  std::vector<float>	readBuffer();
};

#endif // B_RING_BUFFER
