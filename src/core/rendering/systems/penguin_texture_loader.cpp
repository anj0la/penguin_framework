#include <penguin_framework/core/rendering/systems/penguin_texture_loader.hpp>
#include <penguin_framework/core/rendering/systems/penguin_texture_loader_impl.hpp>

// --- Define TextureLoaderImpl Methods ---

using penguin::core::rendering::systems::TextureLoader;
using penguin::core::rendering::systems::TextureLoaderImpl;
using penguin::core::rendering::primitives::Texture;

std::shared_ptr<Texture> TextureLoaderImpl::load(NativeRendererPtr renderer, const char* path) {
    std::string_view path_str(path);
    // String path_str(path);

    auto it = texture_cache.find(path_str);
    if (it != texture_cache.end()) {
        // Found in cache, return the existing shared_ptr
        return it->second;
    }

    // Not found in cache, load it
    std::shared_ptr<Texture> new_texture = std::make_shared<Texture>(renderer, path);

    // Add to cache
    texture_cache[path_str] = new_texture; // NOTE: Only works on a single thread

    return new_texture;
}

// --- Define TextureLoader Methods ---

TextureLoader::TextureLoader() : pimpl_(std::make_unique<TextureLoaderImpl>()) {}
TextureLoader::~TextureLoader() = default;

std::shared_ptr<Texture> TextureLoader::load(NativeRendererPtr renderer, const char* path) {
    return pimpl_->load(renderer, path);
}