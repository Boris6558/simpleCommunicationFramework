#include "uidtool.hpp"

#include "datastorage/mysqlop.hpp"

#include "def/mysqlopdef.hpp"
#include "def/sqltabledef.hpp"

ullong UidTool::CreatUid(std::string login_name)
{
	generated_user_id gud;

	// 先查看数据库是否有这个用户
	SqlSearchRes user_res;

	if (!SQL.Search(gud.table_name, gud.feilds[generated_user_id::FIELD_USER_ID], _F("user_name = '%s'",%login_name.c_str()), user_res))
	{
		SqlSearchRes gud_user_id, gud_offset;
		if (!SQL.Search(gud.table_name, gud.feilds[generated_user_id::FIELD_USER_ID], "user_name = 'start_id'", gud_user_id) ||
			!SQL.Search(gud.table_name, gud.feilds[generated_user_id::FIELD_OFFSET], "user_name = 'start_id'", gud_offset)
			)
		{
			return GENERATED_UID_ERROR;
		}

		int uid_offset = CastTo(int, gud_offset.data);
		ullong new_user_id = CastTo(ullong, gud_user_id.data) + uid_offset;

		SQL.InsertEmptyRow(gud.table_name);
		if (!SQL.Update(gud.table_name, gud.feilds[generated_user_id::FIELD_USER_ID], CastTo(std::string, new_user_id), _F("%s = %d", %gud.feilds[generated_user_id::FIELD_USER_ID] % 0), false) ||
			!SQL.Update(gud.table_name, gud.feilds[generated_user_id::FIELD_USER_NAME], _F("'%s'",%login_name), _F("%s = %d", %gud.feilds[generated_user_id::FIELD_USER_ID] % new_user_id), false)
			)
		{
			return GENERATED_UID_ERROR;
		}
		uid_offset += 1;
		if (!SQL.Update(gud.table_name, gud.feilds[generated_user_id::FIELD_OFFSET], CastTo(std::string, uid_offset), "user_name = 'start_id'", false))
		{
			return GENERATED_UID_ERROR;
		}


		// 返回新user_id
		return new_user_id;

	}

	
	// 如果传入user_name找到直接返回uid
	return CastTo(ullong, user_res.data);
}


