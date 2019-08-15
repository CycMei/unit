#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__




#include <vector>
#include <thread>
#include <string>
#include <functional>
#include <deque>
#include <condition_variable>
#include <mutex>


#include "nocopyable.h"



namespace unit {

	using cap_t = std::size_t;


	const static std::string g_default_threadpoolname = "cyc";
	const static cap_t g_default_threadpoolThreadsCap = 5;
	const static cap_t g_default_threadpoolTasksCap = 10;



	using threads_t = std::vector<std::thread>;
	using task_t = std::function<void()>;
	using tasks_t = std::deque<task_t>;



	class ThreadPool : private NoCopyable {

	private:
		std::string m_name;
		bool m_runing;

	private:
		cap_t m_threadsCap;
		threads_t m_threads;


	private:
		cap_t m_tasksCap;
		mutable std::mutex m_mutex;
		std::condition_variable m_cond_notfull;
		std::condition_variable m_cond_notempty;
		tasks_t m_tasks;


	public:
		ThreadPool();
		ThreadPool(const std::string &name, const cap_t& cap, const cap_t& tasksCap);
		~ThreadPool();



	private:
		void Init();

	public:
		void SetName(const std::string &name);
		
	private:
		void DoWork();
		task_t GetTask();
	public:

		void AddTask(const task_t &task);

	public:
		void Run();
		void Stop();



	};


}



#endif //!__THREADPOOL_H__