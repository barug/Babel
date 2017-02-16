//
// BoostSerializer.hpp for Babel in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 19:43:42 2016 Josselin
// Last update Tue Nov  8 14:23:41 2016 master
//

#ifndef		__BOOSTSERIALIZER_HPP__
# define	__BOOSTSERIALIZER_HPP__

# include	"IDatabase.hpp"

class		BoostSerializer : public IDatabase
{

public:
  BoostSerializer(const std::string &directoryPath);
  virtual ~BoostSerializer();

  virtual bool		saveUser(const Client *client);
  virtual bool		loadUser(const std::string &name, Client *client);
  virtual std::string	getDirectoryPath() const;

private:
  std::string	_directoryPath;
};

#endif /* !__BOOSTSERIALIZER_HPP__ */
