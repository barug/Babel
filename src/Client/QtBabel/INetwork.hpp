#ifndef BABELINETWORK_H
#define BABELINETWORK_H

# include <string>
# include <queue>
# include "Event.hpp"
# include "Message.h"

class INetwork
{
public:
  virtual ~INetwork() {}
  virtual bool				connect(const std::string &ip, const int &port) = 0;
  virtual std::list<Event *>		*getNetworkEvents() = 0;
  virtual void				prepareToSendMessage(Message::IOHeader &header,
							     unsigned char *data) = 0;
  virtual void				sendMessages() = 0;
};

#endif // BABELINETWORK_H
