#ifndef __THREAD_MANAGER_DEF_HPP
#define __THREAD_MANAGER_DEF_HPP

#include <boost/thread.hpp>

typedef boost::promise<int>			Promise_I;
typedef boost::unique_future<int>	UniqueFuture_I;

enum RunMode
{
	RUN_MODE_JOIN,
	RUN_MODE_DETACH,
};

enum RunThread
{
	RUN_THREAD_INVALID = -1,					// 无效

	RUN_THREAD_CONNECT_TO_SRVER,				// 连接服务器
	RUN_THREAD_READ,							// 监听服务端的数据

	RUN_THREAD_MAX,
};

enum SleepMode
{
	SLEEP_SECOND,
	SLEEP_MILLSECOND,
	SLEEP_MICSECOND,
};

enum RunStatus
{
	RUN_STATUS_STOP,
	RUN_STATUS_RUNNING,
	RUN_STATUS_PAUSE,
};

#endif // !__THREAD_MANAGER_DEF_HPP
