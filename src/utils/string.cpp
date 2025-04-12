#include "utils/string.hpp"

String::String(const char* str) {
	size = length(str);
	buf = std::make_unique<char[]>(size + 1);
	std::memcpy(buf.get(), str, size + 1);
}

String::String(const String& other)
	: size(other.size), buf(std::make_unique<char[]>(other.size + 1)) {
	std::memcpy(buf.get(), other.buf.get(), size + 1);
}

String::String(String&& other) noexcept
	: size(std::exchange(other.size, 0)),
	buf(std::move(other.buf)) {
}

String& String::operator=(const String& other) {
	if (this != &other) {
		size = other.size;
		auto new_buf = std::make_unique<char[]>(size + 1);
		std::memcpy(new_buf.get(), other.buf.get(), size + 1);
		buf = std::move(new_buf);
	}
	return *this;
}

String& String::operator=(String&& other) noexcept { 
	if (this != &other) {
		size = std::exchange(other.size, 0);
		buf = std::move(other.buf);
	}
	return *this;
}