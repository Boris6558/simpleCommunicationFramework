#ifndef __TCPSERVERCONFIGDEF_HPP__
#define __TCPSERVERCONFIGDEF_HPP__

#include <cstring>
#include <string>

#include "basedef.hpp"

struct ServerInfo
{
	ServerInfo()
	{
		this->Reset();
	}

	void Reset()
	{
		ip = "";
		port = 0;
	}
	std::string ip;
	uint port;
};

#endif // !__TCPSERVERCONFIGDEF_HPP__
