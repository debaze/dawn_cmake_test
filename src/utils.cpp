#include "utils.hpp"

void print(const char* message) {
	std::cout << message << std::endl;
}

void print(bool condition, const char* message) {
	std::cout << message << ": " << (condition ? "OK" : "KO") << std::endl;
}

char* readFile(const char* path) {
	std::ifstream file(path, std::ios::binary);

	if (file.is_open()) {
		file.seekg(0, std::ifstream::end);
		std::streamoff length = file.tellg();
		file.seekg(0, std::ifstream::beg);

		char* data = new char[length + 1];
		file.read(data, length);
		data[length] = '\0';

		file.close();

		return data;
	}

	return nullptr;
}