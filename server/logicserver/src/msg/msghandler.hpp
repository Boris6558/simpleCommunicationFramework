#ifndef __MSGHANDLER_HPP__
#define __MSGHANDLER_HPP__

/**
 * Э��ת������ʽ[msghead_type##send_content]
 */

#include <string>
#include <cstring>

#include "def/msghandlerdef.hpp"

#define MSG_HANDLER MsgHandler::Instance()

class User;
class TcpServer;
class MsgHandler
{
public:
	MsgHandler();
	~MsgHandler();

	static MsgHandler& Instance();
	void GetCurServer(TcpServer* in_server) { m_cur_server = in_server; }

	void ReadFromClient(User *cur_user,std::string &data,uint size);


	// ����Ϊ����Э���߼�

	// ����Ҫע��
	void OnLogout(User *cur_user, std::string &data, uint data_size);

	// ��Ҫע��
	void OnLogin(User *cur_user,std::string &data,uint data_size);
	void OnGetChatMessage(User *cur_user,std::string &data, uint data_size);

private:
	typedef void(MsgHandler::*NetHandlerFun)(User*,std::string&, uint);
	NetHandlerFun m_handler_list[MSG_CODE_MAX];

	TcpServer *m_cur_server; // ��¼��ʱ������û�id�洢user
	
};

#endif // !__MSGHANDLER_HPP__
