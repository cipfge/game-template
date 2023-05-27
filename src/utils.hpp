#pragma once

#include <string>
#include <filesystem>

namespace utils
{

size_t file_size(const std::string &file_path)
{
    std::filesystem::path path { file_path };
    return std::filesystem::file_size(path);
}

} // namespace utils
