#pragma once

#include "errors.hpp"
#include "string.hpp"

#include <SDL3/SDL_error.h>
#include <exception>
#include <utility>

class Exception final : public std::exception {

public:
	Exception(const char* message, PF_Error error = PF_Error::Unknown) : message(message), error_val(error) {}
	~Exception() noexcept override = default;

	[[nodiscard]] const char* what() const noexcept override { return message; }
	[[nodiscard]] PF_Error error() const noexcept { return error_val; }

	inline static void throw_if(bool condition, const char* message, PF_Error error) { if (condition) throw Exception{ message, error }; }
private:
	String message;
	PF_Error error_val;
};