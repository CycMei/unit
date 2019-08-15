#include <thread>
#include <mutex>
#include <cstdio>
#include <chrono>



#include "countdownlatch.h"

using namespace unit;


class TestCdl {

private:
    CountDownLatch m_cdl;
    std::thread m_thread;


public:
    explicit TestCdl(int count) : m_cdl{count} {

    }

    ~TestCdl() {
        std::printf("~TestCdl() \n");
        m_thread.join();
    }

private:

    void CountDown() {

        std::printf("CountDown ing... \n");

        while(true) {
            m_cdl.CountDown();
            std::printf("count down ing %d \n", m_cdl.GetCount());

            if(m_cdl.GetCount() <= 0) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        }

    }

public:

    void Start() {

        m_thread = std::thread(&TestCdl::CountDown, this);


        std::printf("Start... begin \n");
        m_cdl.Wait();
        std::printf("Start... end \n");

    }


};



void test_countdownlatch() {


    TestCdl tcdl(10);
    std::printf("aaaaaaaaaa.. \n");
    tcdl.Start();



}


int main() {


    test_countdownlatch();
    return 0;
}