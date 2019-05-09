#include <cstdio>
#include <thread>

#include "test_spinlock.h"


namespace example {

	TestSpinLock::TestSpinLock() : 
		m_i{}
	{
		m_i = 1000;
	}

	TestSpinLock::~TestSpinLock() {

	}
	


	void TestSpinLock::ThreadA() {

		while (true) {
			SpinGuard lock(m_lock);
			//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			m_i += 1000;
			std::printf("ThreadA............ %lld \n", m_i);
		}




	}


	void TestSpinLock::ThreadB() {

		while (true) {
			SpinGuard lock(m_lock);
			//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			m_i /= 100;
			std::printf("ThreadB............  %lld \n", m_i);
		}


	}





	void SpinLockTest() {

		TestSpinLock tsl;


		std::thread t1(&TestSpinLock::ThreadA, &tsl);
		std::thread t2(&TestSpinLock::ThreadB, &tsl);

		t1.join();
		t2.join();







		//TestSpinLock tsl;


		//std::vector<std::thread> Athreads;
		//Athreads.resize(5);

		//std::vector<std::thread> Bthreads;
		//Bthreads.resize(5);

		//for (auto &c : Athreads) {
		//	c = std::thread(&TestSpinLock::ThreadA, &tsl);
		//}

		//for (auto &c : Bthreads) {
		//	c = std::thread(&TestSpinLock::ThreadB, &tsl);
		//}

		//for (int i = 0; i < 5; ++i) {
		//	Athreads[i].join();
		//	Bthreads[i].join();
		//}


	}





}