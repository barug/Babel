//
// Client.hpp for Babel in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 20:09:54 2016 Josselin
// Last update Sun Nov 13 22:09:43 2016 Thomas Billot
//

#ifndef		__CLIENT_HPP__
# define	__CLIENT_HPP__

# include	<string>
# include	<vector>
# include	<boost/archive/text_oarchive.hpp>
# include	<boost/archive/text_iarchive.hpp>
# include	<boost/serialization/vector.hpp>
# include	<boost/serialization/access.hpp>

# include	"ICircularBuffer.hpp"
# include	"ISocket.hpp"

class		Client
{

public:
  Client(ISocket *socket);
  ~Client();

  const ISocket				*getSocket() const;
  const std::string			getName() const;
  const std::string			getPassword() const;
  const std::vector<std::string>	getContacts() const;
  bool					isAvailable() const;
  bool					getRequestToCall() const;
  const std::string			&getClientToCall() const;
  bool					getToDelete() const;
  ICircularBuffer			*getCircularBuffer() const;

  void					setName(std::string &name);
  void					setPassword(const std::string &password);
  void					setContacts(const std::vector<std::string> &contacts);
  bool					hasContact(std::string &name);
  bool					getReadyToWrite();
  void					setReadyToWrite(bool state);
  void					setAvailable(bool isAvailable);
  void					setRequestToCall(bool isRequestingToCall);
  void					setClientToCall(const std::string &name);
  bool					addContact(std::string &name);
  bool					removeContact(std::string &name);
  void					setToDelete(bool state);

private:
  
  ISocket				*_socket;
  ICircularBuffer			*_circularBuffer;
  std::string				_name;
  std::string				_password;//?pour la serialization et le check
  std::vector<std::string>		_contacts;
  bool					_readyToWrite;
  bool					_isAvailable;
  bool					_requestToCall;
  std::string				_clientToCall;
  bool					_toDelete;
};

#endif		/* !__CLIENT_HPP__ */
