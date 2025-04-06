#include "core/utils/string.hpp"

String::String(const char* str) {
	size = length(str);
	buf = new char[size + 1];
	for (size_t i = 0; i < size; ++i) {
		buf[i] = str[i];
	}
	buf[size] = '\0';
}

String::String(const String& other) {
	size = other.size;
	buf = new char[size + 1];
	for (size_t i = 0; i < size; ++i) {
		buf[i] = other.buf[i];
	}
	buf[size] = '\0';
}

String::String(String&& other) noexcept {
	size = other.size;
	buf = other.buf;
	other.buf = nullptr;
	other.size = 0;
}

String& String::operator=(const String& other) {
	if (this != &other) {
		delete[] buf;
		size = other.size;
		buf = new char[size + 1];
		for (size_t i = 0; i < size; ++i) {
			buf[i] = other.buf[i];
		}
		buf[size] = '\0';
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