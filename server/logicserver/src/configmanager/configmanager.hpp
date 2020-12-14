#ifndef __CONFIG_MANAGER_HPP
#define __CONFIG_MANAGER_HPP

#include "configop/iconfiginterface.hpp"

#define DEF_TYPE_ENUM(class_name) CONFIG_TYPE_##class_name

#define GET_CONFIG(class_name)\
	class_name* Get##class_name(){ return (class_name*)x_mod[DEF_TYPE_ENUM(class_name)];}


#define CONFIG_MGR ConfigManager::Instance()


class TcpServerConfig;

enum ConfigTypes
{
	DEF_TYPE_ENUM(TcpServerConfig),
	
	CONFIG_TYPE_MAX,
};


class ConfigManager
{
public:
	ConfigManager();
	virtual ~ConfigManager();

	static ConfigManager& Instance();

	int InitAllCfg();

	GET_CONFIG(TcpServerConfig)


	BOOST_STATIC_ASSERT(CONFIG_TYPE_MAX == 1);	// 这里提示是为了不要忘记加配置时这里也要加
private:
	IConfigInterface *x_mod[CONFIG_TYPE_MAX];
	std::string cfg_path[CONFIG_TYPE_MAX];
};

#endif // !__CONFIG_MANAGER_HPP
