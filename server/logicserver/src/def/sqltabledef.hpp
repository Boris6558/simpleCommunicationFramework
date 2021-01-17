#ifndef __SQLTABLE_DEF_HPP__
#define __SQLTABLE_DEF_HPP__

#include <string>
#include <cstring>

#define DEF_TABLE(name) std::string table_name = #name;
#define DEF_FEILD(feild_name,it_enum) feilds[it_enum] = #feild_name;

struct generated_user_id
{
	enum FIELD
	{
		FIELD_USER_ID,
		FIELD_OFFSET,
		FIELD_USER_NAME,

		FIELD_MAX,
	};

	generated_user_id()
	{
		DEF_FEILD(user_id, FIELD_USER_ID);
		DEF_FEILD(offset, FIELD_OFFSET);
		DEF_FEILD(user_name, FIELD_USER_NAME);
	}

	DEF_TABLE(generated_user_id);
	std::string feilds[FIELD_MAX];
};

struct user_info
{
	enum FIELD
	{
		FIELD_ID,
		FIELD_USER_ID,
		FIELD_USER_DATA,

		FIELD_MAX,
	};

	user_info()
	{
		DEF_FEILD(id, FIELD_ID);
		DEF_FEILD(user_id, FIELD_USER_ID);
		DEF_FEILD(user_data,FIELD_USER_DATA);
	}

	DEF_TABLE(user_info);
	std::string feilds[FIELD_MAX];
};


#endif // !__SQLTABLE_DEF_HPP__
