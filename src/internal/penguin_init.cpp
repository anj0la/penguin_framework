#include <penguin_framework/penguin_init.hpp>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

namespace penguin {

	bool init(const InitOptions& options) {
		// Initialize SDL and SDL_ttf (SDL_image is automatically initialized with SDL)
		bool init_sdl = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD | SDL_INIT_HAPTIC);
		bool init_ttf = TTF_Init();
		if (!init_sdl || !init_ttf) {
			return false;
		}

		// Optionally set to headless mode (useful for testing)
		if (options.headless_mode) {
			SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
		}

		return true;
	}

	void quit() {
		TTF_Quit();
		SDL_Quit();
	}
}
