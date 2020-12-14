#ifndef __MSGHANDLER_DEF_HPP
#define __MSGHANDLER_DEF_HPP

#include <cstring>
#include <string>

#include "def/basedef.hpp"

struct MsgHeader // Э��ͷ
{
	MsgHeader()
	{
		msg_type = 0;
	}

	int msg_type;
};

enum MsgCode  // Э���
{
	MSG_CODE_START = 1000,

	USER_LOGIN_MSG_CS = MSG_CODE_START,				// �û���¼
	SEND_MEESAGE_MSG_CS = 1001,						// ������Ϣ

	MSG_CODE_MAX,
};


#endif // !__MSGHANDLER_DEF_HPP
