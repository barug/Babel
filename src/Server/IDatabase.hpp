//
// IDatabase.hpp for Babel in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 19:37:12 2016 Josselin
// Last update Sun Nov 13 22:39:40 2016 Thomas Billot
//

#ifndef		__IDATABASE_HPP__
# define	__IDATABASE_HPP__

# include	"Client.hpp"

class		IDatabase
{

public:
  
  virtual ~IDatabase()	{}
  virtual bool		saveUser(const Client *client) = 0;
  virtual bool		loadUser(const std::string &name, Client *client) = 0;
  virtual std::string	getDirectoryPath() const = 0 ;
};

#endif /* !__IDATABASE_HPP__ */
