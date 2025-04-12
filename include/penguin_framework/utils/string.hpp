#pragma once

#include <cstring>
#include <cstddef>
#include <utility>

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

	constexpr static bool compare(const char* lhs, const char* rhs) {
		auto size_lhs = length(lhs);
		auto size_rhs = length(rhs);

		if (size_lhs < size_rhs || size_lhs > size_rhs) {
			return false;
		}

		for (size_t i = 0; i < size_lhs; ++i) {
			if (lhs[i] != rhs[i]) {
				return false;
			}
		}

		return true;
	}

	constexpr const char* c_str() const {
		return buf ? buf : "";
	}

	inline bool operator==(const String& rhs) {
		return compare(c_str(), rhs.c_str());
	}

private:
	char* buf = nullptr;
	size_t size = 0;
};