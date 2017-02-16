#include "../QtCircularBuffer.h"
#include <string.h>
#include <iostream>

int main()
{
  QtCircularBuffer buffer;
  ICircularBuffer::IOHeader	   header;
  std::vector<unsigned char>	  *dataRead;
  Message		*message;
  
  header.op = 001;
  header.length = strlen("this is the data");  
  buffer.writeOutBuffer(&header,  (unsigned char *) "this is the data");
  header.op = 002;
  header.length = strlen("another bit of data");  
  buffer.writeOutBuffer(&header, (unsigned char *) "another bit of data");
  header.op = 003;
  header.length = strlen("and another one");  
  buffer.writeOutBuffer(&header, (unsigned char *) "and another one");
  dataRead = buffer.readOutBuffer(); 
  buffer.writeInBuffer(dataRead->data(), dataRead->size());
  dataRead = buffer.readOutBuffer(); 
  buffer.writeInBuffer(dataRead->data(), dataRead->size());
  dataRead = buffer.readOutBuffer(); 
  buffer.writeInBuffer(dataRead->data(), dataRead->size());
  message = buffer.readInBuffer();
  std::cout << "op: " << message->getOperationCode() << std::endl;
  std::cout << "size: " << message->getSize() << std::endl;
  std::cout << "data: " << message->getData() << std::endl;;
  message = buffer.readInBuffer();
  std::cout << "op: " << message->getOperationCode() << std::endl;
  std::cout << "size: " << message->getSize() << std::endl;
  std::cout << "data: " << message->getData() << std::endl;
  message = buffer.readInBuffer();
  std::cout << "op: " << message->getOperationCode() << std::endl;
  std::cout << "size: " << message->getSize() << std::endl;
  std::cout << "data: " << message->getData() << std::endl;
  return (0);
}
