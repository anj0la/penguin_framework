#pragma once

#include <filesystem>

inline std::filesystem::path get_test_asset_path(const char* name) {
    return std::filesystem::path(TEST_ASSETS_DIR) / name;
}