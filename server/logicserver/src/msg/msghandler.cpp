#include "msghandler.hpp"

#include "tool/serializememory.hpp"
#include "tool/uidtool.hpp"

#include "network/tcpserver.hpp"
#include "network/user.hpp"

#include "msguser.hpp"
#include "usermanager/usermanager.hpp"

#include "stockstruct/userstock.hpp"

MsgHandler::MsgHandler():
	m_cur_server(NULL)
{
	m_handler_list[USER_LOGIN_MSG_CS] = &MsgHandler::OnLogin;

}

MsgHandler::~MsgHandler()
{
}

MsgHandler & MsgHandler::Instance()
{
	static MsgHandler mh;
	return mh;
}

__DEPRECATED void MsgHandler::ReadFromClient2(User *cur_user, std::string &data, uint size)
{
	//if (cur_user == NULL)
	//{
	//	return;
	//}

	//ProtocolPack sp;
	//SplitString(data, "##", sp);

	//// 非协议内容
	//if (sp.msg_type < MSG_CODE_START || sp.msg_type >= MSG_CODE_MAX)
	//{
	//	//printf("read message:[%s]\n", data.data());
	//	cur_user->Send("recall\n");
	//	return;
	//}

	//// 执行协议
	//(this->*m_handler_list[sp.msg_type])(cur_user,sp.msg_content, size);
	//
	//cur_user->Send("recall\n");

}

void MsgHandler::ReadFromClient(User * cur_user, const char * data, uint size)
{
	if (cur_user == NULL)
	{
		return;
	}

	// 解析包头
	char head[sizeof(MsgHeader)];
	memmove(head, data, sizeof(MsgHeader));
	pint msg_type = (pint)&head;

	// 非协议内容
	if (*msg_type < MSG_CODE_START || *msg_type >= MSG_CODE_MAX)
	{
		printf("(non msg type)read size[%d]: [%s]\n",size,data);
		cur_user->Send("recall\n");
		return;
	}

	// 执行协议
	(this->*m_handler_list[*msg_type])(cur_user, data, size);

}

void MsgHandler::OnLogout(User * cur_user, const char *data, uint data_size)
{
}

void MsgHandler::OnLogin(User *cur_user, const char *data, uint data_size)
{
	P_UserLoginReqCS req = (P_UserLoginReqCS)data;

	UserBaseInfoStock user_once_stock;
	memcpy(user_once_stock.login_name, req->login_name, sizeof(CString));
	memcpy(user_once_stock.login_passwd, req->login_passwd, sizeof(CString));

	ullong new_user_id = UidTool::CreatUid(user_once_stock.login_name);
	if (new_user_id == GENERATED_UID_ERROR)
	{
		return;
	}
	user_once_stock.uid = new_user_id;

	cur_user->Init(user_once_stock);
	USER_MGR.AddUser(cur_user);

	printf("login protoal read size[%d]:login user[%d : %s]\n", data_size, (int)user_once_stock.uid,req->login_name);
	cur_user->Send("recall\n");

}
