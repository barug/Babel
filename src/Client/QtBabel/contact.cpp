#include "Contact.h"

Contact::Contact(const std::string &userName, const bool &isConnected)
    : _userName(userName),
      _isConnected(isConnected)
{}

const std::string     &Contact::getUserName() const
{
    return _userName;
}

const bool            &Contact::getIfConnected() const
{
    return _isConnected;
}

void			Contact::setIfConnected(const bool &isConnected)
{
  _isConnected = isConnected;
}
