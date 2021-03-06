#ifndef __MSGHANDLER_DEF_HPP__
#define __MSGHANDLER_DEF_HPP__
#pragma pack(push,4)

typedef struct MsgHeader // 协议头
{
	MsgHeader()
	{
		msg_type = 0;
	}

	int msg_type;
}*P_MsgHeader;


enum MsgCode // 协议号
{
	USER_LOGIN_MSG_CS = 1000,				// 用户登录

	MSG_CODE_MAX,
};

#pragma pack(pop)
#endif // !__MSGHANDLER_DEF_HPP__
