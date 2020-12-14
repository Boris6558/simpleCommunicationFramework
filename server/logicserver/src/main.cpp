#include <iostream>

#include "dump/dump.hpp"
#include "configmanager/configmanager.hpp"
#include "network/tcpserver.hpp"
#include "network/tcpserverconfig.hpp"
#include "def/tcpserverconfigdef.hpp"
#include "msg/msghandler.hpp"

int main(int argc, char *argv)
{
	MiniDump::EnableAutoDump(true);

	// 初始化所有配置
	CONFIG_MGR.InitAllCfg();

	// 启动服务器
	TcpServerConfig *ts_cfg = CONFIG_MGR.GetTcpServerConfig();
	ServerInfo *info = NULL;
	if (ts_cfg)
	{
		info = ts_cfg->GetServerInfo();
		if (!info)
		{
			printf("TcpServerConfig error!\n");
			assert(0);
		}
	}

	IOService ios;
	TcpServer tcp_server(ios, info->port);
	MSG_HANDLER.GetCurServer(&tcp_server);
	ios.run();

	system("pause");
	return 0;
}