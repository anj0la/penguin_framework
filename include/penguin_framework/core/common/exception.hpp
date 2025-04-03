#pragma once

#include "errors.hpp"
#include <SDL3/SDL_error.h>
#include <exception>
#include <string>
#include <utility>

class Exception final : public std::exception {

public:
	Exception(pf::common::PF_Error error, const char* message) : error_val{ error }, message{ message } {}
	explicit Exception(const char* message) : error_val{ pf::common::PF_Error::Unknown }, message{ message } {}
	~Exception() noexcept override = default;

	[[nodiscard]] pf::common::PF_Error error() const noexcept { return error_val; }
	[[nodiscard]] const char* what() const noexcept override { return message; }

	inline static void throw_if(bool condition, const char* message, pf::common::PF_Error error) {
		if (condition)
			throw Exception{ message, error };
	}
private:
	pf::common::PF_Error error_val;
	const char* message;

};