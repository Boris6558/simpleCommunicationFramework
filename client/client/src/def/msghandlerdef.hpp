#ifndef __MSGHANDLER_DEF_HPP__
#define __MSGHANDLER_DEF_HPP__
#pragma pack(push,4)

typedef struct MsgHeader // Э��ͷ
{
	MsgHeader()
	{
		msg_type = 0;
	}

	int msg_type;
}*P_MsgHeader;


enum MsgCode // Э���
{
	USER_LOGIN_MSG_CS = 1000,				// �û���¼

	MSG_CODE_MAX,
};

#pragma pack(pop)
#endif // !__MSGHANDLER_DEF_HPP__
