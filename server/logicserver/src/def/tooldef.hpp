#ifndef __TOOL_DEF_HPP__
#define __TOOL_DEF_HPP__

#include <cstring>
#include <string>

#pragma pack(push,4)

struct ProtocolPack	// 对收到的协议信息进行解包
{
	ProtocolPack()
	{
		msg_type = 0;
		msg_content = "";
	}

	int msg_type;
	std::string msg_content;
};

#pragma pack(pop)
#endif // !__TOOL_DEF_HPP__
