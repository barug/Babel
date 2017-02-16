//
// Client.hpp for Babel in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 20:09:54 2016 Josselin
// Last update Sun Nov 13 22:08:46 2016 Thomas Billot
//

# include	<algorithm>
# include	<vector>

# include	"Client.hpp"
# include	"BoostCircularBuffer.hpp"
# include	"BoostSocket.hpp"

Client::Client(ISocket *socket)
  : _socket(socket),
    _circularBuffer(new BoostCircularBuffer),
    _name(),
    _password(),
    _contacts(),
    _readyToWrite(false),
    _isAvailable(true),
    _requestToCall(false),
    _clientToCall(),
    _toDelete(false)
{}

Client::~Client()
{
  delete _socket;
  delete _circularBuffer;
}

void				Client::setPassword(const std::string &password)
{
  _password = password;
}

void			        Client::setContacts(const std::vector<std::string> &contacts)
{
  _contacts = contacts;
}

void				Client::setName(std::string &name)
{
  _name = name;
}

void				Client::setAvailable(bool isAvailable)
{
  _isAvailable = isAvailable;
}

void				Client::setRequestToCall(bool isRequestingToCall)
{
  _requestToCall = isRequestingToCall;
}

void				Client::setClientToCall(const std::string &name)
{
  _clientToCall = name;
}

void				Client::setToDelete(bool state)
{
  _toDelete = state;
}

ICircularBuffer			*Client::getCircularBuffer() const
{
  return _circularBuffer;
}

const std::string		Client::getPassword() const
{
  return _password;
}

const std::vector<std::string>	Client::getContacts() const
{
  return _contacts;
}

const ISocket			*Client::getSocket() const
{
  return _socket;
}

const std::string		Client::getName() const
{
  return _name;
}

bool				Client::isAvailable() const
{
  return _isAvailable;
}

bool				Client::getRequestToCall() const
{
  return _requestToCall;
}

const std::string		&Client::getClientToCall() const
{
  return _clientToCall;
}

bool				Client::getToDelete() const
{
  return _toDelete;
}

bool				Client::addContact(std::string &name)
{
  _contacts.push_back(name);
  return true;
}

bool				Client::removeContact(std::string &name)
{
  auto				it = find(_contacts.begin(), _contacts.end(), name);

  if (it != _contacts.end())
      _contacts.erase(it);
  return true;
}

bool				Client::hasContact(std::string &name)
{
  auto				it = find(_contacts.begin(), _contacts.end(), name);

  return it == _contacts.end() ? false : true;
}

void				Client::setReadyToWrite(bool state)
{
  _readyToWrite = state;
}

bool				Client::getReadyToWrite()
{
  return _readyToWrite;
}
