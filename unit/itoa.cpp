

#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cassert>



#include "itoa.h"


namespace unit {


namespace detail {


void test1 () {



	int ni3 = -3;
	int i3 = 3;
	int i2 = 2;
	int i1 = i3 / i2;
	int ni1 = ni3 / i2;
	assert(i1 == 1);
	assert(ni1 == -1);

}


void test2() {



	int i21 = 21;
	int ni5 = -5;
	int r = i21 % ni5;
	assert(r == 1);



	int ni21 = -21;
	int ni8 = -8;
	int s = ni21 % ni8;
	assert(s == -5);


}



void test3() {



	unsigned char c = -32;
	assert(c == 224);


	//演示计算过程
	double d256 = 256;
	double d32 = -32;
	double r = std::floor(d32 / d256);
	std::printf("r:  %d\n", (int)r);
	int mr = d32 - (r * d256);
	assert(mr == 224);



}




}





void m_itoa(char *buf, int value) {

	if(buf == NULL){
		return;
	}

	const static char digits[] = {
		'9', '8', '7', '6', '5', '4', '3', '2', '1',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
	};
	const static char *zero = digits + 9;

	int i = value;
	char *p = buf;


	do{

		//这里的取模应该在求商的时候向零取整才能正常工作
		//不同的编译器可能不同
		int lsd = i % 10;
		i /= 10;

		//zero[lsd] 等同于 *(zero + lsd)，参考数组与指针
		*p++ = zero[lsd];

	}while(i != 0);

	if(value < 0) {
		*p++ = '-';
	}

	*p = '\0';


	std::printf("value:   %d\n", value);
	std::printf("res  buf:     %s\n", buf);


	if(std::strlen(buf) <= 1) {
		return;
	}

	// std::reverse(buf, p);
	// std::printf("buf:     %s\n", buf);


	//反转 buf
	char *beg = buf;
	char *end = p - 1;

	while(true) {
		char c = *beg;
		*beg++ = *end;
		*end-- = c;
		if(beg >= end){
			break;
		}
	}


	std::printf("buf:     %s\n", buf);



}

}