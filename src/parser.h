#pragma once

#include <string>
#include <vector>

// Markdown 解析后的中间表示：一个"块"
struct Block {
    enum Type { Heading, Paragraph, UnorderedList, CodeBlock, HorizontalRule, Blockquote };
    Type type;
    int level;                          // 1~6 用于标题，0 用于其他
    std::string text;                   // 标题 / 段落 / 代码块 的文本内容
    std::vector<std::string> items;     // 无序列表的各列表项
};

// 将原始 Markdown 字符串解析为 Block 列表
std::vector<Block> parse_markdown(const std::string& md);
