//
// CommandHandler.hpp for Babel in /cpp_babel/src/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Nov  3 14:22:50 2016 Josselin
// Last update Sun Nov 13 22:41:47 2016 Thomas Billot
//

#ifndef		__COMMANDHANDLER_HPP__
# define	__COMMANDHANDLER_HPP__

# include	<map>

# include	"BabelServer.hpp"

# define	appelDeFonctionMembre(instance, ptr) ((instance).*(ptr))

class		BabelServer;

class		CommandHandler
{

public:
  
  CommandHandler();
  ~CommandHandler();

  typedef bool			(CommandHandler::* f)(BabelServer *, Client &, Message*);
  
  bool				handleClientMessage(BabelServer *, Client &, Message *);
  bool				logInUser(BabelServer *, Client &, Message *);
  bool				registerUser(BabelServer *, Client &, Message *);
  bool				disconnectUser(BabelServer *,Client &, Message *);
  bool				call(BabelServer *,Client &, Message *);
  bool				getCallPort(BabelServer *, Client &, Message *);
  bool				callStarted(BabelServer *, Client &, Message *);
  bool				callEnded(BabelServer *, Client &, Message *);
  bool				hangUp(BabelServer *, Client &, Message *);
  bool				addContact(BabelServer *, Client &, Message *);
  bool				getContactList(BabelServer *, Client &, Message *);
  bool				removeContact(BabelServer *, Client &, Message *);
  
  bool				sendResponse(short int op,
					     unsigned char * dataToSend,
					     int dataSize,
					     Client &client);
  
private:

  std::map<std::string, f>	_fptr;
};

#endif /* __COMMANDHANDLER_HPP__ */
