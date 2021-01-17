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

	void AddUser(User *user);	// ��¼��ʱ��ӽ���
	void RemoveUser(ullong user_id);
	void RemoveAllUser();
	const User* GetUser(ullong user_id);

	inline uint GetOnlineUser()const{ return m_user_infos.size(); }	// ��ǰ�����û�����
	

private:
	std::map<ullong, User*> m_user_infos; // �洢����user   user_id  ->  User

};

#endif // __USER_NAMAGER_HPP__
