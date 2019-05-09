#include <iostream>
#include <thread>



#include "test_rwlock.h"



namespace example {

	TestRwlock::TestRwlock() {

	}



	TestRwlock::~TestRwlock() {

	}




	void TestRwlock::AddEle(const ele_t &ele) {
		this->PrintThreadId("AddEle lock before..... ");
		WriteGuard lock(m_lock);
		this->PrintThreadId("AddEle lock after..... ");

		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		m_vec.push_back(ele);

	}



	TestRwlock::ele_t TestRwlock::ReadEle() const {
		
		this->PrintThreadId("ReadEle lock before..... ");
		ReadGuard lock(m_lock);
		this->PrintThreadId("ReadEle lock after..... ");

		if (m_vec.empty())
			return ele_t{};

		return m_vec.back();

	}



	void TestRwlock::ContinueAdd() {

		ele_t i = 0;
		while (true) {
			this->AddEle(i++);
		}

	}


	void TestRwlock::ContinueRead() const {

		while (true) {
			this->ReadEle();
		}

	}


	void TestRwlock::PrintThreadId(const char *str) const {
		return;
		m_idmux.lock();
		std::printf(str);
		std::cout << "   tid:    " << std::this_thread::get_id() << "\n";
		m_idmux.unlock();
	}



}



namespace example {


	TestWFRWLock::TestWFRWLock() {

	}


	TestWFRWLock::~TestWFRWLock() {

	}


	void TestWFRWLock::AddEle(const ele_t &ele) {

		WriteGuard lock(m_lock);
		m_vec.push_back(ele);

	}


	TestWFRWLock::ele_t TestWFRWLock::ReadEle() const {

		ReadGuard lock(m_lock);
		if (m_vec.empty()) {
			return ele_t{};
		}

		return m_vec.back();

	}

}


namespace example {


	void test_Rwlock() {

		TestRwlock trl;

		TestRwlock::ele_t i = {};





		std::thread w_1(&TestRwlock::AddEle, &trl, i++);
		std::thread w_2(&TestRwlock::AddEle, &trl, i++);

		std::thread r_1(&TestRwlock::ReadEle, &trl);
		std::thread r_2(&TestRwlock::ReadEle, &trl);




		w_1.join();
		w_2.join();

		r_1.join();
		r_2.join();
	}



	void test_TestWFRWLock() {

		TestWFRWLock trl;

		TestWFRWLock::ele_t i = {};





		std::thread w_1(&TestWFRWLock::AddEle, &trl, i++);
		std::thread w_2(&TestWFRWLock::AddEle, &trl, i++);

		std::thread r_1(&TestWFRWLock::ReadEle, &trl);
		std::thread r_2(&TestWFRWLock::ReadEle, &trl);




		w_1.join();
		w_2.join();

		r_1.join();
		r_2.join();
	}


}