#ifndef __USER_STOCK__
#define __USER_STOCK__

#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>

#include "def/basedef.hpp"

#pragma pack(push,4)

typedef struct UserBaseInfoStock
{
	UserBaseInfoStock()
	{
		this->Reset();
	}

	void Reset()
	{
		uid = 0;
		memset(login_name, 0, sizeof(CString));
		memset(login_passwd, 0, sizeof(CString));
	}

	ullong uid;
	CString login_name;
	CString login_passwd;
}*P_UserBaseInfoStock;
typedef char UserBaseInfoStockHex[sizeof(UserBaseInfoStock)];
BOOST_STATIC_ASSERT(sizeof(UserBaseInfoStockHex) < 512);

#pragma pack(pop)

#endif // !__USER_STOCK__
