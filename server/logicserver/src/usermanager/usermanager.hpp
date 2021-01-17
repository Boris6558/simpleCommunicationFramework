#ifndef __USER_NAMAGER_HPP__
#define __USER_NAMAGER_HPP__

#include <map>
#include "def/basedef.hpp"
#include "stockstruct/userstock.hpp"

#define USER_MGR UserManager::Instance()

class User;
class UserManager
{
public:
	UserManager();
	~UserManager();

	static UserManager& Instance();

	void AddUser(User *user);	// 登录的时候加进来
	void RemoveUser(ullong user_id);
	void RemoveAllUser();
	const User* GetUser(ullong user_id);

	inline uint GetOnlineUser()const{ return m_user_infos.size(); }	// 当前在线用户数量
	

private:
	std::map<ullong, User*> m_user_infos; // 存储所有user   user_id  ->  User

};

#endif // __USER_NAMAGER_HPP__
