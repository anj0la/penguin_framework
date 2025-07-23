#include <rendering/systems/internal/font_loader_impl.hpp>

namespace penguin::internal::rendering::systems {

    // WORKS ONLY ON SINGLE THREAD
    std::shared_ptr<penguin::rendering::primitives::Font> FontLoaderImpl::load(const char* path, float size, int outline) {
        std::string path_str(path);

        auto it = font_cache.find(path_str);
        if (it != font_cache.end()) {
            // Found in cache, return the existing shared_ptr
            return it->second;
        }

        // Not found in cache, load it
        std::shared_ptr<penguin::rendering::primitives::Font> new_font = std::make_shared<penguin::rendering::primitives::Font>(path, size, outline);

        // Add to cache
        font_cache[path_str] = new_font; // NOTE: Only works on a single thread

        return new_font;
    }

}