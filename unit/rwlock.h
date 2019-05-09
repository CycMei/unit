
#ifndef RWLOCK_H
#define RWLOCK_H

#include <condition_variable>
#include <mutex>
#include <cstdint>


#include "nocopyable.h"




/*


	实现与 c++ 11

	如果有 c++ 17，可以结合 
	std::shared_mutex
	std::shared_guard


*/



namespace unit {



	class RWLockBase {

	private:

	public:
		RWLockBase() = default;
		virtual ~RWLockBase() = default;

	public:
		virtual void RDLock() = 0;
		virtual void RDUnLock() = 0;
		virtual void WRLock() = 0;
		virtual void WRUnLock() = 0;

	};

	class RWGuardBase : public NoCopyable {

	protected:
		RWLockBase &m_lock;

	public:
		explicit RWGuardBase(RWLockBase &lock);
		virtual ~RWGuardBase() = default;

	};




}


namespace unit {

	class RWLock final : public NoCopyable, public RWLockBase {

	private:
		/*
			感觉不同的线程对同一个 mutex 加锁、解锁
			一般来讲同一个线程对一个 mutex 进行加锁和解锁
		*/
		std::mutex m_rmutex;
		std::mutex m_wmutex;
		std::uint8_t m_count;


	public:
		RWLock();
		~RWLock() = default;


	public:
		void RDLock() override;
		void RDUnLock() override;
		void WRLock() override;
		void WRUnLock() override;



	};



}






namespace unit {


	class WFWRLock : public NoCopyable, public RWLockBase {

	private:
		mutable std::mutex m_mutex;
		std::condition_variable m_con_r;
		std::condition_variable m_con_w;

	private:
		std::uint8_t m_wCount;
		std::uint8_t m_rCount;
		bool m_writed;


	public:
		WFWRLock();
		~WFWRLock() = default;

	public:
		void RDLock() override;
		void RDUnLock() override;
		void WRLock() override;
		void WRUnLock() override;


	};


}





namespace unit {


	class ReadGuard : public RWGuardBase {

	public:
		explicit ReadGuard(RWLock &lock);
		explicit ReadGuard(WFWRLock &lock);

		~ReadGuard();

	};


	class WriteGuard : public RWGuardBase {

	public:
		explicit WriteGuard(RWLock &lock);
		explicit WriteGuard(WFWRLock &lock);
		~WriteGuard();

	};



}


#endif // !RWLOCK_H
