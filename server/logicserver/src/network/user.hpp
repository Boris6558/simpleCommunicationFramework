#ifndef __USER_HPP__
#define __USER_HPP__

#include "def/tcpserverdef.hpp"
#include "def/basedef.hpp"

#include "stockstruct/userstock.hpp"

struct UserLoginReqCS;
class User
{
public:
	User(Socket &&soc);
	~User();

	void Init(UserBaseInfoStock &user_once);
	inline UserBaseInfoStock& GetUserBaseInfoOnce(){ return m_stock; }

	void Send(std::string send_str);			// 发文本用【一般用来测试】
	void Send(const char *data, int send_len);
	void Read();

	void Logout();

	inline ullong GetUserId()const { return m_stock.uid; }
	inline std::string GetIp()const { return m_soc.remote_endpoint().address().to_string(); }
	inline int GetPort()const { return m_soc.remote_endpoint().port(); }

private:
	void ReadHandler(const ErrorCode &ec,uint size);
	void SendHandler(const ErrorCode &ec, uint size);

private:
	Socket m_soc;
	char m_read_buf[READ_BUFFER];
	UserBaseInfoStock m_stock;
};

#endif // !__USER_HPP__
