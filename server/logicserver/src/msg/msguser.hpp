#ifndef __MSG_USER_HPP__
#define __MSG_USER_HPP__

#include "def/basedef.hpp"
#include "def/msghandlerdef.hpp"

#pragma pack(push,4)
struct UserLoginReqCS			// 1000 ÓÃ»§µÇÂ¼ÇëÇó
{
	UserLoginReqCS()
	{
		memset(user_id, 0, sizeof(CString));
		memset(passwd, 0, sizeof(CString));
	}

	MsgHeader header;

	CString user_id;
	CString passwd;

};

#pragma pack(pop)

#endif // !__MSG_USER_HPP__
