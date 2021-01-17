#ifndef __MSGHANDLER_HPP__
#define __MSGHANDLER_HPP__

/**
 * Э��ת������ʽ[msghead_type##send_content]
 */

#include <string>
#include <cstring>

#include "def/msghandlerdef.hpp"
#include "def/basedef.hpp"

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

	__DEPRECATED void ReadFromClient2(User *cur_user,std::string &data,uint size); // ����
	void ReadFromClient(User *cur_user,const char *data,uint size);



	// ����Ϊ����Э���߼�

	// ����Ҫע��
	void OnLogout(User *cur_user, const char *data, uint data_size);

	// ��Ҫע��
	void OnLogin(User *cur_user, const char *data,uint data_size);

private:
	typedef void(MsgHandler::*NetHandlerFun)(User*,const char *, uint);
	NetHandlerFun m_handler_list[MSG_CODE_MAX];

	TcpServer *m_cur_server; // ��¼��ʱ������û�id�洢user
	
};

#endif // !__MSGHANDLER_HPP__
