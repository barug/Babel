#ifndef CONTACT_H
#define CONTACT_H

# include <string>

class Contact
{
    std::string _userName;
    bool        _isConnected;

public:
					Contact(const std::string &userName,
						const bool &isConnected);
    const std::string			&getUserName() const;
    const bool				&getIfConnected() const;
    void				setIfConnected(const bool &isConnected);
};

#endif // CONTACT_H
