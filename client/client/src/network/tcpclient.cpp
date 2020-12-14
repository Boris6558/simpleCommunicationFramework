#include "tcpclient.hpp"


#include "def/threaddef.hpp"
#include "def/tcpserverconfigdef.hpp"
#include "def/prompttextdef.hpp"

#include "configmanager/configmanager.hpp"
#include "threadmanager/threadmanager.hpp"
#include "msg/msghandler.hpp"

#include "other/networkconfig/tcpserverconfig.hpp"


TcpClient::TcpClient()
{
	TcpServerConfig *ts_cfg = CONFIG_MGR.GetTcpServerConfig();
	ServerInfo *info = NULL;
	if (ts_cfg)
	{
		info = ts_cfg->GetServerInfo();
		if (!info)
		{
			assert(0);
		}
	}
	m_ep = EndPoint(Address::from_string(info->ip), info->port);

	memset(m_read_buf, 0, READ_BUF);
}

TcpClient::~TcpClient()
{
	this->Disconnect();
}

TcpClient & TcpClient::Instance()
{
	static TcpClient tc;
	return tc;
}

bool TcpClient::Connect()
{
	if (m_soc)
	{
		return false;
	}
	m_soc = new Socket(m_ios);

	m_soc->connect(m_ep, ec);

	if (ec)
	{
		printf("[%d] tcpclient timeout!\n",CUR_THREAD_ID);
		return false;
	}
	else
	{
		printf("[%d] tcpclient success!\n", CUR_THREAD_ID);
	}

	return true;
}

void TcpClient::Disconnect()
{
	if (!m_soc)
	{
		return;
	}

	m_soc->close();
	delete m_soc;
	m_soc = NULL;

	printf("[%d] disconnect!!\n", CUR_THREAD_ID);

}

void TcpClient::Send(std::string send_str, int req_type)
{
	MSG_HANDLER.SendToServer(send_str, req_type);  // 协议转发

	m_soc->async_write_some(BUFFER(send_str.data(), send_str.size()),
		[&](const ErrorCode &code,uint size)mutable
	{
		if (!code)
		{
			printf("[%d] send string to server!\n", CUR_THREAD_ID);
			return;
		}

		this->SendHandler();
	}
	);

}

void TcpClient::Read()
{
	memset(m_read_buf, 0, READ_BUF);
	ErrorCode ec;
	m_soc->read_some(BUFFER(m_read_buf, READ_BUF), ec);
	if (ec)
	{
		printf("Read server info fail!! code[%d:%s]\n",ec.value(),ec.message().data());
		if (ec.value() == 10054) // 服务器关闭了
		{
			Q_EMIT this->SigServerClose();
		}
		return;
	}
	this->ReadHandler();
	this->Read();
}

void TcpClient::SendHandler()
{
}

void TcpClient::ReadHandler()
{
	
	// 心跳包
	/*this->Send("tcp heart to server\n");
	THREAD_MGR.Sleep(3);*/

	MSG_HANDLER.ReadFromServer(CastTo(std::string, m_read_buf));

	
}
