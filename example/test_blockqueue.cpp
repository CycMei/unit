#include <thread>

#include "test_blockqueue.h"


namespace example {



	void TBlockQueue::Run() {




		std::thread t1([this]() -> bool {
		
			ele e;
			m_queue.Push(e);
			return true;
		
		});



		std::thread t2([this]() -> bool {

			ele e;
			m_queue.Push(e);
			return true;

		});

		std::thread t3([this]() -> bool {

			ele e;
			m_queue.Pop(e);
			return true;

		});

		t1.join();
		t2.join();
		t3.join();


	}



	void blockqueeu_test() {

		TBlockQueue tbq;
		tbq.Run();
	}


}