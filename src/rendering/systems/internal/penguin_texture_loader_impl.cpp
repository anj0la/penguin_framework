#include <rendering/systems/internal/penguin_texture_loader_impl.hpp>

namespace penguin::internal::rendering::systems {

    // WORKS ONLY ON SINGLE THREAD
    std::shared_ptr<penguin::rendering::primitives::Texture> TextureLoaderImpl::load(NativeRendererPtr renderer, const char* path) {
        std::string path_str(path);

        auto it = texture_cache.find(path_str);
        if (it != texture_cache.end()) {
            // Found in cache, return the existing shared_ptr
            return it->second;
        }

        // Not found in cache, load it
        std::shared_ptr<penguin::rendering::primitives::Texture> new_texture = std::make_shared<penguin::rendering::primitives::Texture>(renderer, path);

        // Add to cache
        texture_cache[path_str] = new_texture; // NOTE: Only works on a single thread

        return new_texture;
    }

}