#ifndef __MSGHANDLER_HPP__
#define __MSGHANDLER_HPP__

#include <cstring>
#include <string>

#include "def/basedef.hpp"


/**
 * Э��ת������ʽ[msghead_type##send_content]-- ����
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
