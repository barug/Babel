#ifndef BABELCLIENT_H
#define BABELCLIENT_H

# include <queue>
# include <iostream>
# include <stdexcept>
# include "IGui.hpp"
# include "INetwork.hpp"
# include "Event.hpp"
# include "IVoiceInterpreter.hpp"
# include "VoiceInterpreter.h"
# include "QtUdpSocket.h"

class BabelClient
{
  bool							_isRunning;
  bool							_isConnected;
  bool							_isAuthentified;
  IGui							*_gui;
  INetwork						*_network;
  IVoiceInterpreter					*_voiceInterpreter;
  std::string						_userName;
  std::list<Contact>					_contacts;
  std::map<Event::EventType,
	   void (BabelClient::*)(Event *event)>		_eventsHandlers;


 public:
  BabelClient(int &ac, char *av[]);
  void        start();

 private:
  void							_handleEvents(std::list<Event *> *guiEvents);
  void							_handleConnection(Event *event);
  void							_handleRegister(Event *event);
  void							_handleAuthentification(Event *event);
  void							_handleLogOut(Event *event);
  void							_handleCall(Event *event);
  void							_handleHangUp(Event *event);
  void							_handleAuthentified(Event *event);
  void							_handleLoggedOut(Event *event);
  void							_handleUserAvailable(Event *event);
  void							_handleUserAdded(Event *event);
  void							_handleContactList(Event *event);
  void							_handleAddContact(Event *event);
  void							_ignoreEvent(Event *event);
  void							_handleContactLoggedIn(Event *event);
  void						        _handleContactLoggedOut(Event *event);
  void							_handleIncomingCall(Event *event);
  void							_handleUserDoesntExist(Event *event);
  void						        _handleAlreadyExist(Event *event);
  void						        _handleAlreadyOn(Event *event);
  void							_handleWrongPassword(Event *event);
};

#endif // BABELCLIENT_H
