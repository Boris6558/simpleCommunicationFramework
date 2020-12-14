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

	ServerInfo* GetServerInfo();

private:
	int InitServerInfoCfg(PTree &root);

private:
	ServerInfo info;
};

#endif // !__TCPSERVERCONFIG_HPP__
