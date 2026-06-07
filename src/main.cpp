#include "utils.h"

#include <iostream>   // cout / cerr
#include <string>     // string

// 把 Markdown 原文包裹成完整 HTML 页面
std::string wrap_html(const std::string& title, const std::string& body) {
    return R"(<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>)" + title + R"(</title>
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
    </style>
</head>
<body>
<pre>)" + body + R"(</pre>
</body>
</html>)";
}

int main(int argc, char* argv[]) {
    // 命令行参数检查
    if (argc != 3) {
        std::cerr << "用法：" << argv[0] << " <输入.md> <输出.html>\n";
        return 1;
    }

    const std::string input_path  = argv[1];
    const std::string output_path = argv[2];

    // 读取 Markdown 文件
    std::string content;
    if (!utils::read_file(input_path, content)) {
        return 1;  // read_file 已经打印了错误信息
    }

    // 生成 HTML（Phase 1：纯文本包裹，不做解析）
    const std::string html = wrap_html(input_path, content);

    // 写入 HTML 文件
    if (!utils::write_file(output_path, html)) {
        return 1;
    }

    std::cout << "✅ 转换完成：" << input_path << " → " << output_path << "\n";
    return 0;
}
