#ifndef BABELIUDPSOCKET_H
#define BABELIUDPSOCKET_H

#include <string>
#include <QByteArray>

class IUdpSocket
{
public:
  virtual ~IUdpSocket() {}
  virtual void sendData(const std::string & data) = 0;
  virtual void	sendData(const float *frames) = 0;
  virtual void	bindUdp(const std::string &ip, const unsigned int &port) = 0;
  virtual void  bindUdp(const unsigned int &port) = 0;
  virtual void	setHostIp(const std::string &ip) = 0;
  virtual void	setHostPort(const unsigned int &port) = 0;
  virtual QByteArray  &waitForRead() = 0;
};

#endif // BABELIUDPSOCKET_H
