#include "user.hpp"

#include "def/basedef.hpp"
#include "def/tcpserverdef.hpp"
#include "tool/serializememory.hpp"

#include "msg/msghandler.hpp"
#include "msg/msguser.hpp"

User::User(Socket &&soc):
	m_soc(boost::move(soc))
{
	memset(m_read_buf, 0, READ_BUF);
	m_user_id = "";
	m_passwd = "";

	static int count = 0;
	printf("link success![%s : %d],count[%d]\n",this->GetIp().data(),this->GetPort(), count++);
}

User::~User()
{
}

void User::Init(UserLoginReqCS & rcs)
{
	m_user_id = rcs.user_id;
	m_passwd = rcs.passwd;
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

void User::Read()
{
	memset(m_read_buf, 0, READ_BUF);

	m_soc.async_read_some(BUFFER(m_read_buf, READ_BUF),
		[=](const ErrorCode &ec,uint size)mutable
	{
		this->ReadHandler(ec,size);

	}
		);

	
}

void User::Logout()
{
	printf("[%s:%d] is Logout!\n",this->GetIp().data(),this->GetPort());
}


void User::ReadHandler(const ErrorCode &ec, uint size)
{
	if (ec)
	{
		//printf("read message error!! ,error info[%d]:%s\n", ec.value(), ec.message().data());
		this->Logout();
		return;
	}

	// 协议转发
	std::string data = CastTo(std::string, m_read_buf);
	MSG_HANDLER.ReadFromClient(this,data,data.size());

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
