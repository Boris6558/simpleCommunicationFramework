#ifndef __TOOL_DEF_HPP__
#define __TOOL_DEF_HPP__

#include <cstring>
#include <string>

#pragma pack(push,4)

struct ProtocolPack	// ���յ���Э����Ϣ���н��
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
