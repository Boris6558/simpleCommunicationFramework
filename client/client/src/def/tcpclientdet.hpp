#ifndef __TCPCLIENT_DEF_HPP
#define __TCPCLIENT_DEF_HPP

#include <boost/asio.hpp>

#define BUFFER	boost::asio::buffer

typedef boost::asio::io_service					IOService;
typedef boost::asio::ip::tcp::endpoint			EndPoint;
typedef boost::asio::ip::tcp::socket			Socket;
typedef boost::asio::ip::address				Address;
typedef boost::system::error_code				ErrorCode;
typedef boost::asio::steady_timer				SteadyTimer;

static const int READ_BUFFER = 1024 * 1024 * 4;				// 每次读取最多4M

#endif // !__TCPCLIENT_DEF_HPP
