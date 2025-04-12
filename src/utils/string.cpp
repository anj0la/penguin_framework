#include "utils/string.hpp"

String::String(const char* str) {
	size = length(str);
	buf = new char[size + 1];
	std::memcpy(buf, str, size + 1);
}

String::String(const String& other)
	: size(other.size), buf(new char[other.size + 1]) {
	std::memcpy(buf, other.buf, size + 1);
}

String::String(String&& other) noexcept
	: size(std::exchange(other.size, 0)),
	buf(std::exchange(other.buf, nullptr)) {
}

String& String::operator=(const String& other) {
	if (this != &other) {
		delete[] buf;
		size = other.size;
		buf = new char[size + 1];
		std::memcpy(buf, other.buf, size + 1);
	}
	return *this;
}

String& String::operator=(String&& other) noexcept { 
	if (this != &other) {
		delete[] buf;
		buf = other.buf;
		size = other.size;
		other.buf = nullptr;
		other.size = 0;
	}
	return *this;
}

String::~String() {
	delete[] buf;
	size = 0;
}