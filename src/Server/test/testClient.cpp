#include "../BoostConnexionAcceptor.hpp"
#include "../BoostSocket.hpp"
#include "../BoostCircularBuffer.hpp"
#include <iostream>

int main()
{
  BoostConnexionAcceptor acceptor("127.0.0.1", 4242);
  BoostSocket		*socket;
  BoostCircularBuffer	buffer;
  std::vector<unsigned char> charBuff;
  Message *message = nullptr;
  
  while (!(socket = acceptor.acceptConnexion()))
    ;
  while (1)
    {
      socket->readSocket(charBuff);
      if (!charBuff.empty())
	{
	  std::cout << charBuff.data() << std::endl;
	  buffer.writeInBuffer(charBuff.data(), charBuff.size());
	  charBuff.clear();
	}
      if ((message = buffer.readInBuffer()))
	{
	  std::cout << "op : " << message->getOperationCode() << std::endl;
	  std::cout << "size : " << message->getSize() << std::endl;
	  std::cout << "data : " << message->getData() << std::endl;
	  delete message;
	  message = nullptr;
	}
    }
}
