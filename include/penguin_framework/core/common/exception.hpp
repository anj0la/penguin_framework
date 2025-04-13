#pragma once

#include "errors.hpp"
#include "string.hpp"

#include <SDL3/SDL_error.h>
#include <exception>
#include <string>
#include <utility>

class Exception final : public std::exception {

public:
	Exception(const char* message, pf::core::common::PF_Error error = pf::core::common::PF_Error::Unknown) : error_val(error), message(message) {}
	~Exception() noexcept override = default;

	[[nodiscard]] pf::core::common::PF_Error error() const noexcept { return error_val; }
	[[nodiscard]] const char* what() const noexcept override { return message; }

	inline static void throw_if(bool condition, const char* message, pf::common::PF_Error error) {
		if (condition)
			throw Exception{ message, error };
	}
private:
	String message;
	pf::core::common::PF_Error error_val;
};