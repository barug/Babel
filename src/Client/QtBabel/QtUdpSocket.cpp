#include "QtUdpSocket.h"
#include <iostream>
#include <VoiceInterpreter.h>

QtUdpSocket::QtUdpSocket(QObject *parent)
  : QObject(parent),
    _hostPort(0),
    _socket(new QUdpSocket(this))
{
}

QtUdpSocket::~QtUdpSocket()
{
    delete this->_socket;
}

void			QtUdpSocket::bindUdp(const std::string &ip, const unsigned int &port)
{
  this->_ownIp = QString::fromStdString(ip); this->_ownPort = (quint16)port;
  this->_socket->bind(this->_ownIp, this->_ownPort);
}

void			QtUdpSocket::bindUdp(const unsigned int &port)
{
  this->_ownPort = (quint16)port;
  this->_socket->bind(this->_ownPort);
}

void			QtUdpSocket::sendData(const std::string &string)
{
  QByteArray		data;

  data.append(QString::fromStdString(string));
  this->_socket->writeDatagram(data, this->_hostIp, this->_hostPort);
  this->_socket->waitForBytesWritten();
}

void			QtUdpSocket::sendData(const float *frames)
{
  QByteArray		data;

  data.append((char *) frames, sizeof(float) * FRAMES_PER_BUFFER);
  this->_socket->writeDatagram(data,
			       data.size(),
			       this->_hostIp,
			       this->_hostPort);
  this->_socket->waitForBytesWritten();
}

void			QtUdpSocket::setHostIp(const std::string &ip)
{
  _hostIp = QString::fromStdString(ip);
}

void			QtUdpSocket::setHostPort(const unsigned int &port)
{
  this->_hostPort = (quint16)port;
}

#include <stdlib.h>
QByteArray	        &QtUdpSocket::waitForRead()
{
  if (this->_socket->hasPendingDatagrams())
    {
      _datagram.resize(this->_socket->pendingDatagramSize());
      this->_socket->readDatagram(_datagram.data(), _datagram.size(), &_sender, &_senderPort);
      if (_hostIp.isNull())
	{
	  _hostIp = _sender;
	  _hostPort = _senderPort;
	}
      // qDebug() << "data" << datagram.data();
      // qDebug() << "data gram received from " << sender.toString();
    }
  return _datagram;
}
