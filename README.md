# md2html — Markdown → HTML 转换工具

C++20 实现的 CLI Markdown 解析器，零外部依赖，编译为单一静态链接可执行文件，附带 Web 前端实时预览。

## 快速开始

### CLI 工具

```bash
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
make
./md2html input.md output.html
```

### Web 前端

```bash
cd web
npm install
npm start
# 浏览器打开 http://localhost:3001
```

## 支持的 Markdown 语法

| 语法 | 示例 | 输出 |
|------|------|------|
| 标题 | `# H1` ~ `###### H6` | `<h1>` ~ `<h6>` |
| 段落 | 空行分隔 | `<p>` |
| 粗体 | `**text**` | `<strong>` |
| 斜体 | `*text*` | `<em>` |
| 无序列表 | `- item` | `<ul><li>` |
| 链接 | `[text](url)` | `<a href>` |
| 代码块 | ` ``` ` 围栏 | `<pre><code>` |
| 内联代码 | `` `code` `` | `<code>` |
| 引用块 | `> text` | `<blockquote>` |
| 水平线 | `---` / `***` | `<hr>` |
| 实体转义 | `<` `>` `&` | `&lt;` `&gt;` `&amp;` |

## 项目结构

```
├── CMakeLists.txt              # C++ 构建配置
├── src/
│   ├── main.cpp                # CLI 入口
│   ├── parser.h / parser.cpp   # Markdown 解析器（6 状态状态机）
│   ├── html_renderer.h / .cpp  # HTML 渲染器（5 步内联处理）
│   └── utils.h / utils.cpp     # 文件读写
├── test/
│   └── sample.md               # 测试样本
├── web/
│   ├── server.js               # Express 后端（调 C++ 二进制）
│   ├── index.html              # 前端页面（实时预览）
│   └── package.json
├── Note.md                     # 学习笔记（13 章）
└── REASONIX.md                 # 项目状态与开发约定
```

## 技术栈

- **语言**：C++20
- **编译器**：GCC 16.1.0（MinGW-w64）
- **构建**：CMake 4.3.2
- **前端**：Express + 原生 HTML/CSS/JS
- **依赖**：零（C++ 纯标准库）

## 开发进度

| Phase | 内容 | 状态 |
|-------|------|------|
| 1 | 骨架：CMake + 文件读写 | ✅ |
| 2 | 核心：标题/段落/粗斜体 | ✅ |
| 3 | 进阶：列表/链接/代码块 | ✅ |
| 4 | 收尾：内联代码/水平线/引用/转义 | ✅ |
| Web | 前端可视化：Express + C++ 二进制 | ✅ |
