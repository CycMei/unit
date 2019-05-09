#ifndef SPINLOCK_H
#define SPINLOCK_H


#include <atomic>



#include "nocopyable.h"

namespace unit {



	class SpinLock final : public NoCopyable {

	private:
		std::atomic_flag m_flag;


	public:
		SpinLock();
		~SpinLock();


	public:
		//SpinLock(const SpinLock &rhs) = delete;
		//SpinLock &operator=(const SpinLock &rhs) = delete;
		//SpinLock(SpinLock &&rhs) = delete;
		//SpinLock &operator=(SpinLock &&rhs) = delete;


	public:
		void Lock();
		bool TryLock();
		void UnLock();
	};



	class SpinGuard final : public NoCopyable {

	private:
		SpinLock &m_lock;

	public:
		explicit SpinGuard(SpinLock &lock);
		~SpinGuard();

	public:
		//SpinGuard(const SpinGuard &rhs) = delete;
		//SpinGuard &operator=(const SpinGuard &rhs) = delete;
		//SpinGuard(SpinGuard &&rhs) = delete;
		//SpinGuard &operator=(SpinGuard &&rhs) = delete;

	};



}


#endif //!SPINLOCK_H