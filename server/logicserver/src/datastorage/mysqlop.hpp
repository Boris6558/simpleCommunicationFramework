#ifndef __MYSQL_OP_HPP_
#define __MYSQL_OP_HPP_

#include <string>
#include <cstring>
#include <mysql/mysql.h>

#include "def/basedef.hpp"
#include "def/mysqlopdef.hpp"

#define SQL MySqlOperator::Instance()

class MySqlOperator
{
public:
	MySqlOperator();
	~MySqlOperator();

	static MySqlOperator& Instance();

	bool InIt(const std::string host,const std::string user,const std::string passwd,const std::string db,uint port);
	void Free();

	bool Query(std::string sql);
	bool InsertEmptyRow(std::string table);
	bool Search(std::string table, std::string field_name, std::string conditions/*WHERE ������������*/, SqlSearchRes &out_res __ARG_OUT);
	bool Update(std::string table,std::string field_name,std::string set_data,std::string conditions/*HERE ������������*/,bool is_hex_data = true);
	bool Delete(std::string table,std::string conditions/*HERE ������������*/);

private:
	MYSQL m_data;
	MYSQL_RES* m_result;	// ��ȡ�����

};

#endif // !__MYSQL_OP_HPP_
