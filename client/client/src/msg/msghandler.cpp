#include "msghandler.hpp"

#include "network/tcpclient.hpp"

MsgHandler::MsgHandler()
{
}

MsgHandler::~MsgHandler()
{
}

MsgHandler & MsgHandler::Instance()
{
	static MsgHandler mh;
	return mh;
}

void MsgHandler::ReadFromServer(const char *data, uint size)
{
	printf("message: read size[%d],read data[%s]\n", size, data);
}
