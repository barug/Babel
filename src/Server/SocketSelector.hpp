//
// SocketSelector.hpp for Babel in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 20:50:36 2016 Josselin
// Last update Mon Nov  7 21:20:44 2016 master
//

#ifndef		__SOCKETSELECTOR_HPP__
# define	__SOCKETSELECTOR_HPP__

# include	<sys/time.h>
# include	<sys/types.h>
# include	<unistd.h>

# include	<map>
# include	<list>

# include	"Client.hpp"

class		SocketSelector
{
public:
  SocketSelector(int fdZero);
  ~SocketSelector();

  typedef struct		s_clients
  {
    std::list<Client*>		writeReady;
    std::list<Client*>		readReady;
    bool			pendingConnection;
    bool			keyboard;
  }				IOReadyClients;

  void				addClient(Client *Client);
  void				removeClient(Client *Client);

  IOReadyClients		getIOReadyClients();

private:

  std::map<int, Client*>	_connectedClients;
  struct timeval		_tv;
  fd_set			_writeFd;
  fd_set			_readFd;
  int				_maxFd;
  int				_fdZero;

  void				setFds();
  IOReadyClients		checkFds();
};

#endif		/* !__SOCKETSELECTOR_HPP__ */
