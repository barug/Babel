//
// BoostConnexionAcceptor.hpp for Babel in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 23:28:20 2016 Josselin
// Last update Tue Nov  8 11:51:24 2016 master
//

#ifndef		__BOOSTCONNEXIONACCEPTOR__
# define	__BOOSTCONNEXIONACCEPTOR__

# include	<string>
# include	<boost/asio.hpp>

# include	"IConnexionAcceptor.hpp"

class BoostConnexionAcceptor : public IConnexionAcceptor
{

public:
  BoostConnexionAcceptor(const std::string &ip, const int &port);
  virtual ~BoostConnexionAcceptor();

  virtual BoostSocket			*acceptConnexion();
  int					getServerFd();

private:
  std::string				_ip;
  int					_port;
  boost::asio::io_service		_serverIos;
  boost::asio::ip::tcp::endpoint	_serverEndpoint;
  boost::asio::ip::tcp::acceptor	_serverAcceptor;

};

#endif		/* !__BOOSTCONNEXIONACCEPTOR_HPP__ */
