
#include <iostream>
#include <cstdio>


#include "threadpool.h"

namespace unit {



	ThreadPool::ThreadPool(const std::string& name, const cap_t& cap, const cap_t& tasksCap) : 
		m_name{ name },
		m_runing{ false },
		m_threadsCap{ cap },
		m_tasksCap{ tasksCap }

	{

	}


	ThreadPool::ThreadPool() : 
		ThreadPool(g_default_threadpoolname, g_default_threadpoolThreadsCap, g_default_threadpoolTasksCap)
	{

	}


	ThreadPool::~ThreadPool() {

		for (auto& c : m_threads) {
			if (c.joinable()) {
				c.join();
			}
		}

	}


	void ThreadPool::Init() {

		
	}





	void ThreadPool::SetName(const std::string& name) {

	}




}

namespace unit {





	void ThreadPool::DoWork() {

		std::printf("ThreadPool::DoWork thread id: ");
		std::cout << std::this_thread::get_id();
		std::printf("\n");
	
		while (m_runing) {

			const auto task = GetTask();

			if (task) {
				task();
			}

		}

	}



	void ThreadPool::AddTask(const task_t& task) {
		std::printf("ThreadPool::AddTask ing .... \n");

		std::unique_lock<std::mutex> lock(m_mutex);

		m_cond_notfull.wait(lock, [this]()->bool {

			bool full = m_tasks.size() > 0 && m_tasks.size() >= m_tasksCap;
			return !full;


		});


		std::printf("ThreadPool::AddTask ed .... \n");
		m_tasks.push_back(std::move(task));
		m_cond_notempty.notify_one();

	}


	task_t ThreadPool::GetTask() {

		std::printf("ThreadPool::GetTask ing .... \n");

		std::unique_lock<std::mutex> lock(m_mutex);
		m_cond_notempty.wait(lock, [this]()->bool {
		
			return !m_tasks.empty();

		});

		std::printf("ThreadPool::GetTask ed .... \n");

		const auto task = m_tasks.front();
		m_tasks.pop_front();

		m_cond_notfull.notify_one();

		return task;

	}

}


namespace unit {




	void ThreadPool::Run() {


		std::printf("ThreadPool::Run m_threadsCap: %lu \n", m_threadsCap);


		m_threads.reserve(m_threadsCap);
		for (cap_t i = 0; i < m_threadsCap; ++i) {
			m_threads.push_back(std::thread(&ThreadPool::DoWork, this));
		}

		m_runing = true;


		std::printf("ThreadPool::Run ing \n");


	}


	void ThreadPool::Stop() {

	

	}

}