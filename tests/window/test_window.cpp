#include "core/window/pf_window.hpp"
#include <SDL3/SDL_init.h>
#include <gtest/gtest.h>

// Setting Up the Test Suite

class PF_WindowTestFixture : public ::testing::Test {
protected:
	PF_Window window;

	PF_WindowTestFixture() {
		SDL_Init(SDL_INIT_VIDEO);
	}

	~PF_WindowTestFixture() override {
		SDL_Quit();
	}

};
