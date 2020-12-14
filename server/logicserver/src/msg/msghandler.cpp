#include "msghandler.hpp"

#include "tool/stringop.hpp"
#include "tool/serializememory.hpp"

#include "network/tcpserver.hpp"
#include "network/user.hpp"

#include "msguser.hpp"

MsgHandler::MsgHandler():
	m_cur_server(NULL)
{
	m_handler_list[USER_LOGIN_MSG_CS] = &MsgHandler::OnLogin;
	m_handler_list[SEND_MEESAGE_MSG_CS] = &MsgHandler::OnGetChatMessage;

}

MsgHandler::~MsgHandler()
{
}

MsgHandler & MsgHandler::Instance()
{
	static MsgHandler mh;
	return mh;
}

void MsgHandler::ReadFromClient(User *cur_user, std::string &data, uint size)
{
	if (cur_user == NULL)
	{
		return;
	}

	ProtocolPack sp;
	SplitString(data, "##", sp);

	// 非协议内容
	if (sp.msg_type < MSG_CODE_START || sp.msg_type >= MSG_CODE_MAX)
	{
		//printf("read message:[%s]\n", data.data());
		cur_user->Send("recall\n");
		return;
	}

	// 执行协议
	(this->*m_handler_list[sp.msg_type])(cur_user,sp.msg_content, size);
	
	cur_user->Send("recall\n");

}

void MsgHandler::OnLogout(User * cur_user, std::string & data, uint data_size)
{
}

void MsgHandler::OnLogin(User *cur_user,std::string &data, uint data_size)
{
	printf("login protoal read size[%d]:[%s]\n", data_size,data.data());

	UserLoginReqCS req;
	UnSerializationByMemory<UserLoginReqCS>(req, data);
	cur_user->Init(req);
}

void MsgHandler::OnGetChatMessage(User *cur_user,std::string & data, uint data_size)
{
	printf("OnGetChatMessage protoal read size[%d]:[%s],count[%d]\n", data_size, data.data());
}
