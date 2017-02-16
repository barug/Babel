//
// BabelServer.hpp for BABEL in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 19:12:23 2016 Josselin
// Last update Fri Nov 11 19:19:30 2016 Thomas Billot
//

#ifndef		__BABELSERVER_HPP__
# define	__BABELSERVER_HPP__

# include	<map>
# include	<string>

# include	"IDatabase.hpp"
# include	"IConnexionAcceptor.hpp"
# include	"SocketSelector.hpp"
# include	"CommandHandler.hpp"
# include	"Client.hpp"

# define	DEBUG 1

class		CommandHandler;

class		BabelServer
{

public:

  BabelServer(const std::string &ip, const int &port, const std::string &directoryPath = "./test/database/"); //default path to change
  ~BabelServer();

  IDatabase				*getDatabase();
  const std::map<std::string, Client*>	&getAuthentifiedClients() const;
  bool					getServerInput(Client *clientToHandle);
  int					run();
  bool					acceptClient();
  bool					removeClient(Client *clientToRemove);
  bool					addClient(Client *clientToAdd);
  bool					handleServerOutput(Client *client);
  bool					handleInput(Client *client);
  void					handleClientRequest(Client &clientToHandle);
  bool					isConnected(std::string name);
  Client*				getClientAuth(const std::string  &name);
  void					deleteClients();
  void					deleteRemainingClients();
  
private:

  std::map<std::string, Client*>	_authentifiedClients;
  IConnexionAcceptor			*_acceptor;
  SocketSelector			*_selector;
  IDatabase				*_database;
  CommandHandler			*_commandHandler;
};

#endif		/* !__BABELSERVER_HPP__ */
