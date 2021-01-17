#ifndef __MYSQL_OP_DEF_HPP__
#define __MYSQL_OP_DEF_HPP__

#include <string>
#include <cstring>

typedef struct SqlSearchRes	   // 数据库查找结果
{
	SqlSearchRes()
	{
		this->Reset();
	}

	void Reset()
	{
		field_name = "";
		data = "";
	}

	std::string field_name;
	std::string data;

}*P_SqlSearchRes;

#endif // !__MYSQL_OP_DEF_HPP__
