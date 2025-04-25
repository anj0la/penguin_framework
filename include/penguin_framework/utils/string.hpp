#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <cstring>
#include <cstddef>
#include <utility>
#include <memory>


class PENGUIN_API [[nodiscard]] String {
public:
	// Default constructor

	String() = default;

	// Regular constructor

	String(const char* str);

	// Copy and move constructors

	String(const String& other); // Copy constructor
	String(String&& other) noexcept; // Move constructor
	String& operator=(const String& other); // Copy assignment
	String& operator=(String&& other) noexcept; // Move assignment

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
		return buf ? buf.get() : "";
	}

	inline bool operator==(const String& rhs) {
		return compare(c_str(), rhs.c_str());
	}

private:
	std::unique_ptr<char[]> buf;
	size_t size = 0;
};