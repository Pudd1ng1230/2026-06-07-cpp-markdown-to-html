#include "parser.h"

#include <algorithm>
#include <sstream>
#include <unordered_set>

// 判断一行是否是水平线（3+ 个 - * _，可含空格）
static bool is_horizontal_rule(const std::string& line) {
    if (line.empty()) return false;

    char marker = '\0';
    int count = 0;

    for (char c : line) {
        if (c == ' ') continue;
        if (c == '-' || c == '*' || c == '_') {
            if (marker == '\0') {
                marker = c;
            } else if (c != marker) {
                return false;  // 混用不同字符，不是水平线
            }
            ++count;
        } else {
            return false;  // 含其他字符
        }
    }

    return count >= 3;
}

std::vector<Block> parse_markdown(const std::string& md) {
    std::vector<Block> blocks;
    std::istringstream stream(md);
    std::string line;

    // 状态变量
    std::string paragraph_buf;
    bool in_paragraph = false;

    std::vector<std::string> list_items;
    bool in_list = false;

    std::string code_buf;
    bool in_code_block = false;

    std::string blockquote_buf;
    bool in_blockquote = false;

    auto flush_paragraph = [&]() {
        if (in_paragraph && !paragraph_buf.empty()) {
            blocks.push_back({Block::Paragraph, 0, paragraph_buf, {}});
            paragraph_buf.clear();
            in_paragraph = false;
        }
    };

    auto flush_list = [&]() {
        if (in_list && !list_items.empty()) {
            blocks.push_back({Block::UnorderedList, 0, "", list_items});
            list_items.clear();
            in_list = false;
        }
    };

    auto flush_blockquote = [&]() {
        if (in_blockquote && !blockquote_buf.empty()) {
            blocks.push_back({Block::Blockquote, 0, blockquote_buf, {}});
            blockquote_buf.clear();
            in_blockquote = false;
        }
    };

    while (std::getline(stream, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        // --- 状态 1：代码块内 ---
        if (in_code_block) {
            if (line.size() >= 3 &&
                line[0] == '`' && line[1] == '`' && line[2] == '`') {
                if (!code_buf.empty() && code_buf.back() == '\n') {
                    code_buf.pop_back();
                }
                blocks.push_back({Block::CodeBlock, 0, code_buf, {}});
                code_buf.clear();
                in_code_block = false;
            } else {
                code_buf += line + '\n';
            }
            continue;
        }

        // --- 状态 2：代码块开始 ---
        if (line.size() >= 3 &&
            line[0] == '`' && line[1] == '`' && line[2] == '`') {
            flush_paragraph();
            flush_list();
            flush_blockquote();
            in_code_block = true;
            code_buf.clear();
            continue;
        }

        // --- 状态 3：水平线 ---
        if (is_horizontal_rule(line)) {
            flush_paragraph();
            flush_list();
            flush_blockquote();
            blocks.push_back({Block::HorizontalRule, 0, "", {}});
            continue;
        }

        // --- 状态 4：无序列表项 ---
        if (line.size() >= 2 && line[0] == '-' && line[1] == ' ') {
            flush_paragraph();
            flush_blockquote();
            std::string item = line.substr(2);
            size_t start = 0;
            while (start < item.size() && item[start] == ' ') ++start;
            item = item.substr(start);
            list_items.push_back(item);
            in_list = true;
            continue;
        }

        // --- 状态 5：引用块 ---
        if (!line.empty() && line[0] == '>') {
            flush_paragraph();
            flush_list();
            // 去掉 ">" 和后面可选的一个空格
            std::string text = line.substr(1);
            if (!text.empty() && text[0] == ' ') {
                text = text.substr(1);
            }
            if (in_blockquote) {
                blockquote_buf += '\n';
            }
            blockquote_buf += text;
            in_blockquote = true;
            continue;
        }

        // --- 状态 6：标题 ---
        int heading_level = 0;
        while (heading_level < static_cast<int>(line.size()) &&
               line[heading_level] == '#') {
            ++heading_level;
        }

        if (heading_level >= 1 && heading_level <= 6 &&
            heading_level < static_cast<int>(line.size()) &&
            line[heading_level] == ' ') {
            flush_paragraph();
            flush_list();
            flush_blockquote();

            std::string text = line.substr(heading_level + 1);
            size_t start = 0;
            while (start < text.size() && text[start] == ' ') ++start;
            size_t end = text.size();
            while (end > start && text[end - 1] == ' ') --end;
            text = text.substr(start, end - start);

            blocks.push_back({Block::Heading, heading_level, text, {}});
            continue;
        }

        // --- 状态 7：空行 ---
        if (line.empty()) {
            flush_paragraph();
            flush_list();
            flush_blockquote();
            continue;
        }

        // --- 状态 8：普通段落行 ---
        flush_list();
        flush_blockquote();
        if (in_paragraph) {
            paragraph_buf += '\n';
        }
        paragraph_buf += line;
        in_paragraph = true;
    }

    // 文件末尾收尾
    if (in_code_block) {
        if (!code_buf.empty() && code_buf.back() == '\n') {
            code_buf.pop_back();
        }
        blocks.push_back({Block::CodeBlock, 0, code_buf, {}});
    }
    flush_list();
    flush_blockquote();
    flush_paragraph();

    return blocks;
}
