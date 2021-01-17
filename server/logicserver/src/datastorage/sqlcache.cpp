#include "sqlcache.hpp"

SqlCache::SqlCache()
{
}

SqlCache::~SqlCache()
{
}

SqlCache & SqlCache::Instance()
{
	static SqlCache sc;
	return sc;
}

void SqlCache::PointToTable(std::string table_name)
{
	m_table_name = table_name;
}

void SqlCache::SetCacheValue(std::string sql_keyvalue, std::string sql_feild, std::string cache_value)
{
	std::string c_key;
	c_key = m_table_name + "::" + sql_keyvalue + "::" + sql_feild;

	m_cache_map[c_key] = cache_value;
}

bool SqlCache::GetCacheValue(std::string sql_keyvalue, std::string cache_key, std::string &ret_value __ARG_OUT)
{
	ret_value = "";
	std::string stsk;
	stsk = m_table_name + "::" + sql_keyvalue + "::" + cache_key;

	std::map<std::string, std::string>::iterator it = m_cache_map.find(stsk);
	if (it != m_cache_map.end())
	{
		ret_value = it->second;
	}

	if (ret_value.compare("") == 0)
	{
		return false;
	}

	return true;
}
