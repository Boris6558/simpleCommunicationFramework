#include "msghandler.hpp"

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

void MsgHandler::ReadFromServer(std::string data)
{
	printf("message: %s\n", data.data());
}

void MsgHandler::SendToServer(std::string &req_str __ARG_OUT, int req_type)
{
	std::string send_cont = req_str;

	req_str = _F("%d##%s",%req_type %send_cont.data());
}
