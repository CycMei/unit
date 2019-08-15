#ifndef __COUNTDOWNLATCH_H__
#define __COUNTDOWNLATCH_H__


#include <mutex>
#include <condition_variable>


#include "nocopyable.h"


namespace unit {


    class CountDownLatch : private NoCopyable {


    private:
        using count_t = int;

    private:
        count_t m_count;
        std::mutex m_mutex;
        std::condition_variable m_cond;



    public:
        explicit CountDownLatch(const count_t &count);
        ~CountDownLatch();

    public:

        void Wait();
        void CountDown();
        void CountDownN(const count_t &n);
        count_t GetCount();


    };


}



#endif //!__COUNTDOWNLATCH_H__