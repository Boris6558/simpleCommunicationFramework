#ifndef __SQL_CACHE_HPP__
#define __SQL_CACHE_HPP__

#include <cstring>
#include <string>
#include <map>

#include "def/basedef.hpp"
#include "def/sqltabledef.hpp"
#include "def/mysqlopdef.hpp"

#include "mysqlop.hpp"

#define SQL_CACHE	SqlCache::Instance()
#define EMPTY_CACHE	"(NULL)"

class SqlCache
{
public:
	SqlCache();
	~SqlCache();

	static SqlCache& Instance();

	void PointToTable(std::string table_name);
	void SetCacheValue(std::string sql_keyvalue, std::string sql_feild, std::string cache_value);
	bool GetCacheValue(std::string sql_keyvalue, std::string sql_feild, std::string &ret_value __ARG_OUT);

	template<class TableStruct>// 缓存找不到从数据库找
	bool LoadDataFromMysql(TableStruct &struct_,std::string cur_table_keyvalue) // 从数据库中同步到缓存
	{
		SqlSearchRes s_res;
		if (!SQL.Search(struct_.table_name, struct_.feilds[TableStruct::FIELD_USER_ID], _F("%s = %s", %struct_.feilds[TableStruct::FIELD_USER_ID] % cur_table_keyvalue), s_res))
		{
			// 找不到

			SQL.InsertEmptyRow(struct_.table_name);
			SQL.Update(struct_.table_name, struct_.feilds[TableStruct::FIELD_USER_ID], cur_table_keyvalue, _F("%s = %s", %struct_.feilds[TableStruct::FIELD_USER_ID] %0), false);
		}
		// 同步到缓存
		for (int i = 0; i < TableStruct::FIELD_MAX; i++)
		{
			SqlSearchRes get_ret;
			SQL.Search(struct_.table_name, struct_.feilds[i], _F("%s = %s", %struct_.feilds[TableStruct::FIELD_USER_ID] % cur_table_keyvalue), get_ret);

			if (get_ret.data.compare("") == 0)
			{
				get_ret.data = EMPTY_CACHE;
			}

			this->SetCacheValue(cur_table_keyvalue, get_ret.field_name, get_ret.data);
		}

		return true;
	}

private:
	std::string m_table_name;
	std::map<std::string, std::string> m_cache_map;		// 缓存key  -> 缓存value
};
#endif // !__SQL_CACHE_HPP__
