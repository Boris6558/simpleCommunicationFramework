#ifndef __TCPSERVER_HPP__
#define __TCPSERVER_HPP__

#include <vector>
#include <map>

#include "def/tcpserverdef.hpp"
#include "def/basedef.hpp"

class User;
class TcpServer
{
public:
	TcpServer(IOService &ios, int port);
	~TcpServer();

private:
	void Start();
	void AcceptHandler(const ErrorCode &ec);	// 客户端连接上时调用

private:
	Acceptor m_acc;
	Socket m_socket;

};

#endif // !__TCPSERVER_HPP__
