#ifndef __MSGHANDLER_HPP__
#define __MSGHANDLER_HPP__

#include <cstring>
#include <string>

#include "def/basedef.hpp"


/**
 * 协议转发，格式[msghead_type##send_content]-- 弃用
 */


#define MSG_HANDLER MsgHandler::Instance()

class MsgHandler
{
public:
	MsgHandler();
	~MsgHandler();

	static MsgHandler& Instance();

	void ReadFromServer(const char *data,uint size);

private:
};

#endif // !__MSGHANDLER_HPP__
