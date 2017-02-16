//
// BoostSocket.hpp for Babel in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 20:45:50 2016 Josselin
// Last update Tue Nov  8 12:08:22 2016 master
//

#ifndef		__BOOSTSOCKET_HPP__
# define	__BOOSTSOCKET_HPP__

# include	"ISocket.hpp"
# include	<boost/asio.hpp>

class		BoostSocket : public ISocket
{

public :

  BoostSocket(boost::asio::io_service &ios);
  virtual ~BoostSocket();
  virtual bool						readSocket(std::vector<unsigned char> &destBuffer) const;
  virtual bool						writeSocket(const std::vector<unsigned char> &srcBuffer) const;

  boost::asio::ip::tcp::socket				&getBoostSocket() const;
  std::string						getIpAddress() const;
  int							getPort() const;
  int							getFd() const;

private :

  boost::shared_ptr<boost::asio::ip::tcp::socket>	_socket;
};

#endif		/* !__BOOSTSOCKET_HPP__ */
