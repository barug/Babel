//
// BoostCircularBuffer.hpp for Babel in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 20:32:29 2016 Josselin
// Last update Sun Nov 13 22:31:53 2016 Thomas Billot
//

#ifndef		__BOOSTCIRCULARBUFFER_HPP__
# define	__BOOSTCIRCULARBUFFER_HPP__

# include	<boost/circular_buffer.hpp>

# include	"ICircularBuffer.hpp"
# include	"Message.hpp"


# define	READ_BUFF_SIZE	(4096)
# define	WRITE_BUFF_SIZE	(4096)
# define	IOHEADER_SIZE	(6)

class BoostCircularBuffer : public ICircularBuffer
{

public:
  BoostCircularBuffer(unsigned int readBufferSize = READ_BUFF_SIZE,
		      unsigned int writeBufferSize = WRITE_BUFF_SIZE);
  virtual ~BoostCircularBuffer();

  virtual Message*				readInBuffer();
  virtual bool					writeInBuffer(unsigned char *data, unsigned int size);
  virtual std::vector<unsigned char>*		readOutBuffer();
  virtual bool					writeOutBuffer(void *IOHeader, unsigned char *data);
 
private:
  boost::circular_buffer<unsigned char>		_inBuffer;
  boost::circular_buffer<unsigned char>		_outBuffer;

};

#endif		/* __BOOSTCIRCULARBUFFER_HPP__ */
