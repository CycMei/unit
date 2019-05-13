#include <vector>

#include "test_singleton.h"


namespace example {

	void test_sing() {




		using unit::Singleton;
		std::vector<std::thread> threads;

		for (unsigned int i = 0; i < std::thread::hardware_concurrency() * 2; ++i) {
			std::thread t1(&Singleton<NoDerSing>::Instance);
			threads.push_back(std::move(t1));
		}

		
		for (auto &c : threads) {
			c.join();
		}



		//Sg::Instance()->AddB();


	}


}