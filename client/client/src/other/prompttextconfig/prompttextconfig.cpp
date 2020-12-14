#include "prompttextconfig.hpp"

PromptTextConfig::PromptTextConfig()
{
}

PromptTextConfig::~PromptTextConfig()
{
}

int PromptTextConfig::Init(std::string path)
{
	LOAD_NODE("config.tip_string", InitLoginString);

	return 0;
}

int PromptTextConfig::InitLoginString(PTree & root)
{
	PTree::iterator it = root.begin();
	for (; it != root.end(); ++it)
	{
		PTree p_data = it->second;


		m_tstring.g_string[TipString::G_MAIN_WIDGET_TITLE] = p_data.get_child("main_widget_title").data();
		m_tstring.g_string[TipString::G_LINK_TIMEOUT_TIP] = p_data.get_child("link_timeout_tip").data();
		m_tstring.g_string[TipString::G_LINK_TIMEOUT_CONTENT] = p_data.get_child("link_timeout_content").data();
		m_tstring.g_string[TipString::G_LOGIN_EMPTY_TXT_TIP] = p_data.get_child("login_empty_txt_tip").data();
		m_tstring.g_string[TipString::G_LOGIN_EMPTY_TXT_CONTENT] = p_data.get_child("login_empty_txt_content").data();
		m_tstring.g_string[TipString::G_LINK_STATUS_ING] = p_data.get_child("link_status_ing").data();

		if (m_tstring.g_string[TipString::G_MAIN_WIDGET_TITLE].compare("") == 0 ||
			m_tstring.g_string[TipString::G_LINK_TIMEOUT_TIP].compare("") == 0 ||
			m_tstring.g_string[TipString::G_LINK_TIMEOUT_CONTENT].compare("") == 0 ||
			m_tstring.g_string[TipString::G_LOGIN_EMPTY_TXT_TIP].compare("") == 0 ||
			m_tstring.g_string[TipString::G_LOGIN_EMPTY_TXT_CONTENT].compare("") == 0 ||
			m_tstring.g_string[TipString::G_LINK_STATUS_ING].compare("") == 0
			)
		{
			return -__LINE__;
		}
	}

	return 0;
}
