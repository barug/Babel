#include "BabelClient.h"
#include "QtGui.h"
#include "QtNet.h"

BabelClient::BabelClient(int& ac, char *av[])
  : _isRunning(false),
    _isConnected(false),
    _gui(new QtGui(ac, av)),
    _network(new QtNet(0)),
    _voiceInterpreter(new VoiceInterpreter(new QtUdpSocket)),
    _contacts(),
    _eventsHandlers{{Event::CLIENT_CONNECTION, &BabelClient::_handleConnection},
		    {Event::CLIENT_REGISTER, &BabelClient::_handleRegister},
		    {Event::CLIENT_AUTHENTIFICATION, &BabelClient::_handleAuthentification},
		    {Event::CLIENT_LOGOUT, &BabelClient::_handleLogOut},
		    {Event::CLIENT_CALL, &BabelClient::_handleCall},
		    {Event::CLIENT_HANGUP, &BabelClient::_handleHangUp},
		    {Event::CLIENT_ADD_CONTACT, &BabelClient::_handleAddContact},
		    {Event::SERVER_CONTACT_NOT_CONNECTED, &BabelClient::_ignoreEvent},
		    {Event::SERVER_CONTACT_IN_CONVERSATION, &BabelClient::_ignoreEvent},
		    {Event::SERVER_CONTACT_DOESNT_EXIST, &BabelClient::_ignoreEvent},
		    {Event::SERVER_REGISTERED, &BabelClient::_ignoreEvent},
		    {Event::SERVER_AUTHENTIFIED, &BabelClient::_handleAuthentified},
		    {Event::SERVER_BAD_PASS, &BabelClient::_handleWrongPassword},
		    {Event::SERVER_LOGGED_OUT, &BabelClient::_handleLoggedOut},
		    {Event::SERVER_USER_ALREADY_EXIST, &BabelClient::_handleAlreadyExist},
		    {Event::SERVER_USER_ALREADY_LOGGED, &BabelClient::_handleAlreadyOn},
		    {Event::SERVER_USER_AVAILABLE, &BabelClient::_handleUserAvailable},
		    {Event::SERVER_USER_ADDED, &BabelClient::_handleUserAdded},
		    {Event::SERVER_USER_DOESNT_EXIST, &BabelClient::_handleUserDoesntExist},
		    {Event::SERVER_CONTACT_LIST, &BabelClient::_handleContactList},
		    {Event::SERVER_CONTACT_LOGGED_IN, &BabelClient::_handleContactLoggedIn},
		    {Event::SERVER_CONTACT_LOGGED_OUT, &BabelClient::_handleContactLoggedOut},
		    {Event::SERVER_INCOMING_CALL, &BabelClient::_handleIncomingCall}}
{
  if (ac > 2)
    {
      std::string	ip = av[1];
      int		port;

      try {
	port = std::stoi(std::string(av[2]));
      }
      catch (std::invalid_argument const &e) {
	std::cerr << "wrong port" << std::endl;
      }
      if (_network->connect(ip, port))
	{
	  _isConnected = true;
	  std::cout << "connected to host at ip: " << ip << " port: " << port << std::endl;
	  _gui->setGuiState(IGui::CONNECTED);
	}
    }
}

void				BabelClient::start()
{
  _isRunning = true;
  std::list<Event *>		*events = nullptr;
  std::list<Event *>		*netEvents = nullptr;

  while (_isRunning)// && !_gui->windowNotActivate())
    {
      events = _gui->getGuiEvents();
      if (_isConnected)
      	{
      	  netEvents = _network->getNetworkEvents();
      	  events->splice(events->end(), *netEvents);
      	}
      _handleEvents(events);
      if (netEvents != nullptr)
      	{
      	  delete netEvents;
      	  netEvents = nullptr;
      	}
      delete events;
      if (_isConnected)
       	_network->sendMessages();
    }
}

void				BabelClient::_handleEvents(std::list<Event *> *events)
{
  for (Event *event: *events)
    {
      std::cout << "handling event: " << event->getType() << std::endl;
      try
	{
	(this->*_eventsHandlers.at(event->getType()))(event);
	}
      catch (const std::out_of_range &e)
	{

	}
      delete event;
    }
}

void				BabelClient::_handleConnection(Event *event)
{
  std::string			ip = event->getData("ip");
  int		port;

  try {
    port = stoi(event->getData("port"));
    if (_network->connect(ip, port))
      {
	_isConnected = true;
	std::cout << "connected to host at ip: " << ip << " port: " << port << std::endl;
	_gui->setGuiState(IGui::CONNECTED);
      }
  }
  catch (std::invalid_argument const &e) {
    std::cerr << "wrong port" << std::endl;
  }
}

void				BabelClient::_handleRegister(Event *event)
{
  std::string			password;
  Message::IOHeader	        header;
  Message::IOAuthentification	authentificationStruct = {};

  std::cout << "handling register" << std::endl;
  std::cout << "userName: " + event->getData("userName") << std::endl;
  std::cout << "password: " + event->getData("password") << std::endl;

  _userName = event->getData("userName");
  password = event->getData("password");
  _userName.copy(authentificationStruct.userName, _userName.length());
  password.copy(authentificationStruct.password, password.length());
  header.op = Event::CLIENT_REGISTER;
  header.length = sizeof(authentificationStruct);
  _network->prepareToSendMessage(header, (unsigned char *) &authentificationStruct);
}

void				BabelClient::_handleAuthentification(Event *event)
{
  std::string			password;
  Message::IOHeader	        header;
  Message::IOAuthentification	authentificationStruct = {};

  std::cout << "handling authentification" << std::endl;
  std::cout << "userName: " + event->getData("userName") << std::endl;
  std::cout << "password: " + event->getData("password") << std::endl;

  _userName = event->getData("userName");
  password = event->getData("password");
  _userName.copy(authentificationStruct.userName, _userName.length());
  password.copy(authentificationStruct.password, password.length());
  header.op = Event::CLIENT_AUTHENTIFICATION;
  header.length = sizeof(authentificationStruct);
  _network->prepareToSendMessage(header, (unsigned char *) &authentificationStruct);
}

void				BabelClient::_handleLogOut(Event *event)
{
  Message::IOHeader	        header;

  header.op = Event::CLIENT_LOGOUT;
  header.length = 0;
  _network->prepareToSendMessage(header, NULL);
}

void				BabelClient::_handleCall(Event *event)
{
  Message::IOHeader		header;
  std::string			contactName = event->getData("contactName");

  header.op = Event::CLIENT_CALL;
  header.length = contactName.length();
  _network->prepareToSendMessage(header, (unsigned char*)contactName.c_str());
}

void				BabelClient::_handleHangUp(Event *event)
{
  // _voiceInterpreter->stopAudioStream();
  // _gui->setLabelVisibility(IGui::USER_HANGUP);
}

void				BabelClient::_handleAddContact(Event *event)
{
  std::string			contactName;
  Message::IOHeader	        header;

  contactName = event->getData("contactName");
  header.op = Event::CLIENT_ADD_CONTACT;
  header.length = contactName.length() + 1;
  _network->prepareToSendMessage(header, (unsigned char *) contactName.c_str());
}

void				BabelClient::_handleAuthentified(Event *event)
{
  (void) event;
  _isAuthentified = true;
  _gui->setGuiState(IGui::AUTHENTIFIED);
}

void				BabelClient::_handleLoggedOut(Event *event)
{
  _isConnected = false;
  _isAuthentified = false;
  _userName.clear();
  _gui->setGuiState(IGui::DISCONNECTED);
}

void				BabelClient::_handleUserAvailable(Event *event)
{
  Message::IOHeader		header;
  std::string			ownIp;
  std::string			port;

  port = "4321";
  // for (const QHostAddress &address: QNetworkInterface::allAddresses())
  //   {
  //     if (address.protocol() == QAbstractSocket::IPv4Protocol
  // 	  && address != QHostAddress(QHostAddress::LocalHost))
  //       ownIp << address.toString();
  //   }
  header.op = Event::CLIENT_PORT_AVAILABLE;
  header.length = port.length() + 1;
  _gui->setLabelVisibility(IGui::IN_CALL);
  _network->prepareToSendMessage(header, (unsigned char *) port.c_str());
  _voiceInterpreter->startAudioStream(4321);
}

void				BabelClient::_handleUserAdded(Event *event)
{
  Message::IOHeader		header;

  header.op = Event::CLIENT_LIST_CONTACT;
  header.length = 0;
  _network->prepareToSendMessage(header, nullptr);
}


void				BabelClient::_handleContactList(Event *event)
{
  Message::IOContactList	*ioContactList;

  _contacts.clear();
  ioContactList = (Message::IOContactList *) event->getData("messageData").c_str();
  std::string data = event->getData("messageData");
  std::cout << "sizeof IOContactList: " << sizeof(Message::IOContactList) << std::endl;
  std::cout << "size of data: " << data.size() << std::endl;
  std::cout << "contact list data" << std::endl;
  std::cout << "nb of contacts: " << ioContactList->nb << std::endl;
  for (unsigned int i = 0; i < data.size(); i++)
    {
      std::cout << "[" << data[i] << "]";
    }
  std::cout << std::endl;
  for (int i = 0; i < ioContactList->nb ; i++)
    {
      _contacts.push_back(Contact(ioContactList->contacts[i].name,
				  ioContactList->contacts[i].isConnected));
    }
  _gui->setContactList(_contacts);
}

void				BabelClient::_handleContactLoggedIn(Event *event)
{
  std::string			contactName = event->getData("messageData");

  for (Contact &contact: _contacts)
    {
      if (contact.getUserName() == contactName)
	{
	  std::cout << "found logged in contact : " << contactName << std::endl;
	  contact.setIfConnected(true);
	  std::cout << "contact is connected: " << contact.getIfConnected() << std::endl;
	}
    }
    std::cout << "new contact list : " << std::endl;
    for (Contact contact: _contacts)
    {
      std::cout << "contact name: " << contact.getUserName() << " isConnected: " << contact.getIfConnected() << std::endl;
    }
  _gui->setContactList(_contacts);
}

void				BabelClient::_handleContactLoggedOut(Event *event)
{
  std::string			contactName = event->getData("messageData");

  for (Contact &contact: _contacts)
    {
      std::cout << "found logged in contact : " << contactName << std::endl;
      if (contact.getUserName() == contactName)
	contact.setIfConnected(false);
      std::cout << "contact is connected: " << contact.getIfConnected() << std::endl;
    }
  std::cout << "new contact list : " << std::endl;
  for (Contact contact: _contacts)
    {
      std::cout << "contact name: " << contact.getUserName() << " isConnected: " << contact.getIfConnected() << std::endl;
    }
  _gui->setContactList(_contacts);
}

void				BabelClient::_ignoreEvent(Event *event)
{
  (void) event;
}

void				BabelClient::_handleIncomingCall(Event *event)
{
  Message::IOCallInformation	callInfo;
  callInfo = *((Message::IOCallInformation*) event->getData("messageData").c_str()) ;
  std::cout << "got incoming call information: " << std::endl;
  std::cout << "from user: " << callInfo.username << std::endl;
  std::cout << "ip: " << callInfo.ip << std::endl;
  std::cout << "port: " << callInfo.port << std::endl;
  _gui->setLabelVisibility(IGui::IN_CALL);
  _voiceInterpreter->setHostIpAndPort(callInfo.ip, callInfo.port);
  _voiceInterpreter->startAudioStream(4322);
}

void				BabelClient::_handleUserDoesntExist(Event *)
{
  _gui->setLabelVisibility(IGui::USER_DOESNT_EXIST);
}

void				BabelClient::_handleAlreadyExist(Event *)
{
  _gui->setLabelVisibility(IGui::USER_ALREADY_EXIST);
}

void				BabelClient::_handleAlreadyOn(Event *)
{
  _gui->setLabelVisibility(IGui::USER_ALREADY_LOGGED);
}

void				BabelClient::_handleWrongPassword(Event *)
{
  _gui->setLabelVisibility(IGui::USER_BAD_PASS);
}
