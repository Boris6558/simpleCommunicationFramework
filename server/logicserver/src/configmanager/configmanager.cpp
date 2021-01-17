#include "configmanager.hpp"

#include "network/tcpserverconfig.hpp"

#define NEW_CONFIG(class_name)	x_mod[DEF_TYPE_ENUM(class_name)] = new class_name

#define DELETE_CONFIG(class_name)					\
	delete x_mod[DEF_TYPE_ENUM(class_name)];		\
	x_mod[DEF_TYPE_ENUM(class_name)] = NULL

ConfigManager::ConfigManager()
{
	NEW_CONFIG(TcpServerConfig);
	

	// 路径设置
	cfg_path[DEF_TYPE_ENUM(TcpServerConfig)] = "server_config/network.xml";


	for (int i = 0; i < CONFIG_TYPE_MAX; ++i)
	{
		if (x_mod[i] == NULL)
		{
			printf("(%s: %d)error[%s]: x_mod[%d] is NULL\n", __FILE__, __LINE__, __FUNCTION__, i);
			BOOST_ASSERT(0); // 不应该
		}
	}

	BOOST_STATIC_ASSERT(CONFIG_TYPE_MAX == 1);
}

ConfigManager::~ConfigManager()
{
	for (int i = 0; i < CONFIG_TYPE_MAX; ++i)
	{
		delete x_mod[i];
		x_mod[i] = NULL;
	}
}

ConfigManager & ConfigManager::Instance()
{
	static ConfigManager cm;
	return cm;
}

int ConfigManager::InitAllCfg()
{
	for (int i = 0; i < CONFIG_TYPE_MAX; ++i)
	{
		if (x_mod[i]->Init(cfg_path[i]) != 0)
		{
			printf("(%s: %d)error[%s]: config path error!! at [%s]\n", __FILE__, __LINE__, __FUNCTION__, cfg_path[i].c_str());
			return -i;
		}

	}

	return 0;
}
