#include "../Message.hpp"
#include "../BoostCircularBuffer.hpp"
#include <iostream>
#include <cstring>
#include <cstdio>

int main()
{
  ICircularBuffer *buffer = new BoostCircularBuffer();
  BoostCircularBuffer::IOHeader t;
  // boost::asio::io_service	ios;
  // boost::asio::ip::tcp::endpoint	endpoint(boost::asio::ip::address::from_string("10.41.175.139"), 4242);
  // boost::asio::ip::tcp::socket		socket(ios);

  //prepare IOHeader
  t.op = 001;
  t.length = 256;
  unsigned char *str = (unsigned char*)"testconnexionTESTaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabtestconnexionTESTaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabtestconnexionTESTaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabcd";
  unsigned char * str2 = (unsigned char*)(&t);
  unsigned char * test = (unsigned char*)malloc(262);

  //simulate receive data with IOHeader struct
  int i = 0;
  while (i< 6){
    test[i] = str2[i];
    i++;
  }
  while (i < 262) {
    test[i] = str[i - 6];
    i++;
  }
  buffer->writeInBuffer(test, 262);

  // socket.connect(endpoint);
  // socket.send(boost::asio::buffer(test, 108), 0);

  //read received data
  Message *message = buffer->readInBuffer();//need to be delete

  //print message attribute
  std::cout << message->getSize() << std::endl;
  std::cout << message->getOperationCode() << std::endl;
  std::cout << message->getData() << std::endl;

  //remember to delete message and buffer
  delete message;
  delete buffer;
  return (0);
}
