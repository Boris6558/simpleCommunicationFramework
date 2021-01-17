#ifndef __THREAD_MANAGER_HPP__
#define __THREAD_MANAGER_HPP__

#include <QObject>
#include <boost/function.hpp>

#include "def/threadmanagerdef.hpp"
#include "def/threaddef.hpp"
#include "def/basedef.hpp"

#define THREAD_MGR ThreadManager::Instance()

class ThreadManager :public QObject
{
	Q_OBJECT

public:
	ThreadManager();
	~ThreadManager();

	static ThreadManager& Instance();

	void Start(boost::function<void(void)> v_v_fun, int run_thread, int run_mode = RUN_MODE_JOIN);
	void Stop(int run_thread);
	void StopAll();
	void Pause(int run_thread);
	void Resume(int run_thread);
	void WaitFlag(int run_thread);		// 线程里需要挂起和唤醒线程的，可以先调用此函数，然后才可以用Pause和Resume控制
	bool StopFlag(int run_thread);		// 循环调用的，while里的true用这个
	void Sleep(ullong time, int sleep_mode = SLEEP_SECOND);
	inline int GetRunStatus(int run_thread)const {return m_thread_status[run_thread];}
	void SetRunStatus(int run_thread, int status);
	inline Mutex& GetMutex(int mutex_type) { return m_muteies[mutex_type]; }

private:
	Thread *m_threads[RUN_THREAD_MAX];
	int m_thread_status[RUN_THREAD_MAX];

	bool m_is_pause[RUN_THREAD_MAX];
	bool m_is_stop[RUN_THREAD_MAX];
	ConditionVar m_cvs[RUN_THREAD_MAX];
	Mutex m_muteies[MUTEX_TYPE_MAX];

};

#endif // !__THREAD_MANAGER_HPP__
