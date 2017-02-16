#include "QtNet.h"
#include <iostream>

QtNet::QtNet(QObject *parent)
  : QObject(parent),
    _socket(new QTcpSocket(this)),
    _buffer(new QtCircularBuffer)
{
}

QtNet::~QtNet()
{
  delete (this->_socket);
}

std::list<Event *>*	QtNet::getNetworkEvents()
{
  std::list<Event *>	*networkEvent = new std::list<Event *>;
  Message		*message;
  QByteArray		inData;

  inData = _socket->readAll();
  if (inData.size() > 0)
    {
      std::cout << "received data: ------" << std::endl;
      for (int i = 0; i < inData.size(); i++)
	std::cout << "[" << inData[i] << "]";
      std::cout << std::endl;
    }
  _buffer->writeInBuffer((unsigned char *)  inData.data(), inData.size());
  while ((message = _buffer->readInBuffer()))
    {
      networkEvent->push_front(new Event((Event::EventType) message->getOperationCode()));
      networkEvent->front()->addData("messageData",
				     std::string((char *) message->getData(),
						 message->getSize()));
    }
  return networkEvent;
}

void				QtNet::prepareToSendMessage(Message::IOHeader &header,
							    unsigned char *data)
{
  _buffer->writeOutBuffer(&header, data);
}

void				QtNet::sendMessages()
{
  std::vector<unsigned char>	*outData;
  Message::IOHeader		*header;
  
  while (_socket->isWritable() && (outData = _buffer->readOutBuffer()))
    {
      header = (Message::IOHeader*)(outData->data());
      std::cout << "sending data: -------" << std::endl;
      std::cout << "op: " << header->op << std::endl;
      std::cout << "data length: " << header->length << std::endl;
      std::cout << "data: ";
      for (unsigned int i = 0; i < outData->size() ; i++)
	std::cout << "[" << (char) ((*outData)[i]) << "]" ;
      std::cout << std::endl;
      _socket->write((const char *) outData->data(), outData->size());
      _socket->waitForBytesWritten();
    }
}


bool			QtNet::connect(const std::string &ip, const int &port)
{
  this->_socket->connectToHost(QString::fromStdString(ip), port);
  if (!this->_socket->waitForConnected(1000))
    {
      std::cout << "could not connect" << std::endl;
      return false;
    }
  return true;
}
