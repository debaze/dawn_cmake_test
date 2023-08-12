#include "utils.hpp"

void print(const char* message) {
	std::cout << message << std::endl;
}

void print(bool condition, const char* message) {
	std::cout << message << ": " << (condition ? "OK" : "KO") << std::endl;
}

const char* readFile(const char* path) {
	const char* result;
	std::ifstream file(path);

	if (file.is_open()) {
		std::string content(
			(std::istreambuf_iterator<char>(file)),
			(std::istreambuf_iterator<char>())
		);

		result = content.c_str();
	}

	file.close();

	return result;
}