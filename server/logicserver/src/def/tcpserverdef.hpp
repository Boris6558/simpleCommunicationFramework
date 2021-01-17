#ifndef __TCPSERVERDEF_HPP__
#define __TCPSERVERDEF_HPP__

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

#define BUFFER boost::asio::buffer
#define IPV4 boost::asio::ip::tcp::v4()

typedef boost::asio::io_service					IOService;
typedef boost::asio::ip::tcp::endpoint			EndPoint;
typedef boost::asio::ip::tcp::socket			Socket;
typedef boost::asio::ip::address				Address;
typedef boost::asio::ip::tcp::acceptor			Acceptor;
typedef boost::system::error_code				ErrorCode;
typedef boost::asio::yield_context				YieldCont;

static const int READ_BUFFER = 1024 * 1024 * 4;				// 每次读取最多4M


#endif // !__TCPSERVERDEF_HPP__
