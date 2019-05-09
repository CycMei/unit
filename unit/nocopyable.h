#ifndef NOCOPYABLE_H
#define NOCOPYABLE_H


namespace unit {

	class NoCopyable {

	protected:
		NoCopyable() = default;
		virtual ~NoCopyable() = default;

	public:
		NoCopyable(const NoCopyable &rhs) = delete;
		NoCopyable &operator=(const NoCopyable &rhs) = delete;
		NoCopyable(NoCopyable &&rhs) = delete;
		NoCopyable &operator=(NoCopyable &&rhs) = delete;

	};

}


#endif // !NOCOPYABLE_H
