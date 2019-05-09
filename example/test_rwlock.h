#ifndef TEST_RWLOCK_H
#define TEST_RWLOCK_H



#include <vector>


#include "rwlock.h"


namespace example {

	using namespace unit;


	class TestRwlock {

	public:
		using ele_t = int;
		using ctr_t = std::vector<ele_t>;

	protected:
		ctr_t m_vec;


	private:
		mutable RWLock m_lock;
		mutable std::mutex m_idmux;

	public:
		TestRwlock();
		~TestRwlock();

	public:
		TestRwlock(const TestRwlock &rhs) = delete;
		TestRwlock &operator=(const TestRwlock &rhs) = delete;
		TestRwlock(TestRwlock &&rhs) = delete;
		TestRwlock &operator=(TestRwlock &&rhs) = delete;


	public:
		void AddEle(const ele_t &ele);
		ele_t ReadEle() const;
		void ContinueAdd();
		void ContinueRead() const;
		void PrintThreadId(const char *str) const;



	};


	void test_Rwlock();



	class TestWFRWLock {


	public:
		using ele_t = int;
		using ctr_t = std::vector<ele_t>;

	protected:
		ctr_t m_vec;

	private:
		mutable WFWRLock m_lock;

	public:
		TestWFRWLock();
		~TestWFRWLock();

	public:
		void AddEle(const ele_t &ele);
		ele_t ReadEle() const;

	};


	void test_TestWFRWLock();




}



#endif // !TEST_RWLOCK_H
