#ifndef __USER_HPP__
#define __USER_HPP__

#include "def/tcpserverdef.hpp"
#include "def/basedef.hpp"

struct UserLoginReqCS;
class User
{
public:
	User(Socket &&soc);
	~User();

	void Init(UserLoginReqCS& rcs);

	void Send(std::string send_str);
	void Read();

	void Logout();

	inline std::string GetUserId()const { return m_user_id; }
	inline std::string GetIp()const { return m_soc.remote_endpoint().address().to_string(); }
	inline int GetPort()const { return m_soc.remote_endpoint().port(); }

private:
	void ReadHandler(const ErrorCode &ec,uint size);
	void SendHandler(const ErrorCode &ec, uint size);

private:
	Socket m_soc;
	char m_read_buf[READ_BUF];

	std::string m_user_id;
	std::string m_passwd;
};

#endif // !__USER_HPP__
