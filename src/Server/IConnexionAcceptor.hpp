//
// IConnexionAcceptor.hpp for Babel in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 23:18:07 2016 Josselin
// Last update Sun Nov 13 22:39:32 2016 Thomas Billot
//

#ifndef		__ICONNEXIONACCEPTOR_HPP__
# define	__ICONNEXIONACCEPTOR_HPP__

# include	"BoostSocket.hpp"

class		IConnexionAcceptor
{

public:

  virtual ~IConnexionAcceptor()	{}
  virtual ISocket	*acceptConnexion() = 0;
  virtual int		getServerFd() = 0;
};

#endif		/* !__ICONNEXIONACCEPTOR_HPP__ */
