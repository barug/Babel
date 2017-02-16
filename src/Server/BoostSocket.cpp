//
// BoostSocket.cpp for Babel in /cpp_babel/design_documents/Server
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Thu Oct 27 20:45:33 2016 Josselin
// Last update Sun Nov 13 22:43:45 2016 Thomas Billot
//

#include	<vector>
#include	<iostream>
#include	<ios>
#include	<boost/array.hpp>

#include	"BoostSocket.hpp"

BoostSocket::BoostSocket(boost::asio::io_service &ios) :
  _socket()
{
  boost::shared_ptr<boost::asio::ip::tcp::socket>	socket(new boost::asio::ip::tcp::socket(ios));
  _socket = socket;
}

BoostSocket::~BoostSocket()
{}


bool					BoostSocket::readSocket(std::vector<unsigned char> &destBuffer) const
{
  try
    {
      boost::system::error_code		ec;
      boost::asio::streambuf		receivedStreamBuffer;
      std::string			str;

      size_t bytes = boost::asio::read(this->getBoostSocket(),
				       receivedStreamBuffer,
				       boost::asio::transfer_at_least(1),
				       ec);
      if (bytes == 0 || ec != boost::system::errc::errc_t::success)
	return (false);
      boost::asio::streambuf::const_buffers_type bufs = receivedStreamBuffer.data();
      std::string tmp(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + receivedStreamBuffer.size());
      for (auto it : tmp)
	destBuffer.push_back(it);
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
  return (true);
}

bool					BoostSocket::writeSocket(const std::vector<unsigned char> &srcBuffer) const
{
  try
    {
      boost::system::error_code		ec;
      unsigned int i = this->getBoostSocket().send(boost::asio::buffer(srcBuffer, srcBuffer.size()), 0, ec);
      if (i == 0 || ec != boost::system::errc::errc_t::success)
	return (false);
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
  return (true);
}

boost::asio::ip::tcp::socket	&BoostSocket::getBoostSocket() const
{
  return (*_socket.get());
}

std::string     BoostSocket::getIpAddress() const
{
  return (this->getBoostSocket().remote_endpoint().address().to_string());
}

int		BoostSocket::getPort() const
{
  return (this->getBoostSocket().remote_endpoint().port());
}

int		BoostSocket::getFd() const
{
  return (_socket->native());
}
