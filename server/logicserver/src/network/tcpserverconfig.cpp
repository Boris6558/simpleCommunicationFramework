#include "tcpserverconfig.hpp"

TcpServerConfig::TcpServerConfig()
{
}

TcpServerConfig::~TcpServerConfig()
{
}

int TcpServerConfig::Init(std::string path)
{
	LOAD_NODE("config.server_info", InitServerInfoCfg);
	LOAD_NODE("config.db_info", InitDatabaseInfoCfg);

	return 0;
}

const ServerInfo * TcpServerConfig::GetServerInfo()
{
	return &server_info;
}

const DatabaseInfo * TcpServerConfig::GetDatabaseInfo()
{
	return &db_info;
}

int TcpServerConfig::InitServerInfoCfg(PTree & root)
{
	PTree::iterator it = root.begin();
	for (; it != root.end(); ++it)
	{
		PTree p_data = it->second;

		server_info.ip = p_data.get_child("ip").data();
		server_info.port = CastTo(uint, p_data.get_child("port").data());
	}

	return 0;
}

int TcpServerConfig::InitDatabaseInfoCfg(PTree & root)
{
	PTree::iterator it = root.begin();
	for (; it != root.end(); ++it)
	{
		PTree p_data = it->second;

		db_info.ip = p_data.get_child("ip").data();
		db_info.user = p_data.get_child("user").data();
		db_info.passwd = p_data.get_child("passwd").data();
		db_info.database = p_data.get_child("database").data();
		db_info.port = CastTo(uint, p_data.get_child("port").data());
	}
	return 0;
}
