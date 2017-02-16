#ifndef BABELEVENT_H
#define BABELEVENT_H

# include <string>
# include <map>

class Event
{
public:

  enum EventType					: short int
    {
      CLIENT_CONNECTION					= 0,
      CLIENT_AUTHENTIFICATION				= 1,
      CLIENT_REGISTER					= 2,
      CLIENT_LOGOUT					= 3,
      CLIENT_CALL					= 4,
      CLIENT_PORT_AVAILABLE				= 5,
      CLIENT_HANGUP					= 6,
      CLIENT_ADD_CONTACT				= 7,
      CLIENT_LIST_CONTACT				= 8,
      CLIENT_REMOVE_CONTACT				= 9,
      CLIENT_HANDSHAKE					= 10,
      SERVER_USER_DOESNT_EXIST				= 101,
      SERVER_USER_ALREADY_LOGGED			= 102,
      SERVER_BAD_PASS					= 103,
      SERVER_USER_ALREADY_EXIST				= 104,
      SERVER_USER_NOT_CONNECTED				= 105,
      SERVER_CONTACT_NOT_CONNECTED			= 106,
      SERVER_CONTACT_IN_CONVERSATION			= 107,
      SERVER_CONTACT_DOESNT_EXIST			= 108,
      SERVER_HANDSHAKE_FAILED				= 109,
      SERVER_USER_NOT_A_CONTACT				= 110,
      SERVER_REGISTERED					= 202,
      SERVER_AUTHENTIFIED				= 201,
      SERVER_LOGGED_OUT					= 203,
      SERVER_USER_AVAILABLE				= 204,
      SERVER_USER_ADDED					= 207,
      SERVER_CALL_STARTED				= 205,
      SERVER_CONTACT_LIST				= 301,
      SERVER_CONTACT_LOGGED_IN				= 302,
      SERVER_CONTACT_LOGGED_OUT				= 303,
      SERVER_INCOMING_CALL				= 304
    };

private:
    EventType                                       _eventType;
    std::map<std::string, std::string>              _data;

public:
    Event(const EventType &type);
    const EventType                                 &getType() const;
    void                                            addData(const std::string &id,
                                                            const std::string &data);
    const std::string                               &getData(const std::string &id) const;
    const std::map<std::string, std::string>        &getAllData() const;
};

#endif // BABELEVENT_H
