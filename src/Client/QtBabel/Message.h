#ifndef __MESSAGE_H__
# define __MESSAGE_H__

# include <vector>

# define STRUCT_SIZE	6

class Message
{  
public:
  #pragma pack(push, 1)
  typedef struct		s_IOHeader
  {
    short int			op;
    int				length;
  }				IOHeader;

  typedef struct		s_IOAuthentification
  {
    char			userName[128];
    char			password[128];
  }				IOAuthentification;
  
  typedef struct		s_Contact
  {
    char			name[128];
    bool			isConnected;
  }				IOContact;

  typedef struct		s_IOContactList
  {
    int				nb;
    IOContact			contacts[];
  }				IOContactList;

  typedef struct		s_IOCallInformation
  {
    char			username[128];
    char			ip[15];
    int				port;
  }				IOCallInformation;
#pragma pack(pop)

  Message();
  Message(std::vector<unsigned char> *buffer);
  ~Message();
  void				setOperationCode(const short int &operationCode);
  void				setSize(const int &size);
  void				setData(unsigned char *data);
  short int			getOperationCode() const;
  int				getSize() const;
  unsigned char			*getData() const;

private:
  unsigned char			*_data;
  short int			_operationCode;
  int				_size;
  std::vector<unsigned char>    *_ptr;

};

#endif /* !__MESSAGE_HPP__ */
