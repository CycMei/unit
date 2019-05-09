#include "rwlock.h"



namespace unit {

	RWGuardBase::RWGuardBase(RWLockBase &lock) :
		m_lock{ lock }
	{

	}


}

namespace unit {



	RWLock::RWLock() :
		m_count{}
	{

	}



	void RWLock::RDLock() {

		std::unique_lock<std::mutex> lock(m_rmutex);
		++m_count;
		if (m_count == 1) {
			m_wmutex.lock();
		}

	}


	void RWLock::RDUnLock() {

		std::unique_lock<std::mutex> lock(m_rmutex);
		--m_count;
		if (m_count == 0) {
			m_wmutex.unlock();
		}

	}


	void RWLock::WRLock() {

		m_wmutex.lock();

	}



	void RWLock::WRUnLock() {

		m_wmutex.unlock();

	}

}







namespace unit {


	WFWRLock::WFWRLock() : 
		m_wCount{},
		m_rCount{},
		m_writed{ false }
	{

	}


	void WFWRLock::RDLock() {

		std::unique_lock<std::mutex> lock(m_mutex);

		m_con_r.wait(lock, [this]() -> bool {
			return this->m_wCount == 0;
		});

		++m_rCount;


	}


	void WFWRLock::RDUnLock() {

		std::unique_lock<std::mutex> lock(m_mutex);
		
		if (--m_rCount == 0 && m_wCount > 0) {
			m_con_w.notify_one();
		}

	}


	void WFWRLock::WRLock() {

		std::unique_lock<std::mutex> lock(m_mutex);
		
		++m_wCount;

		m_con_w.wait(lock, [this]() -> bool {
			
			return this->m_rCount == 0 && !m_writed;

		});

		m_writed = true;


	}



	void WFWRLock::WRUnLock() {

		std::unique_lock<std::mutex> lock(m_mutex);
		
		if (--m_wCount == 0) {
			m_con_r.notify_all();
		}
		else {
			m_con_w.notify_one();
		}

		m_writed = false;

	}
}







namespace unit {


	ReadGuard::ReadGuard(RWLock &lock) :
		RWGuardBase{ lock }
	{
		m_lock.RDLock();

	}


	ReadGuard::ReadGuard(WFWRLock &lock) :
		RWGuardBase{ lock }
	{
		m_lock.RDLock();
	}


	ReadGuard::~ReadGuard() {

		m_lock.RDUnLock();

	}



}




namespace unit {


	WriteGuard::WriteGuard(RWLock &lock) :
		RWGuardBase{ lock }
	{
		m_lock.WRLock();

	}


	WriteGuard::WriteGuard(WFWRLock &lock) :
		RWGuardBase{ lock }
	{
		m_lock.WRLock();
	}


	WriteGuard::~WriteGuard() {

		m_lock.WRUnLock();

	}



}