#ifndef __UNIT_ITOA_H__
#define __UNIT_ITOA_H__






/*


向上取整，向正无穷取整
eg： 2.5 -> 3，-2.5 -> -2


向下取整，向负无穷取整
eg： 2.5 -> 2, -2.5 -> -3


向零取整，直接切除小数部分
eg： 2.5 -> 2，-2.5 -> -2





对于整型数a，b来说，取模运算或者求余运算的方法都是：
1.求整数商： 是向上取整还是向下取整还是向零取整？
	c = a / b
2.计算模或者余数：
	r = a - c * b

*/

namespace unit {


namespace detail {


	/*
	
	The quotient is rounded in implementation-defined direction.(until C++11)
	The quotient is truncated towards zero (fractional part is discarded).(since C++11)
	商在实现定义的方向上舍入。（直到C ++ 11）
	商被截断为零（丢弃小数部分）。（从C ++ 11开始）


	c++11
	运算符： /
	结果向零取整

	对于整数 m，n
	-m 不应该溢出，也就是 -m < 0，如果溢出 -m 就变为了正数
	(-m) / n = -(m / n)
	m / (-n) = -(m / n)

	*/
void test1 ();















	/*

	Note: Until C++11, 
	if one or both operands to binary operator % were negative, 
	the sign of the remainder was implementation-defined, 
	as it depends on the rounding direction of integer division. 
	The function std::div provided well-defined behavior in that case.

	注意：在C ++ 11之前，如果二元运算符％的一个或两个操作数都是负数，则余数的符号是实现定义的，因为它取决于整数除法的舍入方向。 
	在这种情况下，函数std :: div提供了明确定义的行为。


	c++11
	运算符： %
	对于整数 m，n
	m % n 的结果的符号应该和 m 一样
	其实就是在求商的时候，以那种方式取整导致的，c++11 就是 test1 这个函数

	m % (-n) = m % n
	(-m) % n = -(m % n)

	*/

void test2();






















	/*

	c++：一个类型转换
	当给一个无符号类型赋予负数时：
	eg：
	
	unsigned char 
	最大值为： 255，
	表示总数为： 256，也就是： 2^8
	当赋给它的值 < 0 时
	结果为：该值取模 256
	但是：此时取模过程当中的商应该是向下取整这种情况


	有一种简单得到结果的方法： 改值加上最大表示数


	*/
void test3();

}


void m_itoa(char *buf, int value);



}



#endif //!__UNIT_ITOA_H__
