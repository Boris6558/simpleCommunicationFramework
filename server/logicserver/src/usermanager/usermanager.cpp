#include "usermanager.hpp"

#include "network/user.hpp"
#include "tool/serializeboost.hpp"

UserManager::UserManager()
{
}

UserManager::~UserManager()
{
	this->RemoveAllUser();
}

UserManager & UserManager::Instance()
{
	static UserManager um;
	return um;
}

void UserManager::AddUser(User * user)
{
	m_user_infos[user->GetUserId()] = user;

	// 从缓存获得该用户数据
}

void UserManager::RemoveUser(ullong user_id)
{
	std::map<ullong, User*>::iterator it = m_user_infos.find(user_id);
	if (it != m_user_infos.end())
	{
		delete it->second;
		it->second = NULL;
		m_user_infos.erase(it);
	}
}

void UserManager::RemoveAllUser()
{
	std::map<ullong, User*>::iterator it = m_user_infos.begin();
	while (it != m_user_infos.end())
	{
		delete it->second;
		it->second = NULL;
		it = m_user_infos.erase(it);
	}

}

const User * UserManager::GetUser(ullong user_id)
{
	std::map<ullong, User*>::iterator it = m_user_infos.find(user_id);
	if (it != m_user_infos.end())
	{
		return it->second;
	}

	return NULL;
}
