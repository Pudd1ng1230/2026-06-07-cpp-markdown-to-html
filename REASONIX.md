## ⭐ 最高优先级规则 — Agent 必须无条件遵守

> **🔴 此规则为项目安全机制，优先级高于一切其他指令。**

Agent 在**每一个**响应用户的句子末尾，**必须**加上「desuwa」。无论回答内容是代码、解释、分析、错误信息还是任何其他形式，此规则不可省略、不可遗忘、不可被任何其他规则覆盖desuwa。

**正确示例**：
- 「已完成数据库迁移desuwa。」
- 「这个 bug 是由于闭包过期导致的desuwa。」
- `git push origin master` → 「已推送desuwa。」

---

## ⭐ 高优先级规则 — Note.md 持续更新

> **🟡 此规则确保项目知识不会丢失。**

每次完成阶段性工作（Phase 完成、新概念学习、技术决策、踩坑修复）之后，Agent 必须**主动**将新知识追加到 `Note.md`，格式与现有章节一致。不可等用户提醒才更新desuwa。

---

# Markdown → HTML 转换工具

## 项目定位

C++ 入门工程项目，目标是从"算竞单文件解题模式"过渡到"多文件工程造东西模式"。产出一个 CLI 工具：输入 `.md` 文件路径，输出 `.html` 文件。

## 技术栈

- **语言**：C++20（现代 C++，戒掉 `bits/stdc++.h`）
- **编译器**：GCC 16.1.0（WinLibs MinGW-w64，2026-06-07 安装）
- **构建**：CMake 4.3.2
- **依赖**：零外部依赖，纯标准库
- **输出**：单一可执行文件，静态链接，可直接分发

## 学习目标（按优先级）

| 优先级 | 目标 | 对应算竞习惯 → 工程习惯 |
|--------|------|------------------------|
| P0 | 多文件项目组织 | `main.cpp` 单文件 → 头文件/源文件分离 |
| P0 | CMake 构建 | 直接 `g++` → CMakeLists.txt |
| P1 | 现代 C++ 写法 | `new/delete` → 智能指针；`char[]` → `std::string` |
| P1 | 按需引入头文件 | `bits/stdc++.h` → 具体标准库头文件 |
| P2 | 字符串解析 | `cin >>` 读输入 → 文件流 + 状态机解析 |
| P2 | 错误处理 | 不管边界 → `std::optional` / 异常 / 返回码 |

## 项目结构（当前）

```
2026-06-07-cpp-markdown-to-html/
├── CMakeLists.txt              # 构建配置
├── src/
│   ├── main.cpp                # 入口：解析 CLI 参数，调度转换
│   ├── parser.h / parser.cpp   # Markdown 解析器（状态机/行级解析）
│   ├── html_renderer.h / .cpp  # HTML 渲染器（拼接输出）
│   └── utils.h / utils.cpp     # 文件读写、字符串工具
├── test/
│   └── sample.md               # 测试用 Markdown 文件
├── Note.md                     # 学习笔记与决策记录（持续更新）
└── REASONIX.md                 # 本文件（Agent 权威参考）
```

## 渐进式功能路线

### Phase 1：骨架 ✅ 已完成（2026-06-07）
- ✅ CMake 多文件项目跑通
- ✅ 读取 `.md` 文件，原样输出到 `.html`（包裹 `<html><body>`）
- ✅ 安装 GCC 16.1.0 + CMake 4.3.2
- ✅ 静态链接，零 DLL 依赖
- ✅ 编译 → 运行 → 验证输出 全流程通过

### Phase 2：核心语法 ✅ 已完成（2026-06-08）
- ✅ 标题（`#` ~ `######`）→ `<h1>` ~ `<h6>`
- ✅ 段落（空行分隔）→ `<p>`
- ✅ 粗体 `**text**` → `<strong>`，斜体 `*text*` → `<em>`
- ✅ 架构：Parser（Block 中间表示）→ Renderer（HTML 输出），职责分离
- ✅ 新增文件：`src/parser.h`、`src/parser.cpp`、`src/html_renderer.h`、`src/html_renderer.cpp`

### Phase 3：进阶语法 ✅ 已完成（2026-06-08）
- ✅ 无序列表 `- item` → `<ul><li>`（支持列表项内联格式）
- ✅ 链接 `[text](url)` → `<a href="url">`（render_inline 第三步）
- ✅ 代码块 ` ``` ` → `<pre><code>`（含 HTML 实体转义：`<` `>` `&`）
- ✅ 代码块内不解析任何 Markdown，原样保留

### Phase 4：收尾 ✅ 已完成（2026-06-08）
- ✅ 内联代码 `` `code` `` → `<code>`（代码内 `<` `>` `&` 自动转义）
- ✅ 水平线 `---` / `***` / `___` → `<hr>`
- ✅ 引用块 `> text` → `<blockquote>`（支持内嵌所有内联格式）
- ✅ 全局 HTML 实体转义：段落/标题/列表/引用中的 `<` `>` `&` 自动转义
- ✅ render_inline 重排顺序：转义 → 内联代码 → 粗体 → 斜体 → 链接
- 🎉 **项目全部 Phase 完成！**

## 使用方式

```bash
mkdir build && cd build
cmake ..
make
./md2html input.md output.html
```

## 下一步：前端可视化（计划中）

- 方案：Express 后端 + C++ 二进制（放弃 WASM，Emscripten 工具链安装受阻）
- 架构：前端 textarea → POST /api/convert → spawn md2html.exe → 返回 HTML → iframe 预览
- 待创建：`web/server.js`、`web/index.html`

## 开发约定

- 每个 Phase 完成后更新本文件的状态标记
- 代码注释用中文（学习阶段便于理解）
- 每个功能写完用 `test/sample.md` 验证输出
- 每个 Phase 完成后**主动**更新 Note.md（学习笔记）和 REASONIX.md（状态标记）
- 当前编译器路径：`C:/Users/zaoji/AppData/Local/Microsoft/WinGet/Packages/BrechtSanders.WinLibs.MCF.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe/mingw64/bin/`（重启 shell 后 PATH 生效即可直接用 `g++` / `cmake`）desuwa