#ifndef TEST_SPINLOCK_H
#define TEST_SPINLOCK_H



#include "spinlock.h"

namespace example {


	using namespace unit;


	class TestSpinLock {

	private:
		long long m_i;
		SpinLock m_lock;

	public:
		TestSpinLock();
		~TestSpinLock();

	public:
		TestSpinLock(const TestSpinLock &rhs) = delete;
		TestSpinLock &operator=(const TestSpinLock &rhs) = delete;
		TestSpinLock(TestSpinLock &&rhs) = delete;
		TestSpinLock &operator=(TestSpinLock &&rhs) = delete;


	public:
		void ThreadA();
		void ThreadB();


	};


	void SpinLockTest();

}



#endif //!TEST_SPINLOCK_H