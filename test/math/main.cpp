#include <iostream>
#include "vecf.cpp"

void vprint(const math::vecf& v) {
	std::cout << "{" << v.x << ", " << v.y << ", " << v.z << "}" << std::endl;
}

int main() {
	math::vecf a;
	math::vecf b(1, 2, 3);
	math::vecf c(b);

	vprint(a);
	vprint(b);
	vprint(c);

	math::vecf d;
	d = b;

	vprint(d);

	std::cin.get();
}