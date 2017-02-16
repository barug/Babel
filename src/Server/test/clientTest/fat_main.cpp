#include "../../BabelServer.hpp"
#include "../../BoostCircularBuffer.hpp"

#include <iostream>

int		main()
{
  boost::asio::io_service		ios;
  boost::asio::ip::tcp::endpoint	endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 4242);
  boost::asio::ip::tcp::socket		socket(ios);

  ICircularBuffer::IOHeader		h;

  socket.connect(endpoint);

  // {
  //   typedef struct			s_logInfo
  //   {
  //     char				username[128] = "anonymous";
  //     char				password[128] = "azerty123";
  //   }					logInfo;

  //   logInfo				log;

  //   unsigned char *header = (unsigned char *)(&h);
  //   unsigned char *tmp = (unsigned char *)(&log);
  //   std::cout << sizeof(&tmp) << std::endl;
  //   h.op = 002;
  //   h.length = 256;
  //   unsigned char *res = (unsigned char *)malloc(sizeof(unsigned char) * 262);

  //   int i = 0;
  //   while (i < 6)
  //     res[i] = header[i++];
  //   int j = 0;
  //   while (i < 262)
  //     res[i++] = tmp[j++];
  //   for (int x = 0; x < 262; x++)
  //     std::cout << res[x];
  //   std::cout << std::endl;

  //   std::cout << socket.send(boost::asio::buffer(res, 262), 0) << std::endl;
  //   boost::system::error_code		ec;
  //   boost::asio::streambuf		receivedStreamBuffer;
  //   std::string				str;
  //   size_t bytes = boost::asio::read(socket, receivedStreamBuffer, boost::asio::transfer_at_least(1), ec);
  //   std::cout << "size of read =" << bytes << std::endl;
  //   std::istream	buf(&receivedStreamBuffer);
  //   std::string	data;
  //   buf >> data;
  //   std::cout << data << std::endl;

  //   std::cout <<"CONECT" << std::endl;
  // }

  // {

  //   typedef struct			s_logInfo3
  //   {
  //     char				username[128] = "anonymous";
  //     char				password[128] = "azerty123";
  //   }					logInfo3;

  //   logInfo3				log;

  //   unsigned char *header = (unsigned char *)(&h);
  //   unsigned char *tmp = (unsigned char *)(&log);
  //   std::cout << sizeof(&tmp) << std::endl;
  //   h.op = 003;
  //   h.length = 256;
  //   unsigned char *res = (unsigned char *)malloc(sizeof(unsigned char) * 262);

  //   int i = 0;
  //   while (i < 6)
  //     {
  //	res[i] = header[i];
  //	i++;
  //     }
  //   int j = 0;
  //   while (i < 262)
  //     {
  //	// if (tmp[j] >= 'a' && tmp[j] <= 'z')
  //	res[i] = tmp[j];
  //	// else
  //	//	res[i] = '\0';
  //	i++;
  //	j++;
  //     }
  //   for (int x = 0; x < 262; x++)
  //     {
  //	std::cout << res[x];
  //     }
  //   std::cout << std::endl;
  //   std::cout << socket.send(boost::asio::buffer(res, 262), 0) << std::endl;
  //   boost::system::error_code		ec;
  //   boost::asio::streambuf		receivedStreamBuffer;
  //   std::string				str;

  //   size_t bytes = boost::asio::read(socket, receivedStreamBuffer, boost::asio::transfer_at_least(1), ec);
  //   std::cout << "size of read =" << bytes << std::endl;
  //   std::istream	buf(&receivedStreamBuffer);
  //   std::string	data;

  //   buf >> data;
  //   std::cout << data << std::endl;
  // }

  {
    typedef struct			s_logInfo
    {
      char				username[128] = "anonymous";
      char				password[128] = "azerty123";
    }					logInfo;

    logInfo				log;

    unsigned char *header = (unsigned char *)(&h);
    unsigned char *tmp = (unsigned char *)(&log);
    std::cout << sizeof(&tmp) << std::endl;
    h.op = 001;
    h.length = 256;
    unsigned char *res = (unsigned char *)malloc(sizeof(unsigned char) * 262);

    int i = 0;
    while (i < 6)
      res[i] = header[i++];
    int j = 0;
    while (i < 262)
      res[i++] = tmp[j++];
    for (int x = 0; x < 262; x++)
      std::cout << res[x];
    std::cout << std::endl;

    std::cout << socket.send(boost::asio::buffer(res, 262), 0) << std::endl;

    boost::system::error_code		ec;
    boost::asio::streambuf		receivedStreamBuffer;
    std::string				str;

    size_t bytes = boost::asio::read(socket, receivedStreamBuffer, boost::asio::transfer_at_least(1), ec);
    std::cout << "size of read =" << bytes << std::endl;
    std::istream	buf(&receivedStreamBuffer);
    std::string	data;

    buf >> data;
    for (auto it : data)
      {
	std::cout << it;
      }
    std::cout << std::endl;
  }
  {

    typedef struct			s_logInfo3
    {
      char				username[128] = "anonymous";
      char				password[128] = "azerty123";
    }					logInfo3;

    logInfo3				log;

    unsigned char *header = (unsigned char *)(&h);
    unsigned char *tmp = (unsigned char *)(&log);
    std::cout << sizeof(&tmp) << std::endl;
    h.op = 003;
    h.length = 256;
    unsigned char *res = (unsigned char *)malloc(sizeof(unsigned char) * 262);

    int i = 0;
    while (i < 6)
      {
	res[i] = header[i];
	i++;
      }
    int j = 0;
    while (i < 262)
      {
	// if (tmp[j] >= 'a' && tmp[j] <= 'z')
	res[i] = tmp[j];
	// else
	//	res[i] = '\0';
	i++;
	j++;
      }
    for (int x = 0; x < 262; x++)
      {
	std::cout << res[x];
      }
    std::cout << std::endl;
    std::cout << socket.send(boost::asio::buffer(res, 262), 0) << std::endl;
    boost::system::error_code		ec;
    boost::asio::streambuf		receivedStreamBuffer;
    std::string				str;

    size_t bytes = boost::asio::read(socket, receivedStreamBuffer, boost::asio::transfer_at_least(1), ec);
    std::cout << "size of read =" << bytes << std::endl;
    std::istream	buf(&receivedStreamBuffer);
    std::string	data;

    buf >> data;
    std::cout << data << std::endl;
  }
  {
    typedef struct			s_logInfo
    {
      char				username[128] = "anonymous";
      char				password[128] = "azerty123";
    }					logInfo;

    logInfo				log;

    unsigned char *header = (unsigned char *)(&h);
    unsigned char *tmp = (unsigned char *)(&log);
    std::cout << sizeof(&tmp) << std::endl;
    h.op = 003;
    h.length = 256;
    unsigned char *res = (unsigned char *)malloc(sizeof(unsigned char) * 262);

    int i = 0;
    while (i < 6)
      res[i] = header[i++];
    int j = 0;
    while (i < 262)
      res[i++] = tmp[j++];
    for (int x = 0; x < 262; x++)
      std::cout << res[x];
    std::cout << std::endl;

    std::cout << socket.send(boost::asio::buffer(res, 262), 0) << std::endl;

    boost::system::error_code		ec;
    boost::asio::streambuf		receivedStreamBuffer;
    std::string				str;

    size_t bytes = boost::asio::read(socket, receivedStreamBuffer, boost::asio::transfer_at_least(1), ec);
    std::cout << "size of read =" << bytes << std::endl;
    std::istream	buf(&receivedStreamBuffer);
    std::string	data;

    buf >> data;
    for (auto it : data)
      {
	std::cout << it;
      }
    std::cout << std::endl;
  }


}
