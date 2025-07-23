#include <penguin_framework/entry_point.hpp>
#include <penguin_framework/penguin_init.hpp>
#include <SDL3/SDL_main.h> 

namespace penguin {

    int main(int argc, char* argv[]) {
        penguin::init();
        int exit_code = penguin_entry();
        penguin::quit();
        return exit_code;
    }
}
