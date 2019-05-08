#include "spinlock.h"


namespace unit {


	SpinLock::SpinLock() :
		m_flag{ ATOMIC_FLAG_INIT }
	{

	}




	SpinLock::~SpinLock() {

	}





	void SpinLock::Lock() {

		while (!this->TryLock()) {
			;
		}

	}


	bool SpinLock::TryLock() {

		return !m_flag.test_and_set(std::memory_order_acquire);

	}



	void SpinLock::UnLock() {

		m_flag.clear(std::memory_order_release);

	}


}



namespace unit {

	SpinGuard::SpinGuard(SpinLock &lock) :
		m_lock{ lock }
	{
		
		m_lock.Lock();

	}


	SpinGuard::~SpinGuard() {

		m_lock.UnLock();

	}

}