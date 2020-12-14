#ifndef __PROMPT_TEXT_HPP__
#define __PROMPT_TEXT_HPP__

#include "configop/iconfiginterface.hpp"
#include "def/prompttextdef.hpp"

class PromptTextConfig : public IConfigInterface
{
public:
	PromptTextConfig();
	virtual ~PromptTextConfig();

	virtual int Init(std::string path);

	inline const TipString& GetTipString()const { return m_tstring; }

private:
	int InitLoginString(PTree &root);

private:
	TipString m_tstring;
};

#endif // !__PROMPT_TEXT_HPP__
