#ifndef __THREAD_DEF_HPP__
#define __THREAD_DEF_HPP__

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <boost/thread.hpp>

#define CUR_THREAD_ID GetCurrentThreadId()
	
typedef boost::thread							Thread;
typedef boost::condition_variable				ConditionVar;
typedef boost::mutex							Mutex;
typedef boost::unique_lock<Mutex>				UniqueLock;

#endif // !__THREAD_DEF_HPP__
