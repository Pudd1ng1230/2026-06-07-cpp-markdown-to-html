#pragma once

#include <string>

namespace utils {

// 读取整个文件内容，成功返回 true 并写入 content；失败返回 false
bool read_file(const std::string& path, std::string& out_content);

// 将内容写入文件，返回是否成功
bool write_file(const std::string& path, const std::string& content);

}  // namespace utils
