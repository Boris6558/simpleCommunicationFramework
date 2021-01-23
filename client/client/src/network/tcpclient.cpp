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

	memset(m_read_buf, 0, READ_BUFFER);
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
		this->Disconnect();
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
void TcpClient::Send(std::string send_str)
{
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
	memset(m_read_buf, 0, READ_BUFFER);
	ErrorCode ec;
	m_soc->read_some(BUFFER(m_read_buf, READ_BUFFER), ec);
	if (ec)
	{
		printf("Read server info fail!! code[%d:%s]\n",ec.value(),ec.message().data());
		switch (ec.value())
		{
		case 10054:			// 服务器关闭了
		case 2:				// 断点

			Q_EMIT this->SigServerClose();
			break;
		}
		return;
	}
	this->ReadHandler();
	this->Read();
}

void TcpClient::Send(const char * data, int send_len)
{
	m_soc->async_write_some(BUFFER(data, send_len),
		[&](const ErrorCode &code, uint size)mutable
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

void TcpClient::SendHandler()
{
}

void TcpClient::ReadHandler()
{

	// 实际读到的字节
	int read_byte = 0;
	for (int i = READ_BUFFER - 1; i > 0; i--)
	{
		if (m_read_buf[i] == '\0' && m_read_buf[i - 1] != '\0')
		{
			break;
		}
		++read_byte;
	}
	read_byte = READ_BUFFER - read_byte - 1;

	MSG_HANDLER.ReadFromServer(m_read_buf, read_byte);

	
}
