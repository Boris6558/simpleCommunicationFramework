#include "threadmanager.hpp"

ThreadManager::ThreadManager()
{
	for (int i = 0; i < RUN_THREAD_MAX; i++)
	{
		m_threads[i] = NULL;
		m_is_pause[i] = false;
		m_is_stop[i] = false;
	}

	memset(m_thread_status, RUN_STATUS_STOP, sizeof(m_thread_status));
}

ThreadManager::~ThreadManager()
{
	for (int i = 0; i < RUN_THREAD_MAX; i++)
	{
		delete m_threads[i];
		m_threads[i] = NULL;

		m_is_pause[i] = false;
		m_is_stop[i] = false;
	}
}

ThreadManager & ThreadManager::Instance()
{
	static ThreadManager tm;
	return tm;
}

void ThreadManager::Start(boost::function<void(void)> v_v_fun, int run_thread, int run_mode)
{
	if (run_thread <= RUN_THREAD_INVALID || run_thread >= RUN_THREAD_MAX)
	{
		return;
	}

	if (m_threads[run_thread])
	{
		return;
	}

	m_threads[run_thread] = new Thread(v_v_fun);
	if (run_mode == RUN_MODE_JOIN)
	{
		m_threads[run_thread]->join();
	} 
	else
	{
		m_threads[run_thread]->detach();
	}

	m_is_stop[run_thread] = true;
	this->SetRunStatus(run_thread, RUN_STATUS_RUNNING);

}

void ThreadManager::Stop(int run_thread)
{
	if (run_thread <= RUN_THREAD_INVALID || run_thread >= RUN_THREAD_MAX)
	{
		return;
	}

	if (!m_threads[run_thread])
	{
		return;
	}

	if (m_is_stop[run_thread])
	{
		m_is_stop[run_thread] = false;
	}

	delete m_threads[run_thread];
	m_threads[run_thread] = NULL;

	this->SetRunStatus(run_thread, RUN_STATUS_STOP);

}

void ThreadManager::StopAll()
{
	for (int i = 0; i < RUN_THREAD_MAX; i++)
	{
		this->Stop(i);
	}
}

void ThreadManager::Pause(int run_thread)
{
	m_is_pause[run_thread] = true;
	this->SetRunStatus(run_thread, RUN_STATUS_PAUSE);
}

void ThreadManager::Resume(int run_thread)
{
	m_is_pause[run_thread] = false;
	m_cvs[run_thread].notify_all();
	this->SetRunStatus(run_thread,RUN_STATUS_RUNNING);
}

void ThreadManager::WaitFlag(int run_thread)
{
	Mutex mut;
	UniqueLock lock(mut);
	m_cvs[run_thread].wait(lock,
		[&]()mutable -> bool
	{
		return !m_is_pause[run_thread];
	}
	);
}

bool ThreadManager::StopFlag(int run_thread)
{
	return m_is_stop[run_thread];
}

void ThreadManager::Sleep(ullong time, int sleep_mode)
{
	switch (sleep_mode)
	{
	case SLEEP_SECOND:
		boost::this_thread::sleep_for(boost::chrono::seconds(time));
		break;

	case SLEEP_MILLSECOND:
		boost::this_thread::sleep_for(boost::chrono::milliseconds(time));
		break;

	case SLEEP_MICSECOND:
		boost::this_thread::sleep_for(boost::chrono::microseconds(time));
		break;
	}
}

void ThreadManager::SetRunStatus(int run_thread, int status)
{
	if (status < RUN_STATUS_STOP || status > RUN_STATUS_PAUSE)
	{
		return;
	}

	m_thread_status[run_thread] = status;
}


