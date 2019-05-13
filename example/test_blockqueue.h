#ifndef TEST_BLOCKQUEUE_H
#define TEST_BLOCKQUEUE_H


#include "blockingqueue.h"

namespace example {

	using unit::BlockingQueue;
	using unit::NoCopyable;



	namespace detail {
		
		class ele {

		};
	}

	using detail::ele;

	class TBlockQueue final : public NoCopyable {

	private:
		BlockingQueue<ele> m_queue;

	public:

	public:
		TBlockQueue() = default;
		~TBlockQueue() = default;

	public:
		void Run();

	};


	void blockqueeu_test();

}

#endif // !TEST_BLOCKQUEUE_H
