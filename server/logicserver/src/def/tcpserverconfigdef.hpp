#ifndef __TCPSERVERCONFIGDEF_HPP__
#define __TCPSERVERCONFIGDEF_HPP__

#include <cstring>
#include <string>

#include "basedef.hpp"

struct ServerInfo		// 服务器
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

struct DatabaseInfo		// 数据库
{
	DatabaseInfo()
	{
		this->Reset();
	}

	void Reset()
	{
		ip = "";
		user = "";
		passwd = "";
		database = "";
		port = 0;
	}
	std::string ip;
	std::string user;
	std::string passwd;
	std::string database;
	uint port;
};

#endif // !__TCPSERVERCONFIGDEF_HPP__
