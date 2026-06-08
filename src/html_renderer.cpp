#include "html_renderer.h"

#include <sstream>

// 处理行内格式，按顺序：
// 1. 全局转义 < > &
// 2. `代码`
// 3. **粗体**
// 4. *斜体*
// 5. [text](url)
static std::string render_inline(const std::string& text) {
    std::string result = text;

    // 第一步：全局 HTML 实体转义（保护用户文本中的 < > &）
    {
        std::string escaped;
        for (char c : result) {
            switch (c) {
            case '<': escaped += "&lt;"; break;
            case '>': escaped += "&gt;"; break;
            case '&': escaped += "&amp;"; break;
            default:  escaped += c;
            }
        }
        result = std::move(escaped);
    }

    // 第二步：处理 `行内代码`（必须在粗体/斜体之前，因为代码内的 * 不应被解析）
    size_t pos = 0;
    while ((pos = result.find('`', pos)) != std::string::npos) {
        size_t end = result.find('`', pos + 1);
        if (end == std::string::npos) break;
        // 提取代码内容（已经是转义过的，安全）
        std::string code = result.substr(pos + 1, end - pos - 1);
        result.replace(pos, end - pos + 1, "<code>" + code + "</code>");
        pos += 6 + code.size() + 7;  // <code> + code + </code>
    }

    // 第三步：处理 **粗体**
    pos = 0;
    while ((pos = result.find("**", pos)) != std::string::npos) {
        size_t end = result.find("**", pos + 2);
        if (end == std::string::npos) break;
        result.replace(pos, 2, "<strong>");
        end = result.find("**", pos + 8);
        if (end == std::string::npos) break;
        result.replace(end, 2, "</strong>");
        pos = end + 9;
    }

    // 第四步：处理 *斜体*（剩余单星号）
    pos = 0;
    while ((pos = result.find('*', pos)) != std::string::npos) {
        size_t end = result.find('*', pos + 1);
        if (end == std::string::npos) break;
        result.replace(pos, 1, "<em>");
        end = result.find('*', pos + 4);
        if (end == std::string::npos) break;
        result.replace(end, 1, "</em>");
        pos = end + 5;
    }

    // 第五步：处理 [text](url) 链接
    pos = 0;
    while ((pos = result.find('[', pos)) != std::string::npos) {
        size_t bracket_end = result.find(']', pos + 1);
        if (bracket_end == std::string::npos) break;

        if (bracket_end + 1 >= result.size() ||
            result[bracket_end + 1] != '(') {
            pos = bracket_end + 1;
            continue;
        }

        size_t paren_end = result.find(')', bracket_end + 2);
        if (paren_end == std::string::npos) break;

        std::string link_text = result.substr(pos + 1, bracket_end - pos - 1);
        std::string url = result.substr(bracket_end + 2, paren_end - bracket_end - 2);

        std::string anchor = "<a href=\"" + url + "\">" + link_text + "</a>";
        result.replace(pos, paren_end - pos + 1, anchor);
        pos += anchor.size();
    }

    return result;
}

// 渲染单个 Block 为 HTML 片段
static std::string render_block(const Block& block) {
    switch (block.type) {
    case Block::Heading: {
        std::string inner = render_inline(block.text);
        return "<h" + std::to_string(block.level) + ">" + inner +
               "</h" + std::to_string(block.level) + ">\n";
    }
    case Block::Paragraph: {
        std::string inner = render_inline(block.text);
        return "<p>" + inner + "</p>\n";
    }
    case Block::UnorderedList: {
        std::ostringstream out;
        out << "<ul>\n";
        for (const auto& item : block.items) {
            out << "  <li>" << render_inline(item) << "</li>\n";
        }
        out << "</ul>\n";
        return out.str();
    }
    case Block::CodeBlock: {
        // 代码块：不经过 render_inline，单独转义
        std::string escaped;
        for (char c : block.text) {
            switch (c) {
            case '<': escaped += "&lt;"; break;
            case '>': escaped += "&gt;"; break;
            case '&': escaped += "&amp;"; break;
            default:  escaped += c;
            }
        }
        return "<pre><code>" + escaped + "</code></pre>\n";
    }
    case Block::HorizontalRule:
        return "<hr>\n";
    case Block::Blockquote: {
        std::string inner = render_inline(block.text);
        return "<blockquote>\n<p>" + inner + "</p>\n</blockquote>\n";
    }
    default:
        return "";
    }
}

std::string render_html(const std::string& title,
                        const std::vector<Block>& blocks) {
    std::ostringstream html;

    html << R"(<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>)" << title << R"(</title>
    <style>
        body {
            max-width: 800px;
            margin: 0 auto;
            padding: 2rem 1rem;
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif;
            line-height: 1.7;
            color: #1a1a1a;
            background: #fff;
        }
        h1 { font-size: 2em; border-bottom: 2px solid #eee; padding-bottom: 0.3em; }
        h2 { font-size: 1.5em; border-bottom: 1px solid #eee; padding-bottom: 0.2em; }
        h3 { font-size: 1.25em; }
        strong { color: #d14; }
        code {
            background: #f0f0f0;
            padding: 0.2em 0.4em;
            border-radius: 3px;
            font-family: "Fira Code", "Consolas", monospace;
            font-size: 0.9em;
        }
        pre {
            background: #f5f5f5;
            padding: 1em;
            border-radius: 4px;
            overflow-x: auto;
        }
        pre code {
            background: none;
            padding: 0;
            font-size: 0.9em;
        }
        blockquote {
            border-left: 4px solid #ccc;
            margin: 1em 0;
            padding: 0.5em 1em;
            color: #666;
            background: #fafafa;
        }
        blockquote p { margin: 0; }
        hr {
            border: none;
            border-top: 2px solid #eee;
            margin: 2em 0;
        }
    </style>
</head>
<body>
)";

    for (const auto& block : blocks) {
        html << render_block(block);
    }

    html << R"(
</body>
</html>
)";

    return html.str();
}
