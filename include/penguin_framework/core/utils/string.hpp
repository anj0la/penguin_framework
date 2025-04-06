#pragma once

#include <cstring>

class [[nodiscard]] String {
public:

	// Default constructor

	String() : buf(nullptr), size(0) {}

	// Regular constructor

	String(const char* str);

	// Copy and move constructors

	String(const String& other); // Copy constructor
	String(String&& other) noexcept; // Move constructor
	String& operator=(const String& other); // Copy assignment
	String& operator=(String&& other) noexcept; // Move assignment

	// Destructor

	~String();

	// Other functions

	constexpr static size_t length(const char* str) {
		size_t len = 0;
		while (*str != '\0') {
			len++;
			str++;
		}
		return len;
	}

	constexpr const char* c_str() const {
		return buf ? buf : "";
	}

	inline bool operator==(const String& lhs, const String& rhs) {
		return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
	}

private:
	char* buf = nullptr;
	unsigned int size = 0;
};