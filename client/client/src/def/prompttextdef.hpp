#ifndef __PROMPT_TEXT_DEF_HPP__
#define __PROMPT_TEXT_DEF_HPP__

#include <cstring>
#include <string.h>

struct TipString
{
	enum Str
	{
	G_MAIN_WIDGET_TITLE,
	G_LINK_TIMEOUT_TIP,
	G_LINK_TIMEOUT_CONTENT,
	G_LOGIN_EMPTY_TXT_TIP,
	G_LOGIN_EMPTY_TXT_CONTENT,
	G_LINK_STATUS_ING,

	G_STR_MAX,

	};

	TipString()
	{
		this->Reset();
	}
	void Reset()
	{
		for (int i = 0; i < G_STR_MAX; i++)
		{
			g_string[i] = "";
		}
	}

	std::string g_string[G_STR_MAX];
};





#endif // !__PROMPT_TEXT_DEF_HPP__
