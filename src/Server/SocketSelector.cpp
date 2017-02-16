//
// SocketSelector.cpp for Babel in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 20:50:48 2016 Josselin
// Last update Mon Nov  7 21:17:46 2016 master
//

# include	<sys/time.h>
# include	<sys/types.h>
# include	<unistd.h>
# include	<map>

  #include <iostream>

# include	"SocketSelector.hpp"

SocketSelector::SocketSelector(int fdZero) :
  _fdZero(fdZero)
{
  _tv.tv_usec = 0;
  _tv.tv_sec = 5;
}

SocketSelector::~SocketSelector()
{}

void	SocketSelector::addClient(Client *Client)
{
  int	fd = Client->getSocket()->getFd();
  auto	it = _connectedClients.find(fd);

  if (it == _connectedClients.end())
    _connectedClients.emplace(fd, Client);
}

void	SocketSelector::removeClient(Client *Client)
{
  auto	it = _connectedClients.find(Client->getSocket()->getFd());

  if (it != _connectedClients.end())
    _connectedClients.erase(it);
}

void		SocketSelector::setFds()
{
  FD_ZERO(&_writeFd);
  FD_ZERO(&_readFd);

  FD_SET(_fdZero, &_readFd);
  FD_SET(STDIN_FILENO, &_readFd);

  _maxFd = _fdZero > STDIN_FILENO ? _fdZero : STDIN_FILENO;

  for (auto it : _connectedClients)
    {
      if (it.first > _maxFd)
	_maxFd = it.first;
      FD_SET(it.first, &_readFd);
      FD_SET(it.first, &_writeFd);
    }
  if (!_tv.tv_usec)
    _tv.tv_sec = 5;
}

SocketSelector::IOReadyClients		SocketSelector::checkFds()
{
  SocketSelector::IOReadyClients	transmission;

  transmission.keyboard = transmission.pendingConnection = false;
  if (FD_ISSET(_fdZero, &_readFd))
    transmission.pendingConnection = true;
  if (FD_ISSET(STDIN_FILENO, &_readFd))
    transmission.keyboard = true;

  for (auto it : _connectedClients) //foreach mamen
    {
      if (FD_ISSET(it.first, &_readFd))
	transmission.readReady.push_back(it.second);
      if (FD_ISSET(it.first, &_writeFd))
	transmission.writeReady.push_back(it.second);
    }
  return transmission;
}

SocketSelector::IOReadyClients	SocketSelector::getIOReadyClients()
{
  this->setFds();
  if (select(_maxFd + 1, &_readFd,
	     &_writeFd, NULL, &_tv) == -1 )
    { /* maybe some clean of code there */ }
  return this->checkFds();
}
