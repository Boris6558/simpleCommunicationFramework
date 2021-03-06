#include "tcpserver.hpp"
#include "configmanager/configmanager.hpp"
#include "network/tcpserverconfig.hpp"
#include "user.hpp"

TcpServer::TcpServer(IOService &ios,int port) :
	m_acc(ios, EndPoint(IPV4, port)),
	m_socket(ios)
{
	this->Start();
}

TcpServer::~TcpServer()
{

}

void TcpServer::Start()
{
	m_acc.async_accept(m_socket,
		[&](const ErrorCode &ec)mutable
	{
		this->AcceptHandler(ec);
		
	}
		);

}

void TcpServer::AcceptHandler(const ErrorCode &ec)
{
	if (ec)
	{
		printf("async_accept error!! ,error info[%d]:%s\n",ec.value(),ec.message().data());
		return;
	}


	User *user = new User(boost::move(m_socket));
	user->Read();


	this->Start();

}
