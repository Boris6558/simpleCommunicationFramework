#ifndef __MSG_USER_HPP__
#define __MSG_USER_HPP__

#include "def/basedef.hpp"
#include "def/msghandlerdef.hpp"

#pragma pack(push,4)

struct UserLoginReqCS		// 1001 下发用户信息
{
	UserLoginReqCS()
	{
		memset(login_name,0,sizeof(CString));
		memset(login_passwd, 0, sizeof(CString));
	}
	MsgHeader header;

	CString login_name;
	CString login_passwd;

};

#pragma pack(pop)

#endif // !__MSG_USER_HPP__
