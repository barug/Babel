#ifndef QT_UDP_SOCKET_H_
# define QT_UDP_SOCKET_H_

#include <QUdpSocket>
#include "IUdpSocket.hpp"
#include "VoiceInterpreter.h"

class QtUdpSocket : public QObject, public IUdpSocket
{
  Q_OBJECT

private:
  QUdpSocket	*_socket;
  QHostAddress	_ownIp;
  quint16	_ownPort;
  QHostAddress	_hostIp;
  quint16	_hostPort;
  QByteArray	_datagram;
  QHostAddress		_sender;
  quint16		_senderPort;


public:
  explicit QtUdpSocket(QObject *parent = 0);
  virtual ~QtUdpSocket();
  virtual void	sendData(const std::string &string);
  virtual void	sendData(const float *frames);
  virtual void	bindUdp(const std::string &ip, const unsigned int &port);
  virtual void  bindUdp(const unsigned int &port);
  virtual void	setHostIp(const std::string &ip);
  virtual void	setHostPort(const unsigned int &port);
  virtual QByteArray  &waitForRead();
};

#endif	// QT_UDP_SOCKET_H_
