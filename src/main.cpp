#include "utils.h"
#include "parser.h"
#include "html_renderer.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "用法：" << argv[0] << " <输入.md> <输出.html>\n";
        return 1;
    }

    const std::string input_path  = argv[1];
    const std::string output_path = argv[2];

    // 1. 读取 Markdown 文件
    auto content = utils::read_file(input_path);
    if (!content) {
        return 1;
    }

    // 2. 解析为 Block 列表
    auto blocks = parse_markdown(*content);

    // 3. 渲染为 HTML
    const std::string html = render_html(input_path, blocks);

    // 4. 写入输出文件
    if (!utils::write_file(output_path, html)) {
        return 1;
    }

    std::cout << "✅ 转换完成：" << input_path << " → " << output_path << "\n";
    return 0;
}
