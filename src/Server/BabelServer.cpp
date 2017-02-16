//
// BabelServer.hpp for BABEL in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 19:12:23 2016 Josselin
// Last update Sun Nov 13 23:14:44 2016 Thomas Billot
//

# include	<iostream>
# include	<algorithm>
# include	<map>
# include	<unistd.h>

# include	"BoostConnexionAcceptor.hpp"
# include	"BoostSerializer.hpp"
# include	"BabelServer.hpp"
# include	"SocketSelector.hpp"
# include	"CommandHandler.hpp"

BabelServer::BabelServer(const std::string &ip, const int &port, const std::string &directoryPath) :
  _authentifiedClients(),
  _acceptor(new BoostConnexionAcceptor(ip, port)),
  _selector(new SocketSelector(_acceptor->getServerFd())),
  _database(new BoostSerializer(directoryPath)),
  _commandHandler(new CommandHandler())
{}

BabelServer::~BabelServer()
{
  delete _database;
  delete _acceptor;
  delete _selector;
  delete _commandHandler;
}

bool					BabelServer::handleServerOutput(Client *clientToWrite)
{
  const ISocket				*socketClient;
  std::vector<unsigned char>		*srcBuffer;

  socketClient = clientToWrite->getSocket();
  srcBuffer = clientToWrite->getCircularBuffer()->readOutBuffer();
  while (srcBuffer && !srcBuffer->empty())
    {
      socketClient->writeSocket(*srcBuffer);
      delete (srcBuffer);
      srcBuffer = clientToWrite->getCircularBuffer()->readOutBuffer();
    }
  delete (srcBuffer);
  return (false);
}

int					BabelServer::run()
{
  SocketSelector::IOReadyClients	transmission;
  bool					run = true;
  char					buff[10];

  while (run)
    {
      transmission = _selector->getIOReadyClients();

      if (transmission.pendingConnection && !this->acceptClient())
	run = false;
      else if (transmission.keyboard)
	{
	  bzero(buff, 10);
	  read(STDIN_FILENO, buff, 10);
	  std::string			input(buff);
	  if (input == "quit\n")
	    run = false;
	}

      else if (!transmission.readReady.empty())
	{
	  for (auto it : transmission.readReady)
	    if (this->getServerInput(it) == false)
	      it->setToDelete(true);
	    else
	      handleClientRequest(*it);
	}
      for (auto it : _authentifiedClients)
	{
	  Client	*clientToWrite = it.second;
	  
	  if ( clientToWrite->getReadyToWrite() 
	       && ((std::find(transmission.writeReady.begin(),
			      transmission.writeReady.end(),
			      clientToWrite))
		   != transmission.writeReady.end()) )
	    {
	      handleServerOutput(clientToWrite);
	      clientToWrite->setReadyToWrite(false);
	    }
	  else if (clientToWrite->getReadyToWrite() == true)
	    clientToWrite->setToDelete(true);
	}
      deleteClients();
    }
  deleteRemainingClients();
  std::cout << "Goodbye" << std::endl;
  return (0);
}

bool					BabelServer::getServerInput(Client *client)
{
  const ISocket				*socketClient;
  std::vector<unsigned char>		*destBuffer = new std::vector<unsigned char>;

  socketClient = client->getSocket();
  if (socketClient->readSocket(*destBuffer) == false)
    {
      delete (destBuffer);
      return (false);
    }
  if (destBuffer->size() != 0)
    {
      if (client->getCircularBuffer()->writeInBuffer(destBuffer->data(), destBuffer->size()) == false)
	std::cout << "Error in WriteInBuffer" << std::endl;
    }
  delete (destBuffer);
  return (true);
}

void					BabelServer::handleClientRequest(Client &clientToHandle)
{
  Message				*clientMessage;

  if ((clientMessage = clientToHandle.getCircularBuffer()->readInBuffer()) != NULL)
    {
      _commandHandler->handleClientMessage(this, clientToHandle, clientMessage);
      delete(clientMessage);
    }
}

const std::map<std::string, Client*>	&BabelServer::getAuthentifiedClients() const
{
  return this->_authentifiedClients;
}

bool					BabelServer::acceptClient()
{
  ISocket				*socketClient;

  if ((socketClient = _acceptor->acceptConnexion()) == NULL)
    return (false);
  Client	*newClient = new Client(socketClient);
  this->addClient(newClient);
  _selector->addClient(newClient);
  return (true);
}

void					BabelServer::deleteClients()
{
  std::vector<Client*>			clientsToDelete;
  Client				*tmp;
  
  for (auto it : _authentifiedClients)
    {
      tmp = it.second;
      if (tmp->getToDelete() == true)
	{
	  _selector->removeClient(tmp);
	  clientsToDelete.push_back(tmp);
	  
	  if (tmp->getName() != "")
	    {
	      Client *contactFriend;
	      std::string	userName = tmp->getName();
	      for (auto it : tmp->getContacts())
		if ((contactFriend = this->getClientAuth(it)) != nullptr)
		  _commandHandler->sendResponse(303, (unsigned char *) userName.c_str(), userName.size(), *contactFriend);
	      _database->saveUser(tmp);
	    }
	}
    }
  for (auto it : clientsToDelete)
    {
      auto name = _authentifiedClients.find(it->getName());
      _authentifiedClients.erase(name);
      delete (it);
    }
}

void					BabelServer::deleteRemainingClients()
{
  for (auto it : _authentifiedClients)
    delete (it.second);
}

bool	BabelServer::removeClient(Client *clientToRemove)
{
  std::vector<Client *>		deleteVector;
  
  if (clientToRemove)
    {
      _selector->removeClient(clientToRemove);
      auto	it = _authentifiedClients.find(clientToRemove->getName());
      if (it != _authentifiedClients.end())
	_authentifiedClients.erase(it);
      return true;
    }
  return false;
}

bool		BabelServer::isConnected(std::string name)
{
  auto		it = _authentifiedClients.find(name);

  return (name.empty() || it == _authentifiedClients.end() ) ? false : true;
}

bool	BabelServer::addClient(Client *clientToAdd)
{
  if (clientToAdd->getName() == "")
    {
      _authentifiedClients.emplace("", clientToAdd);
      return true;
    }
  else
    {
      for ( const std::map<std::string, Client*>::iterator it = _authentifiedClients.begin();
	    it != _authentifiedClients.end();)
	if (it->second == clientToAdd)
	  {
	    _authentifiedClients.emplace(clientToAdd->getName(), clientToAdd);
	    _authentifiedClients.erase(it);
	    return true;
	  }
    }
  return false;
}

IDatabase*	BabelServer::getDatabase()
{
  return _database;
}

Client*		BabelServer::getClientAuth(const std::string  &name)
{
  auto it = _authentifiedClients.find(name);

  if (it == _authentifiedClients.end())
    return nullptr;
  return it->second;
}
