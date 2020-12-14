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

static const int READ_BUF = 65534;				// 读取字节数最大字节数

#endif // !__TCPCLIENT_DEF_HPP
