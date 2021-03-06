#include "tcpserverconfig.hpp"
#include "def/tcpserverconfigdef.hpp"

TcpServerConfig::TcpServerConfig()
{
}

TcpServerConfig::~TcpServerConfig()
{

}

int TcpServerConfig::Init(std::string path)
{
	LOAD_NODE("config.server_info", InitServerInfoCfg);

	return 0;
}

ServerInfo * TcpServerConfig::GetServerInfo()
{
	return &info;
}

int TcpServerConfig::InitServerInfoCfg(PTree & root)
{
	PTree::iterator it = root.begin();
	for (; it != root.end(); ++it)
	{
		PTree p_data = it->second;

		info.ip = p_data.get_child("ip").data();
		info.port = CastTo(uint, p_data.get_child("port").data());

		if (info.port <= 0 || info.port > 65535)
		{
			return -__LINE__;
		}

	}

	return 0;
}
