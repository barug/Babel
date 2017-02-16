//
// Message.hpp for Babel in /cpp_babel/src/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Wed Nov  2 12:43:38 2016 Josselin
// Last update Wed Nov  9 15:59:10 2016 Thomas Billot
//

#ifndef __MESSAGE_HPP__
# define __MESSAGE_HPP__

# define STRUCT_SIZE	6

# include <vector>

class Message
{

public:
  
  Message(std::vector<unsigned char> *buffer);
  ~Message();
  short int				getOperationCode() const;
  int					getSize() const;
  unsigned char				*getData() const;

private:
  
  unsigned char				*_data;
  short int				_operationCode;
  int					_size;
  std::vector<unsigned char>		*_ptr;
};

#endif /* !__MESSAGE_HPP__ */
