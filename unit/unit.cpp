#include <cmath>




#include "unit.h"


namespace unit {

    std::string Dec2Bin(const unsigned int &value) {

		unsigned int tmp = value;

		std::string str = "";

		while (tmp) {

			unsigned int bin = tmp % 2;
			char c = bin + '0';
			str.insert(str.begin(), c);
			tmp = tmp >> 1;
		}


		return str;

    }


	std::string Dec2BinForUint8(const std::uint8_t& value) {


		std::uint8_t tmp = value;
		std::uint8_t count = 7;

		std::string str = "";


		while (true)
		{

			auto v = static_cast<std::uint8_t>(std::pow(2, count));
			
			std::uint8_t bin = tmp >= v ? 1 : 0;

			if (tmp >= v) {
				tmp = tmp - v;
			}

			char c = bin + '0';
			str.push_back(c);

			if (count == 0) {
				break;
			}

			--count;

		}

		return str;

	}


}
