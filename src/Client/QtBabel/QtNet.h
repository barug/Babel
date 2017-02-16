#ifndef         QT_NET_H
# define        QT_NET_H

#include        <QTcpSocket>
#include        "INetwork.hpp"
#include	"QtCircularBuffer.h"

class           QtNet : public QObject, public INetwork
{
  Q_OBJECT
  
  QByteArray		       	data;
  QTcpSocket	       		*_socket;
  ICircularBuffer		*_buffer;
  
public:
  explicit QtNet(QObject *parent = 0);
  virtual ~QtNet();
  virtual bool				connect(const std::string &ip, const int &port);
  virtual std::list<Event *>		*getNetworkEvents();
  virtual void				prepareToSendMessage(Message::IOHeader &header,
							     unsigned char *data);
  virtual void			        sendMessages();  
};

#endif              // QT_NET_H
