#ifndef __MSGHANDLER_DEF_HPP
#define __MSGHANDLER_DEF_HPP

#include <cstring>
#include <string>

#include "def/basedef.hpp"

#pragma pack(push,4)

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

	MSG_CODE_MAX,
};

#pragma pack(pop)

#endif // !__MSGHANDLER_DEF_HPP
