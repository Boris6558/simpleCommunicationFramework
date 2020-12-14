#ifndef __MSGHANDLER_DEF_HPP
#define __MSGHANDLER_DEF_HPP

#include <cstring>
#include <string>

#include "def/basedef.hpp"

struct MsgHeader // 协议头
{
	MsgHeader()
	{
		msg_type = 0;
	}

	int msg_type;
};

enum MsgCode  // 协议号
{
	MSG_CODE_START = 1000,

	USER_LOGIN_MSG_CS = MSG_CODE_START,				// 用户登录
	SEND_MEESAGE_MSG_CS = 1001,						// 发送消息

	MSG_CODE_MAX,
};


#endif // !__MSGHANDLER_DEF_HPP
