#pragma once

#include "errors.hpp"
#include <exception>
#include <string>
#include <utility>

class Exception final : public std::exception {

public:
	Exception(pf::PF_Error error, const char* message) : error_val{ error }, message{ message } {}
	explicit Exception(const char* message) : error_val{ pf::PF_Error::UNKNOWN_ERROR }, message{ message } {}
	~Exception() noexcept override = default;

	[[nodiscard]] pf::PF_Error error() const noexcept { return error_val; }
	[[nodiscard]] const char* what() const noexcept override { return message; }

	inline static void throw_if(bool condition, pf::PF_Error error, const char* message) {
		if (condition)
			throw Exception{ error, message };
	}
private:
	pf::PF_Error error_val;
	const char* message;

};