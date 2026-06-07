#include "utils.h"

#include <fstream>   // ifstream / ofstream
#include <sstream>   // stringstream
#include <iostream>  // cerr

namespace utils {

bool read_file(const std::string& path, std::string& out_content) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "错误：无法打开文件 \"" << path << "\"\n";
        return false;
    }

    // 把整个流读进 stringstream 再转成 string
    std::stringstream buffer;
    buffer << file.rdbuf();
    out_content = buffer.str();
    return true;
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
