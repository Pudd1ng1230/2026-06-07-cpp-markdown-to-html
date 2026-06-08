#pragma once

#include <optional>
#include <string>

namespace utils {

// 读取整个文件内容，成功返回内容，失败返回 nullopt
std::optional<std::string> read_file(const std::string& path);

// 将内容写入文件，返回是否成功
bool write_file(const std::string& path, const std::string& content);

}  // namespace utils
