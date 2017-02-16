#include "../Client.hpp"
#include "../BoostSerializer.hpp"
#include "../BoostSocket.hpp"
#include <boost/asio.hpp>
#include <vector>
#include <iostream>
#include <string>


//serialize and load an user with 2 contacts and password
int main()
{
  std::string			n = "origine";
  boost::asio::io_service	ios;
  IDatabase			*database = new BoostSerializer("../");

  //set user
  Client			*client = new Client(new BoostSocket(ios));
  client->setName(n);

  //set user contacts
  Client			*client1 = new Client(new BoostSocket(ios));
  n = "test";
  client1->setName(n);
  Client			*client2 = new Client(new BoostSocket(ios));
  n = "test2";
  client2->setName(n);
  std::vector<std::string>	map = {client2->getName(), client1->getName()};
  client->setContacts(map);

  //dispay user contacts
  for (unsigned int i = 0; i < client->getContacts().size(); i++)
    std::cout << client->getContacts()[i] << std::endl;

  //save user
  database->saveUser(client);

  //delete user

  delete client1;
  delete client2;
  delete client;

  //reload user
  Client			*newclient = new Client(new BoostSocket(ios));
  n = "origine";
  newclient->setName(n);
  database->loadUser(newclient->getName(), newclient);

  //display user contacts
  std::cout << newclient->getName() << std::endl;
  std::cout << newclient->getContacts().size() << std::endl;
  for (unsigned int i = 0; i < newclient->getContacts().size(); i++)
    std::cout << client->getContacts()[i] << std::endl;


  delete newclient;

  return (0);
}
