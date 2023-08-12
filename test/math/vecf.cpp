#include <iostream>
#include "vecf.hpp"

namespace math {
	vecf::vecf(): x(0), y(0), z(0) {
		std::cout << "vecf()" << std::endl;
	};
	vecf::vecf(float x, float y, float z): x(x), y(y), z(z) {
		std::cout << "vecf(x, y, z)" << std::endl;
	};
	vecf::vecf(const vecf& other): x(other.x), y(other.y), z(other.z) {
		std::cout << "vecf(other)" << std::endl;
	};

	vecf& vecf::operator =(const vecf& other) {
		std::cout << "vecf = other" << std::endl;

		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	};
}