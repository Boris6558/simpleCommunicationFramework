#include "user.hpp"

#include "def/basedef.hpp"
#include "def/tcpserverdef.hpp"

#include "tool/serializememory.hpp"
#include "usermanager/usermanager.hpp"

#include "msg/msghandler.hpp"
#include "msg/msguser.hpp"

User::User(Socket &&soc):
	m_soc(boost::move(soc))
{
	memset(m_read_buf, 0, READ_BUFFER);

	static int count = 0;
	printf("link success![%s : %d],count[%d]\n",this->GetIp().data(),this->GetPort(), count++);
}

User::~User()
{
}

void User::Init(UserBaseInfoStock &user_once)
{
	m_stock = user_once;
}

void User::Send(std::string send_str)
{
	m_soc.async_write_some(BUFFER(send_str.data(), send_str.size()),
		[=](const ErrorCode &code, uint size)mutable
	{
		this->SendHandler(code,size);
	}
	);
}

void User::Send(const char * data, int send_len)
{
	m_soc.async_write_some(BUFFER(data, send_len),
		[=](const ErrorCode &code, uint size)mutable
	{
		this->SendHandler(code, size);
	}
	);
}

void User::Read()
{
	memset(m_read_buf, 0, READ_BUFFER);

	m_soc.async_read_some(BUFFER(m_read_buf, READ_BUFFER),
		[=](const ErrorCode &ec,uint size)mutable
	{
		this->ReadHandler(ec,size);

	}
		);

	
}

void User::Logout()
{
	printf("user_id[%lld],[%s:%d] is Logout!\n",this->GetUserId(),this->GetIp().data(),this->GetPort());

	// 退出后保存用户的数据

	// 最后删除该用户数据
	USER_MGR.RemoveUser(this->GetUserId());
}


void User::ReadHandler(const ErrorCode &ec, uint size)
{
	if (ec)
	{
		//printf("read message error!! ,error info[%d]:%s\n", ec.value(), ec.message().data());
		this->Logout();
		return;
	}

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

	// 协议转发
	MSG_HANDLER.ReadFromClient(this,m_read_buf, read_byte);

	this->Read();
	

}

void User::SendHandler(const ErrorCode &ec, uint size)
{
	if (ec)
	{
		printf("AsynSend error!\n");
		return;
	}
}
