#include "mysqlop.hpp"

MySqlOperator::MySqlOperator():
	m_result(NULL)
{
}

MySqlOperator::~MySqlOperator()
{
}

MySqlOperator & MySqlOperator::Instance()
{
	static MySqlOperator mo;
	return mo;
}

bool MySqlOperator::InIt(const std::string host, const std::string user, const std::string passwd, const std::string db, uint port)
{

	mysql_init(&m_data);
	if (!mysql_real_connect(&m_data, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, NULL, 0))
	{
		return false;
	}

	return true;
}

void MySqlOperator::Free()
{
	mysql_free_result(m_result);
	mysql_close(&m_data);
	mysql_library_end();
}

bool MySqlOperator::Query(std::string sql)
{
	if (mysql_real_query(&m_data, sql.c_str(), sql.size()) != 0)
	{
		return false;
	}
	return true;
}

bool MySqlOperator::InsertEmptyRow(std::string table)
{
	if (!this->Query(_F("INSERT INTO %s () VALUES ();", %table)))
	{
		return false;
	}
	return true;
}

bool MySqlOperator::Search(std::string table, std::string field_name, std::string conditions, SqlSearchRes &out_res __ARG_OUT)
{
	if (conditions.compare("") == 0)
	{
		return false;
	}

	if (!this->Query(_F("SELECT %s FROM %s WHERE %s;", %field_name %table %conditions)))
	{
		return false;
	}

	if (m_result) m_result = NULL;
	m_result = mysql_store_result(&m_data);
	if (!m_result) return false;

	std::map<std::string, std::string> m_field_to_value;					// 保存一行数据

	MYSQL_ROW m_rows = mysql_fetch_row(m_result);
	MYSQL_FIELD *field = mysql_fetch_field_direct(m_result, 0);
	if (!field || m_rows == NULL)
	{
		return false;
	}

	m_field_to_value[field->name] = m_rows[0] != NULL ? m_rows[0] : "NULL";
	out_res.field_name = field->name;
	out_res.data = m_rows[0] != NULL ? m_rows[0] : "";

	return true;
}

bool MySqlOperator::Update(std::string table, std::string field_name, std::string set_data, std::string conditions, bool is_hex_data)
{
	if (conditions.compare("") == 0)
	{
		return false;
	}

	std::string update_sql = "";

	if (is_hex_data)
	{
		update_sql = _F("UPDATE %s SET %s = HEX(%s) WHERE %s;", %table %field_name %set_data %conditions);
	} else
	{
		update_sql = _F("UPDATE %s SET %s = %s WHERE %s;", %table %field_name %set_data %conditions);
	}

	if (!this->Query(update_sql))
	{
		return false;
	}


	return true;
}

bool MySqlOperator::Delete(std::string table, std::string conditions)
{
	std::string delete_sql = "";
	if (conditions.compare("") == 0)
	{
		delete_sql = _F("DELETE FROM %s;", %table);
	} else
	{
		delete_sql = _F("DELETE FROM %s WHERE %s;", %table %conditions);
	}

	if (!this->Query(delete_sql))
	{
		return false;
	}

	return true;
}
