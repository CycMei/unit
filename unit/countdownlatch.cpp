#include "countdownlatch.h"


namespace unit {


    CountDownLatch::CountDownLatch(const count_t &count) :
        m_count{ count }
    {

    }


    CountDownLatch::~CountDownLatch() {

    }


    void CountDownLatch::Wait() {

        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait(lock, [this]()->bool{

            return m_count <= 0;
        });

    }


    void CountDownLatch::CountDown() {

        std::lock_guard<std::mutex> lock(m_mutex);
        if(--m_count <= 0) {
            m_cond.notify_all();
        }
    }


    void CountDownLatch::CountDownN(const count_t &n) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if(m_count -= n <= 0) {
            m_cond.notify_all();
        }
    }

    CountDownLatch::count_t CountDownLatch::GetCount() {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_count;
    }


}