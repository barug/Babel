//
// ICircularBuffer.hpp for Babel in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 20:25:08 2016 Josselin
// Last update Sun Nov 13 22:39:17 2016 Thomas Billot
//

#ifndef		__ICIRCULARBUFFER_HPP__
# define	__ICIRCULARBUFFER_HPP__

# include	<vector>

# include	"Message.hpp"


class		ICircularBuffer
{

public:
  
  virtual ~ICircularBuffer()		{}
  virtual Message*			readInBuffer() = 0;
  virtual bool				writeInBuffer(unsigned char * data, unsigned int size) = 0;
  virtual std::vector<unsigned char>*	readOutBuffer() = 0;
  virtual bool				writeOutBuffer(void * IOHeader, unsigned char * data) = 0;

public:
  
#pragma pack(push, 1)
  typedef struct		s_IOHeader
  {
    short int			op;
    int				length;
  }				IOHeader;

  typedef struct		s_Contact
  {
    char			name[128];
    bool			isConnected;
  }				IOContact;

  typedef struct		s_IOContactList
  {
    int				nb;
    IOContact			client[];
  }				IOContactList;

  typedef struct		s_IOCallInformation
  {
    char			username[128];
    char			ip[15];
    int				port;
  }				IOCallInformation;
#pragma pack(pop)
};

#endif		/* !__ICIRCULARBUFFER_HPP__ */
