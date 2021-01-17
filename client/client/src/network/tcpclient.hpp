#ifndef __TCPCLIENT_HPP__
#define __TCPCLIENT_HPP__

#include <QObject>
#include "def/tcpclientdet.hpp"
#include "def/basedef.hpp"

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

	void Send(std::string send_str); // 发文本用，用来测试
	void Read();
	void Send(const char *data,int send_len);

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

	char m_read_buf[READ_BUFFER];

};

#endif // !__TCPCLIENT_HPP__
