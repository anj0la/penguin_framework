#pragma once

#include <penguin_api.hpp>

namespace penguin {

	struct InitOptions {
		bool headless_mode = false;
	};

	PENGUIN_API bool init(const InitOptions& options = {});
	PENGUIN_API void quit();
}
