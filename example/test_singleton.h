#ifndef TEST_SINGLETION_H
#define TEST_SINGLETION_H


#include "singleton.h"

namespace example {

	using unit::Singleton;


	class NoDerSing {


		FRIEND_SINGLETON(NoDerSing)

	private:
		NoDerSing() {

		}

	public:
		~NoDerSing() = default;


	public:
		void AddA() {

		}

	};



	class Sg : virtual public Singleton<Sg> {
		
		FRIEND_SINGLETON(Sg)


	private:

		Sg() {

		}

	public:
		~Sg() {

		}


	public:
		void AddB() {

		}

	};

	//class SD : public Sg {
	//public:
	//	SD() {

	//	}

	//	~SD() {

	//	}
	//};


	void test_sing();

}


#endif //!TEST_SINGLETION_H