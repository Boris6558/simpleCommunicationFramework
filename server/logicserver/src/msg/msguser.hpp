#ifndef __MSG_USER_HPP__
#define __MSG_USER_HPP__

#include "def/basedef.hpp"
#include "def/msghandlerdef.hpp"

#pragma pack(push,4)
typedef struct UserLoginReqCS			// 1000 ÓÃ»§µÇÂ¼ÇëÇó
{
	UserLoginReqCS()
	{
		memset(login_name, 0, sizeof(CString));
		memset(login_passwd, 0, sizeof(CString));
	}

	MsgHeader header;

	CString login_name;
	CString login_passwd;

}*P_UserLoginReqCS;

#pragma pack(pop)

#endif // !__MSG_USER_HPP__
