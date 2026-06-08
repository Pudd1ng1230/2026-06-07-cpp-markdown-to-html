#pragma once

#include "parser.h"

#include <string>
#include <vector>

// 将 Block 列表渲染为完整的 HTML 文档字符串
std::string render_html(const std::string& title,
                        const std::vector<Block>& blocks);
