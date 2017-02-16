//
// ISocket.hpp for Babel in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 20:35:06 2016 Josselin
// Last update Sun Nov 13 22:39:45 2016 Thomas Billot
//

#ifndef		__ISOCKET_HPP__
# define	__ISOCKET_HPP__

# include	<vector>

class		ISocket
{

public:
  
  virtual ~ISocket() {}

  virtual bool		readSocket(std::vector<unsigned char> &destBuffer) const = 0;
  virtual bool		writeSocket(const std::vector<unsigned char> &srcBuffer) const = 0;

  virtual std::string	getIpAddress(void) const = 0;
  virtual int		getPort(void) const = 0;
  virtual int		getFd() const = 0;
};

#endif		/* !__ISOCKET_HPP__ */
