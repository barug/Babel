//
// CommandHandler.cpp for Babel in /cpp_babel/src/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Nov  3 14:22:53 2016 Josselin
// Last update Sun Nov 13 23:12:18 2016 Thomas Billot
//

# include	<iostream>
# include	<sstream>
# include	<fstream>

# include	"Client.hpp"
# include	"Message.hpp"
# include	"CommandHandler.hpp"
# include	"BabelServer.hpp"
# include	"ICircularBuffer.hpp"

CommandHandler::CommandHandler() : _fptr{{"1", &CommandHandler::logInUser},
					 {"2", &CommandHandler::registerUser},
					 {"3", &CommandHandler::disconnectUser},
					 {"4", &CommandHandler::call},
					 {"5", &CommandHandler::getCallPort},
					 {"6", &CommandHandler::hangUp},
					 {"7", &CommandHandler::addContact},
					 {"8", &CommandHandler::getContactList},
					 {"9", &CommandHandler::removeContact},
					 {"501", &CommandHandler::callStarted},
 					 {"502", &CommandHandler::callEnded}}
{}

CommandHandler::~CommandHandler()
{}

bool				CommandHandler::sendResponse(short int op,
							     unsigned char *dataToSend,
							     int dataSize,
							     Client &client)
{
  ICircularBuffer::IOHeader	header;

  header.op = op;
  header.length = dataSize;
  client.getCircularBuffer()->writeOutBuffer(&header, dataToSend);
  client.setReadyToWrite(true);
  std::cout << "We send : " << header.op << " datalength:  " << header.length << std::endl;
  return true;
}

bool				CommandHandler::logInUser(BabelServer *server,
							  Client &clientToHandle,
							  Message *message)
{
  std::string			name;
  std::string			password;
  unsigned char *		data = message->getData();

  std::cout << "[+] CommandHandler::logInUser" << std::endl;
  if (message->getSize() == 256) {
    for (int i = 0; i < 128 && data[i]; i++)
      name += data[i];
    for (int i = 128; i < 256 && data[i]; i++)
      password += data[i];
  }
  else
    return false;
  clientToHandle.setName(name);
  auto it = server->getAuthentifiedClients().find(clientToHandle.getName());
  if (it != server->getAuthentifiedClients().end())
    {
      name = "";
      clientToHandle.setName(name);
      sendResponse(102, nullptr, 0, clientToHandle);
      return false;
    }
  if (!server->getDatabase()->loadUser(clientToHandle.getName(), &clientToHandle))
    {
      name = "";
      clientToHandle.setName(name);
      sendResponse(101, nullptr, 0, clientToHandle);
      return false;
    }
  if (password.compare(clientToHandle.getPassword()) != 0)
    {
      name = "";
      clientToHandle.setName(name);
      sendResponse(103, nullptr, 0, clientToHandle);
      return false;
    }
  server->addClient(&clientToHandle);
  sendResponse(201, nullptr, 0, clientToHandle);
  std::string msg = clientToHandle.getName();
  Client *contactFriend;
  for (auto it : clientToHandle.getContacts())
    if ((contactFriend = server->getClientAuth(it)) != nullptr)
      sendResponse(302, (unsigned char *)msg.c_str(), msg.size(), *contactFriend);
  this->getContactList(server, clientToHandle, NULL);
  return true;
}

bool				CommandHandler::registerUser(BabelServer *server,
							     Client &clientToHandle,
							     Message *message)
{
  std::string			name;
  std::string			password;
  unsigned char*		data = message->getData();

  std::cout << "[+] CommandHandler::registerUser" << std::endl;
  if (message->getSize() == 256)
    {
      for (int i = 0; i < 128 && data[i]; i++)
	name += data[i];
      for (int i = 128; i < 256 && data[i]; i++)
	password += data[i];
    }
  else
    return false;
  if (!server->getDatabase()->loadUser(name, &clientToHandle))
    {
      clientToHandle.setName(name);
      clientToHandle.setPassword(password);
      server->getDatabase()->saveUser(&clientToHandle);
      sendResponse(202, nullptr, 0, clientToHandle);
      server->addClient(&clientToHandle);
      this->sendResponse(201, nullptr, 0, clientToHandle);
      return this->getContactList(server, clientToHandle, NULL);
    }
  sendResponse(104, nullptr, 0, clientToHandle);
  return false;
}

bool			CommandHandler::disconnectUser(BabelServer *server,
						       Client &clientToHandle,
						       Message *)
{
  std::cout << "[+] CommandHandler::disconnectUser" << std::endl;
  sendResponse(203, nullptr, 0, clientToHandle);

  std::string userName = clientToHandle.getName();
  Client *contactFriend;
  for (auto it : clientToHandle.getContacts())
    if ((contactFriend = server->getClientAuth(it)) != nullptr)
      sendResponse(303, (unsigned char *) userName.c_str(), userName.size(), *contactFriend);
  clientToHandle.setToDelete(true);
  return true;
}

bool					CommandHandler::call(BabelServer *server,
							     Client &clientToHandle,
							     Message *message)
{
  std::cout << "[+] CommandHandler::call" << std::endl;
  try
    {
      std::map<std::string, Client *>	clients = server->getAuthentifiedClients();
      std::string			userToCall((char *)message->getData());


      if (!userToCall.empty())
	{
	  auto it = clients.find(userToCall);
	  if (it != clients.end())
	    {
	      Client *tmp = it->second;
	      if (tmp->isAvailable() == false)
		{
		  sendResponse(107, nullptr, 0, clientToHandle);
		  return (true);
		}
	      sendResponse(204, nullptr, 0, clientToHandle);
	      clientToHandle.setRequestToCall(true);
	      clientToHandle.setClientToCall(userToCall);
	    }
	  else
	    sendResponse(106, nullptr, 0, clientToHandle);
	}
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (false);
    }
  return (true);
}

bool						CommandHandler::getCallPort(BabelServer *server,
									    Client &clientToHandle,
									    Message *message)
{
  std::cout << "[+] CommandHandler::getCallPort" << std::endl;
  try
    {
      ICircularBuffer::IOHeader			header = {};
      ICircularBuffer::IOCallInformation	callInfo = {};
      Client *clientToCall =
	server->getAuthentifiedClients().find(clientToHandle.getClientToCall())->second;
      int					port = 0;
      std::string				portToCall((char *)message->getData());
      
      if (!portToCall.empty())
	{
	  port = std::stoi(portToCall);
	  std::string ip = clientToHandle.getSocket()->getIpAddress();	  
	  int i = -1;
	  for (auto it : clientToHandle.getName())
	    callInfo.username[++i] = it;
	  i = -1;
	  for (auto it : ip)
	    callInfo.ip[++i] = it;
	  callInfo.port = port;
	  header.op = 304;
	  header.length = sizeof(callInfo);
	  clientToCall->getCircularBuffer()->writeOutBuffer(&header, (unsigned char *)(&callInfo));
	  clientToCall->setClientToCall(clientToHandle.getName());
	  clientToCall->setReadyToWrite(true);
	}
      else
	return (false);
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (false);
    }
  return (true);
}

bool			CommandHandler::callStarted(BabelServer *server, Client &clientToHandle, Message *)
{
  std::cout << "[+] CommandHandler::callStarted" << std::endl;
  try
    {
      std::map<std::string, Client *>	clients = server->getAuthentifiedClients();
      Client				*clientToCall = clients.find(clientToHandle.getClientToCall())->second;
      ICircularBuffer::IOHeader		header;
      std::string			response("CallStarted");

      header.op = 205;
      header.length = response.size();
      unsigned char *tmp = (unsigned char *)response.c_str();
      clientToCall->getCircularBuffer()->writeOutBuffer(&header, tmp);
      clientToHandle.setAvailable(false);
      clientToCall->setAvailable(false);
      clientToCall->setReadyToWrite(true);
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (false);
    }
  return (true);
}

bool			CommandHandler::callEnded(BabelServer *server,
						  Client &clientToHandle,
						  Message *)
{
  std::cout << "[+] CommandHandler::callEnded" << std::endl;
  try
    {
      std::map<std::string, Client *>	clients = server->getAuthentifiedClients();
      Client				*clientToCall = clients.find(clientToHandle.getClientToCall())->second;
      ICircularBuffer::IOHeader		header;
      std::string			response("CallEnded");

      header.op = 305;
      header.length = response.size();
      unsigned char *tmp = (unsigned char *)response.c_str();
      clientToCall->getCircularBuffer()->writeOutBuffer(&header, tmp);
      clientToHandle.setAvailable(true);
      clientToCall->setAvailable(true);
      clientToCall->setReadyToWrite(true);
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (false);
    }
  return (true);
}

bool					CommandHandler::hangUp(BabelServer *server,
							       Client &clientToHandle,
							       Message *messageToHandle)
{
  std::cout << "[+] CommandHandler::hangUp" << std::endl;
  try
    {
      std::map<std::string, Client *>	clients = server->getAuthentifiedClients();
      Client				*clientToCall = clients.find(clientToHandle.getClientToCall())->second;
      std::string			m((char *)messageToHandle->getData());
      std::string			hangUp("HangUp");
      int				ret = std::strncmp(m.c_str(), hangUp.c_str(), hangUp.size());
      ICircularBuffer::IOHeader		header;
      std::string			response("CallStoped");

      if (ret == 0)
	{
	  header.op = 206;
	  header.length = response.size();
	  unsigned char *tmp = (unsigned char *)response.c_str();
	  clientToHandle.getCircularBuffer()->writeOutBuffer(&header, tmp);
	  clientToCall->getCircularBuffer()->writeOutBuffer(&header, tmp);
	  clientToHandle.setAvailable(true);
	  clientToHandle.setReadyToWrite(true);
	  clientToCall->setAvailable(true);
	  clientToCall->setReadyToWrite(true);
	}
      else
	return (false);
      return (true);
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (false);
    }
  return (true);
}

bool		CommandHandler::addContact(BabelServer *server,
					   Client &clientToHandle,
					   Message *stuff)
{
  std::cout << "[+] CommandHandler::addContact" << std::endl;
  std::string	check = server->getDatabase()->getDirectoryPath();
  std::string	name((char *)stuff->getData());
  std::ifstream	file(check + name + ".babel");
  Client *contactClient;

  if (file.good()
      && (clientToHandle.hasContact(name) == false)
      && (clientToHandle.getName() != name))
    {
      std::string adderName = clientToHandle.getName();
      if ((contactClient = server->getClientAuth(name)) != nullptr)
	{
	  contactClient->addContact(adderName);
	  this->sendResponse(207, nullptr, 0, *contactClient);
	  this->getContactList(server, *contactClient, nullptr);	  
	}
      else
	{
	  contactClient = new Client(nullptr);
	  server->getDatabase()->loadUser(name, contactClient);
	  contactClient->setName(name);
	  contactClient->addContact(adderName);
	  server->getDatabase()->saveUser(contactClient);
	  delete (contactClient);
	}
      clientToHandle.addContact(name);
      this->sendResponse(207, nullptr, 0, clientToHandle);
      this->getContactList(server, clientToHandle, nullptr);
      return true;
    }
  this->sendResponse(108, nullptr, 0, clientToHandle);
  return false;
}

bool					CommandHandler::getContactList(BabelServer *server,
								       Client &clientToHandle,
								       Message *)
{
  std::cout << "[+] CommandHandler::getContactList" << std::endl;
  ICircularBuffer::IOContactList	answer = {};
  std::vector<ICircularBuffer::IOContact>		contacts;
  std::stringstream			 binaryStream;
  
  answer.nb = 0;
  for (auto contactName : clientToHandle.getContacts())
    {
      int				i = -1;
      ICircularBuffer::IOContact	contact = {};

      for ( auto car : contactName)
      	contact.name[++i] = car;
      contact.isConnected = server->isConnected(contactName);
      contacts.push_back(contact);
      answer.nb++;
    }
  binaryStream.write((char *) &answer, sizeof(answer));
  for (auto contact: contacts)
      binaryStream.write((char *) &contact, sizeof(contact));
  sendResponse(301,
	       (unsigned char *)(binaryStream.str().c_str()),
	       binaryStream.str().size(),
	       clientToHandle);
  return (true);
}

bool			CommandHandler::removeContact(BabelServer *server,
						      Client &clientToHandle,
						      Message *stuff)
{
  std::cout << "[+] CommandHandler::removeContact" << std::endl;
  std::string		check = server->getDatabase()->getDirectoryPath();
  std::string		name((char *)stuff->getData());
  std::ifstream		file(check + name + ".babel");

  if (file.good())
    {
      this->sendResponse(108, nullptr, 0, clientToHandle);
      return false;
    }
  else if (!clientToHandle.hasContact(name))
    {
      this->sendResponse(109, nullptr, 0, clientToHandle);
      return false;
    }
  this->sendResponse(109, nullptr, 0, clientToHandle);
  return clientToHandle.removeContact(name);
}

bool				CommandHandler::handleClientMessage(BabelServer *server,
								    Client &clientToHandle,
								    Message *messageToHandle)
{
  std::stringstream		ss;
  std::string			s;

  ss << messageToHandle->getOperationCode();
  s = ss.str();
  ss.clear();
  std::cout << "_______" << std::endl;
  std::cout << "size = \t\t" << messageToHandle->getSize() << std::endl;
  std::cout << "opcode = \t" << messageToHandle->getOperationCode() << std::endl;
  std::cout << "_______" << std::endl;
  auto it = _fptr.find(s);
  if ( it != _fptr.end() &&
       messageToHandle->getOperationCode() != 1 &&
       messageToHandle->getOperationCode() != 2 &&
       clientToHandle.getName().empty() )
    sendResponse(105, nullptr, 0, clientToHandle);
  if  (it != _fptr.end())
    return (appelDeFonctionMembre(*this, it->second)(server, clientToHandle, messageToHandle));
  return (false);
}
