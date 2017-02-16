//
// Main.cpp for Main in /home/master/rendu/cpp_babel/src/Server
//
// Made by master
// Login   <master@epitech.net>
//
// Started on  Wed Nov  2 15:09:38 2016 master
// Last update Sun Nov 13 23:35:25 2016 bogard_t
//

# include	<string>
# include	<iostream>
# include	"BabelServer.hpp"

int		displayUsage(char **av)
{
  std::cout << "Usage :\n\t./" << av[0] << " ip port path/to/database" << std::endl;
  return (0);
}

int		main(int ac, char **av)
{
  if (ac < 4)
    return (displayUsage(av));
  int port;
  std::string ip;

  try {
    port = std::stoi(av[2]);
    ip = std::string(av[1]);

    boost::system::error_code	ec;
    boost::asio::ip::address::from_string(ip, ec);
    if (ec)
      {
	std::cerr << "Wrong Ip" << std::endl;
	return (-1);
      }
    BabelServer	babel(ip, port, std::string(av[3]));
    return (babel.run());
  }
  catch (std::invalid_argument const &e)
    {
      std::cerr << "Wrong Port" << std::endl;
      return (-1);
    }
  return (0);
}
