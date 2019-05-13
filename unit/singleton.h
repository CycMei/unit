#ifndef SINGLETON_H
#define SINGLETON_H


#include <memory>
#include <mutex>
#include <cstdio>

#include "nocopyable.h"
/*


	使用方式

	1. 
	class A {

		FRIEND_SINGLETON(A);
	
	private:
		A() {}

	public:
		~A() {}
	
	};

	Singleton<A>::Instance()




	2.
	class B : public Singleton<B> {

		FRIEND_SINGLETON(B);

	
	private:

		B() {}

	public:
		~B() {}
	
	};

	B::Instance()


*/


namespace unit {


	template <typename T>
	class Singleton : public NoCopyable {

		friend T;

	private:
		static std::shared_ptr<T> m_value;
		static std::once_flag m_flag;


	private:
		Singleton() = default;

	public:
		virtual ~Singleton() = default;
		


	public:
		static auto Instance() -> decltype(m_value);



	private:
		static void Init();



	};


	template <typename T>
	std::shared_ptr<T> Singleton<T>::m_value{ nullptr };


	template <typename T>
	std::once_flag Singleton<T>::m_flag{};


	template <typename T>
	auto Singleton<T>::Instance() -> decltype(m_value) {

		std::call_once(m_flag, &Singleton::Init);
		return m_value;

	}



	template <typename T>
	void Singleton<T>::Init() {

		printf("this_thread_id:  %d     ", std::this_thread::get_id());
		std::printf("instance init ...... \n");

		if (m_value == nullptr) {
			
			m_value = std::shared_ptr<T>(new T());
		}

	}


}


#define FRIEND_SINGLETON(C) friend class Singleton<C>;




#endif //!SINGLETON_H