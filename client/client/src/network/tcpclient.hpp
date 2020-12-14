#ifndef __TCPCLIENT_HPP__
#define __TCPCLIENT_HPP__

#include <QObject>
#include "def/tcpclientdet.hpp"

#define TCP_C TcpClient::Instance()


struct TipString;
class TcpClient : public QObject
{
	Q_OBJECT

public:
	TcpClient();
	~TcpClient();
	static TcpClient& Instance();

	bool Connect();
	void Disconnect();

	void Send(std::string send_str,int req_type);
	void Read();

private:
	void SendHandler();
	void ReadHandler();

Q_SIGNALS:
	void SigConnectTimeout();
	void SigConnectSuccess();
	void SigServerClose();
private:
	IOService m_ios;
	EndPoint m_ep;
	Socket *m_soc;
	ErrorCode ec;

	char m_read_buf[READ_BUF];

};

#endif // !__TCPCLIENT_HPP__
