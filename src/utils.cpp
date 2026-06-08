#include "utils.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace utils {

std::optional<std::string> read_file(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "错误：无法打开文件 \"" << path << "\"\n";
        return std::nullopt;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool write_file(const std::string& path, const std::string& content) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "错误：无法写入文件 \"" << path << "\"\n";
        return false;
    }

    file << content;
    return true;
}

}  // namespace utils
