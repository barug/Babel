//
// Message.cpp for Babel in /cpp_babel/src/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Wed Nov  2 12:43:58 2016 Josselin
// Last update Wed Nov  9 15:59:29 2016 Thomas Billot
//

#include "Message.hpp"
#include <iostream>
#include <stdio.h>
#include <cstring>

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
}

Message::~Message()
{
  delete (_ptr);
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
