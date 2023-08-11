#include "utils.hpp"

void print(const char* message) {
	std::cout << message << std::endl;
}

void print(bool condition, const char* message) {
	std::cout << message << ": " << (condition ? "OK" : "KO") << std::endl;
}