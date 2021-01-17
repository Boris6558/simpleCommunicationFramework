#ifndef __TCPSERVERCONFIG_HPP__
#define __TCPSERVERCONFIG_HPP__

#include "configop/iconfiginterface.hpp"
#include "def/tcpserverconfigdef.hpp"

class TcpServerConfig : public IConfigInterface
{
public:
	TcpServerConfig();
	virtual ~TcpServerConfig();

	virtual int Init(std::string path);

	const ServerInfo* GetServerInfo();
	const DatabaseInfo* GetDatabaseInfo();


private:
	int InitServerInfoCfg(PTree &root);
	int InitDatabaseInfoCfg(PTree &root);

private:
	ServerInfo server_info;
	DatabaseInfo db_info;
};

#endif // !__TCPSERVERCONFIG_HPP__
