//
// BoostConnexionAcceptor.cpp for Babel in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 23:28:07 2016 Josselin
// Last update Tue Nov  8 11:52:52 2016 master
//


#include	<boost/asio.hpp>
#include	<iostream>

#include	"BoostConnexionAcceptor.hpp"

BoostConnexionAcceptor::BoostConnexionAcceptor(const std::string &ip, const int &port) :
  _ip(ip),
  _port(port),
  _serverIos(),
  _serverEndpoint(boost::asio::ip::address::from_string(_ip), _port),
  _serverAcceptor(_serverIos, _serverEndpoint)
{}

BoostConnexionAcceptor::~BoostConnexionAcceptor()
{}

BoostSocket			*BoostConnexionAcceptor::acceptConnexion()
{
  boost::system::error_code	ec;
  BoostSocket			*socket = new BoostSocket(_serverIos);

  if (_serverAcceptor.accept(socket->getBoostSocket(), ec) != boost::system::errc::errc_t::success)
    {
      delete (socket);
      return (NULL);
    }
  return (socket);
}

int		BoostConnexionAcceptor::getServerFd()
{
  return _serverAcceptor.native();
}
