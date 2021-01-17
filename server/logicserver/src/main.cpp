#include <iostream>

#include "dump/dump.hpp"
#include "configmanager/configmanager.hpp"
#include "network/tcpserver.hpp"
#include "network/tcpserverconfig.hpp"

#include "def/tcpserverconfigdef.hpp"
#include "def/sqltabledef.hpp"

#include "msg/msghandler.hpp"

#include "datastorage/mysqlop.hpp"
#include "datastorage/sqlcache.hpp"

int main(int argc, char *argv)
{
	MiniDump::EnableAutoDump(true);

	// 初始化所有配置
	CONFIG_MGR.InitAllCfg();

	TcpServerConfig *ts_cfg = CONFIG_MGR.GetTcpServerConfig();
	if (ts_cfg == NULL)
	{
		return -1;
	}

	// 连接mysql
	const DatabaseInfo *db_info = ts_cfg->GetDatabaseInfo();
	if (db_info == NULL)
	{
		printf("DatabaseInfo error!\n");
		assert(0);
	}
	if (SQL.InIt(db_info->ip, db_info->user, db_info->passwd, db_info->database, db_info->port) == false)
	{
		printf("init mysql error!\n");
		return -1;
	}

	// 启动服务器
	const ServerInfo *info = NULL;
	info = ts_cfg->GetServerInfo();
	if (!info)
	{
		printf("TcpServerConfig error!\n");
		assert(0);
	}
	IOService ios;
	TcpServer tcp_server(ios, info->port);
	MSG_HANDLER.GetCurServer(&tcp_server);
	ios.run();


	SQL.Free();
	system("pause");
	return 0;
}