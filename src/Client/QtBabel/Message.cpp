#include "Message.h"
#include <cstring>

Message::Message()
{}

Message::Message(std::vector<unsigned char> *buffer) : _data(buffer->data()),
						       _operationCode(),
						       _size(),
						       _ptr(buffer)
{
    unsigned char op[2] = {_data[0], _data[1]};
  unsigned char size[4] = {_data[2], _data[3], _data[4], _data[5]};

  std::memcpy(&_operationCode, op, 2);
  std::memcpy(&_size, size, 4);
  this->_data += STRUCT_SIZE;

  // this->_data = buffer->data();
  // this->_operationCode = this->_data[0];
  // this->_size = this->_data[4];
  // this->_data += 8;
  // this->_ptr = buffer;
}

Message::~Message()
{
  delete this->_ptr;
}

void				Message::setOperationCode(const short int &operationCode)
{
  _operationCode = operationCode;
}

void				Message::setSize(const int &size)
{
  _size = size;
}
  
void				Message::setData(unsigned char *data)
{
  _data = data;
}

short int				Message::getOperationCode() const
{
  return this->_operationCode;
}

int					Message::getSize() const
{
  return this->_size;
}

unsigned char				*Message::getData() const
{
  return this->_data;
}
