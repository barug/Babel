//
// BoostSerializer.cpp for Babel in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 19:48:24 2016 Josselin
// Last update Sun Nov 13 18:01:44 2016 Thomas Billot
//

#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/filesystem.hpp>
#include "BoostSerializer.hpp"

BoostSerializer::BoostSerializer(const std::string &directoryPath) : _directoryPath(directoryPath)
{
  this->_directoryPath += (this->_directoryPath.back() == '/') ? "./" : "/";
  if (!boost::filesystem::exists(boost::filesystem::path(_directoryPath.c_str())))
    boost::filesystem::create_directories(boost::filesystem::path(_directoryPath.c_str()));
}

BoostSerializer::~BoostSerializer() {}

bool					BoostSerializer::saveUser(const Client *client)
{
  try {
    if (client != NULL && !client->getName().empty()) {
      std::string			path = this->_directoryPath + client->getName() + ".babel";
      std::ofstream			stream(path);
      boost::archive::text_oarchive	archive(stream);

      std::cout << "We open :" << path << std::endl;
      archive << client->getContacts();
      archive << client->getPassword();
      std::cout << "User Seriallized" << std::endl;
      return true;
    }
    else
      return false;
  }
  catch (const std::exception &e) {
    return false;
  }
}

bool					BoostSerializer::loadUser(const std::string &name, Client *client)
{
  std::string check = this->getDirectoryPath();
  std::ifstream file(check + name + ".babel");

  if (file.good())
    std::cout << "Le fichier exist" << std::endl;
  else
    std::cout << "[" << check << name << ".babel" << "]" << std::endl;

  try {
    if (client != NULL && !name.empty()) {
      std::string			path = this->_directoryPath + name + ".babel";
      std::ifstream			stream(path);
      std::string			passTMP;
      std::vector<std::string>		contactTMP;
      boost::archive::text_iarchive	archive(stream);

      archive >> contactTMP;
      archive >> passTMP;
      client->setContacts(contactTMP);
      client->setPassword(passTMP);

      std::cout << "User loaded" << std::endl;
      return true;
    }
    else
      return false;
  }
  catch (const std::exception &e) {
    return false;
  }
}

std::string	BoostSerializer::getDirectoryPath() const
{
  return _directoryPath;
}
