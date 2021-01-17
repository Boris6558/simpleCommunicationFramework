#ifndef __UID_TOOL_HPP_
#define __UID_TOOL_HPP_

#include <boost/noncopyable.hpp>
#include <cstring>
#include <string>

#include "def/basedef.hpp"
#include "def/uidtooldef.hpp"

class UidTool : public boost::noncopyable
{
public:
	static ullong CreatUid(std::string login_name);
};

#endif // !__UID_TOOL_HPP_
