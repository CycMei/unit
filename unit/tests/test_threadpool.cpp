#include <chrono>
#include <thread>

#include "threadpool.h"


void test_func() {

	std::printf("0-0000000000000000000 ...............  \n");

}



class A {

public:
	void operator()() {

	}

	A(const A& rhs) = delete;

};

void skkd() {

	A a;
	std::function<void()> ss = a;


}



void test_threadpool() {

	skkd();

	using namespace unit;

	
	ThreadPool tp(std::string("cyc"), 1, 2);


	tp.AddTask(test_func);
	std::thread th([&tp]()->void {

		std::printf("a....... \n");
		tp.AddTask(test_func);
		std::printf("b....... \n");

		});



	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::printf("wake up11.. \n");


	tp.Run();


	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	std::printf("wake up.. \n");


	th.join();

}

int main() {

	test_threadpool();

	return 0;
}