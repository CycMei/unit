
#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H


#include <cstdio>
#include <memory>
#include <mutex>
#include <deque>
#include <condition_variable>


#include "nocopyable.h"

namespace unit {




	template <typename T>
	class BlockingQueue final : public NoCopyable {


	private:
		mutable std::mutex m_mutex;
		std::deque<T> m_data;
		std::condition_variable m_cond;


	public:
		BlockingQueue() = default;
		~BlockingQueue() = default;


	public:

		void Push(const T &val) &;
		std::shared_ptr<T> Pop() const &;
		void Pop(T &val) &;
		bool Empty() const &;


	};

}


namespace unit {

	template <typename T>
	void BlockingQueue<T>::Push(const T &val) & {

		std::lock_guard<std::mutex> lock(m_mutex);
		std::printf("BlockingQueue push...... \n");
		m_data.push_back(val);
		m_cond.notify_one();

	}

	template <typename T>
	std::shared_ptr<T> BlockingQueue<T>::Pop() const & {

		std::unique_lock<std::mutex> lock(m_mutex);
		m_cond.wait(lock, [this]() -> bool {
			return !(m_data.empty());
		});

		std::printf("BlockingQueue Pop...... \n");
		std::shared_ptr<T> res = std::make_shared<T>(m_data.front());
		m_data.pop_front();
		return res;

	}



	template <typename T>
	void BlockingQueue<T>::Pop(T &val) & {

		std::unique_lock<std::mutex> lock(m_mutex);
		m_cond.wait(lock, [this]() -> bool {
			return !(m_data.empty());
		});

		std::printf("BlockingQueue Pop val...... \n");
		val = m_data.front();
		m_data.pop_front();
	}

	template <typename T>
	bool BlockingQueue<T>::Empty() const & {

		std::lock_guard<std::mutex> lock(m_mutex);
		return m_data.empty();

	}


}



#endif //!BLOCKINGQUEUE_H