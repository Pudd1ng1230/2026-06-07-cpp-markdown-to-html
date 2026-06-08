# C++ 工程学习笔记

> 从算竞到工程的成长记录 · 持续更新中 · 始于 2026-06-01

---

## 一、前端是不是太简单了？现在的趋势是全栈吗？

### 回答

**半对半错。** 静态页面确实不够用了，但不是"前端不重要了"，而是"前端变深了"。

一个现代前端工程师实际在做什么：

| 层级 | 内容 | 例子 |
|------|------|------|
| 静态页面 | HTML + CSS + 原生 JS | 10 年前的前端 |
| 框架层 | React / Vue / Angular 组件化开发 | MovieTracker 的 8 个页面 |
| 状态管理 | 跨组件共享数据、缓存、乐观更新 | 先改 UI 再发请求 |
| 工程化 | Vite/Webpack 打包、Tree Shaking、HMR、Proxy | `vite.config.js` |
| 全栈边界 | Next.js/Nuxt SSR、API Routes、中间件 | 前后端一体项目 |

纯切图仔确实被淘汰了，但懂 React 生态、懂工程化、懂性能优化的前端工程师仍然是刚需。MovieTracker 项目前端占了 60% 工作量（状态管理、乐观更新、图表组件、路由设计），后端反而比较薄。

---

## 二、后端 Java 最卷，MovieTracker 为什么不用 Java？

### 回答

**不是不能，是不划算。** 选型看场景：

| 维度 | Java (Spring Boot) | Node.js (Express) |
|------|-------------------|-------------------|
| 启动时间 | 3-10 秒 | 50 毫秒 |
| 内存占用 | 200-500MB | 30-80MB |
| 代码量 | Controller + Service + DAO + DTO + Mapper | 一个 js 文件 |
| 部署成本 | 需要 JVM，1C1G VPS 勉强跑 | 1C512M 都绰绰有余 |
| 适合场景 | 大型团队、微服务、企业级 | 个人项目、快速原型、轻量 API |

MovieTracker 定位是**个人单机项目**——1 个用户、2243 条数据、SQLite 单文件。用 Java 就像用卡车送一封信：能送到，但没有必要。

Java 的真正优势在：几十人团队协作的类型安全、编译期检查、微服务治理（Spring Cloud）、ORM 事务管理。一个人写小项目，这些反而是负担。

---

## 三、C++ 可以用来写小型项目吗？

### 回答

**完全可以，而且是很好的选择。** 你有算竞基础，C++ 是你的舒适区，这是优势。

**C++ 适合的小项目：**

| 类型 | 例子 | 为什么 |
|------|------|--------|
| 工具/CLI | 文件批量重命名、Markdown 转 HTML | 编译成单一 exe，无依赖，性能极好 |
| 游戏 | 2D 小游戏（SFML/SDL2） | C++ 是游戏工业标准 |
| 算法可视化 | 排序/寻路动画（ImGui + OpenGL） | 算竞知识直接变现 |
| 高性能服务 | HTTP 服务器（Crow/cpp-httplib） | 比 Node 快 10-50× |
| 嵌入式 | Arduino/ESP32 控制 LED、传感器 | C++ 在嵌入式是统治地位 |

**C++ 不太适合的：**

| 场景 | 原因 |
|------|------|
| 带 Web UI 的全栈项目 | C++ 没有 React/Vue 生态 |
| 快速原型验证 | 编译-运行-调试循环比脚本语言慢 |
| 数据处理/爬虫 | Python 10 行搞定，C++ 要 100 行 |

**推荐路线：** 用 C++ 写 HTTP 后端（`cpp-httplib` header-only 库），用 React 写前端，中间通过 REST API 通信。一个 C++ 算法可视化项目——后端 C++ 跑算法返回数据，前端 Canvas/ECharts 画图，既有技术深度又有展示效果喵。

---

## 四、想进入 C++ 开发岗，需要学什么？

### 现有基础（算竞带来）

- 算法/数据结构滚瓜烂熟
- 手写快排、Dijkstra 等经典算法
- 熟练使用 `#include <bits/stdc++.h>`
- 单文件 `main.cpp` 解题模式
- `int a[100010]` 开大数组
- `cin >> n` 读输入

### 缺失技能（开发岗要求）

- 工程代码组织（头文件/源文件分离、模块划分）
- CMake / 构建系统
- 编译链接原理（.o → .so/.exe）
- 多文件项目管理
- 内存管理（RAII、智能指针、所有权）
- 网络编程、多线程、数据库交互

> **核心差距：算竞教会了"用 C++ 解题"，开发岗要的是"用 C++ 造东西"。**

---

### 🔴 第一层：必须会，面试必问

**1. 现代 C++（C++17/20）**

| 概念 | 淘汰的写法 | 现代写法 |
|------|-----------|----------|
| 指针 | `int* p = new int(5); delete p;` | `auto p = std::make_unique<int>(5);` |
| 字符串 | `char str[100];` | `std::string` / `std::string_view` |
| 数组 | `int arr[N];` | `std::array<int, N>` / `std::vector` |
| 函数回调 | 函数指针 | `std::function` + lambda |
| 移动语义 | 不知道 | `std::move` / 右值引用 |

**重点三个：RAII（资源获取即初始化）、智能指针（unique_ptr / shared_ptr）、移动语义。**

**2. STL 深入**

- 容器选择依据：`vector` vs `list`（缓存局部性）
- 关联容器：`unordered_map` vs `map`（哈希 vs 红黑树，rehash 开销）
- 算法库：`std::copy_if`、`std::transform`、`std::accumulate`
- `std::optional`、`std::variant`（替代 NULL/union）

**3. CMake**

```
cmake_minimum_required(VERSION 3.20)
project(my_app)
add_executable(my_app main.cpp utils.cpp)
target_compile_features(my_app PRIVATE cxx_std_20)
```

要学会：`add_library` / `target_link_libraries` / `find_package` / 静态库动态库区别。

---

### 🟡 第二层：区分"能用"和"能用好"

**4. 编译链接原理**

```
预处理 → 编译 → 汇编 → 链接
  ↓        ↓       ↓       ↓
宏展开   .s汇编   .o目标   .exe可执行
头文件   语法树   机器码   符号解析
```

面试高频：头文件重复包含怎么防（`#pragma once`）、为什么模板不能分离编译、`undefined reference` 怎么排查。

**5. 调试工具**

| 工具 | 用途 |
|------|------|
| GDB | `break`、`backtrace`、`print`、`watch` |
| AddressSanitizer | `-fsanitize=address` 定位越界 |
| Valgrind | 内存泄漏检测 |
| perf | 性能热点分析 |

**6. 设计模式（常用的 5-6 个）**

单例、工厂、观察者、策略、RAII（C++ 特有模式）。关键不是背 UML 图，而是能说出"这里为什么用工厂而不是直接 new"。

---

### 🟢 第三层：选方向，定深度

| 方向 | 典型公司 | 额外要学 |
|------|----------|----------|
| **后台/服务端** | 腾讯/字节/量化 | 网络编程（asio）、多线程（锁/无锁）、Linux 系统编程（epoll/信号）、数据库 |
| **游戏开发** | 米哈游/网易/育碧 | Unreal Engine、图形学（OpenGL）、物理引擎、ECS 架构 |
| **嵌入式/IoT** | 华为/大疆/车企 | 交叉编译、RTOS、硬件寄存器、I2C/SPI/UART、内存受限优化 |
| **量化金融** | 幻方/九坤/券商 | 低延迟编程（缓存友好、分支预测、无锁队列）、FIX 协议、数学 |
| **基础架构/DB** | PingCAP/OceanBase | 分布式共识（Raft/Paxos）、存储引擎（LSM-Tree/B+Tree）、RPC 框架 |

---

### 📋 推荐学习路线

```
第 1-2 周：补现代 C++ 基础
  → 把算竞里 new/delete 全部改成智能指针
  → 写一个 CMake 管理的多文件项目
  → 把 #include <bits/stdc++.h> 戒掉

第 3-4 周：做一个"单机 C++ 项目"
  → 比如一个 HTTP 服务器（cpp-httplib 库，200 行）
  → 或者一个终端贪吃蛇（ncurses）
  → 关键：不是解题，是"跑起来不崩溃的软件"

第 5-8 周：选方向深化
  → 喜欢网络和服务器 → 写一个简单聊天室（TCP socket）
  → 喜欢游戏 → 用 SFML 做个小游戏
  → 喜欢底层 → 买块 ESP32 开发板玩嵌入式
```

### 🎯 毕业设计级别项目推荐

用 C++ 实现 HTTP REST API 服务器（cpp-httplib）+ React 前端 + SQLite 存储。代码量 1000-1500 行，展示 C++ 功底 + 全栈能力，面试官一眼能看出你和纯 Web 培训出来的候选人的区别。

---

---

## 五、第一个 C++ 项目启动：Markdown → HTML 转换工具

> 记录时间：2026-06-07

### 决策过程

在第三章列出的 C++ 小型项目类型中，**工具/CLI** 类最适合作为入门项目。具体选择了「Markdown 转 HTML」，原因：

1. **问题域熟悉**：Markdown 语法规则明确，不需要额外学习业务知识
2. **编译成单一 exe**：零依赖，产出一个独立可执行文件
3. **算法映射直接**：字符串解析、状态机、递归——算竞中的基本功可以无缝迁移
4. **成果可视化**：输出 HTML 直接用浏览器打开看效果，反馈即时
5. **可渐进增强**：先支持标题/段落/粗斜体，再逐步加代码块、表格、链接等

### 项目目标

- 学习多文件 C++ 项目组织（头文件/源文件分离）
- 掌握 CMake 构建系统
- 使用现代 C++（C++17/20）：`std::string_view`、`std::optional`、智能指针
- 戒掉 `#include <bits/stdc++.h>`，按需引入标准库头文件
- 产出：一个 CLI 工具，输入 `.md` 文件路径，输出 `.html` 文件

### 文件夹命名

从 `2026-06-07-cpp-try` 更名为 `2026-06-07-markdown-to-html`，体现具体项目方向喵。

---

> **记录时间**：2026-06-01 · 基于与编程导师的对话整理

---

## 六、工程文件结构：src/、test/、CMakeLists.txt 是什么？

> 记录时间：2026-06-07 · Phase 1 搭建中学习

### src/ — 源代码目录

**算竞习惯**：所有代码塞一个 `main.cpp`。

**工程做法**：代码按职责拆成多个文件放进 `src/`。

| 文件 | 职责 |
|------|------|
| `src/main.cpp` | 程序入口：解析命令行参数、调度流程 |
| `src/utils.h` | 声明"文件读写工具"有哪些函数 |
| `src/utils.cpp` | 实现"文件读写工具"的具体逻辑 |
| `src/parser.h` / `.cpp` | Markdown 解析器（规划中） |
| `src/html_renderer.h` / `.cpp` | HTML 渲染器（规划中） |

拆分三原则：
1. **复用**：`utils::read_file()` 写一次，多个文件都能用
2. **隔离**：改文件读写只动 `utils.cpp`，不影响其他模块
3. **编译速度**：大项目只编译修改过的文件，不全量重编

### test/ — 测试目录

**算竞习惯**：拿样例跑一下，看输出。

**工程做法**：测试文件放进 `test/`，每次改完代码都跑一遍所有测试。当前 `test/sample.md` 是项目的测试样本，后期可以加多个测试文件覆盖边界情况。

### CMakeLists.txt — 构建配置

**算竞习惯**：`g++ main.cpp -o a.exe`。

**工程做法**：用 CMake 描述"怎么编译"，CMake 自动生成构建脚本。

| 概念 | 算竞命令 | CMake 等价 |
|------|----------|------------|
| 编译标准 | `-std=c++20` | `set(CMAKE_CXX_STANDARD 20)` |
| 源文件列表 | `main.cpp utils.cpp` | `add_executable(md2html ...)` |
| 头文件路径 | `-I src` | `target_include_directories(...)` |
| 静态链接 | `-static` | `set(CMAKE_EXE_LINKER_FLAGS "-static")` |

### 三者关系

```
CMakeLists.txt          ← 你写的"编译说明书"
      ↓ cmake 读取
   Makefile             ← CMake 自动生成
      ↓ make 执行
   g++ 编译 src/*.cpp
      ↓
   md2html.exe          ← 最终产物
      ↓ 运行
   test/sample.md  →  output.html
```

---

## 七、Phase 1 完成：骨架搭建 + 工具链升级

> 记录时间：2026-06-07

### 工具链

| 工具 | 旧版（Dev-Cpp 自带） | 新版（WinLibs 安装） |
|------|----------------------|---------------------|
| GCC | 4.9.2（2014 年） | 16.1.0（2026 年） |
| CMake | 无 | 4.3.2 |
| C++ 标准 | 仅 C++14 | 完整 C++20/23 |
| 安装方式 | Dev-Cpp 捆绑 | winget 一键安装 |

新编译器路径（重启 shell 后 PATH 自动生效）：
```
C:/Users/zaoji/AppData/Local/Microsoft/WinGet/Packages/
  BrechtSanders.WinLibs.MCF.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe/
  mingw64/bin/
```

### Phase 1 成果

- ✅ `CMakeLists.txt`：C++20 + 静态链接
- ✅ `src/main.cpp`：CLI 参数解析 + HTML 包裹
- ✅ `src/utils.h` / `utils.cpp`：文件读写模块
- ✅ `test/sample.md`：测试样本
- ✅ 编译 → 运行 → 输出验证 全流程通过
- ✅ 静态链接，`md2html.exe` 零 DLL 依赖

### 当前项目结构

```
2026-06-07-cpp-markdown-to-html/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   ├── utils.h
│   └── utils.cpp
├── test/
│   └── sample.md
├── Note.md          ← 本文件（学习笔记，持续更新）
└── REASONIX.md      ← Agent 参考（项目状态 + 规则）
```

### 本文档更名

从 `Question.md` 更名为 `Note.md`，定位从"问答记录"升级为"持续更新的学习笔记"。以后每学一个新概念、每完成一个 Phase 都会追加到本文档喵。

---

## 八、std::optional 语法详解

> 记录时间：2026-06-07 · Phase 2 开始前学习

### 它是什么

`std::optional<T>` 是 C++17 引入的"可能没有值的盒子"。它解决了一个古老问题：函数想返回一个值，但有时候没有合法的值可以返回。

在 C 时代只能返回 `NULL` 指针或 `-1` 这种魔法数；在 C++17 之前用 `std::pair<bool, T>` 或输出参数。`std::optional` 让"没有值"成为一个类型安全的一等公民。

### 在本项目中的用法

**utils.h 中的声明：**
```cpp
std::optional<std::string> read_file(const std::string& path);
```
翻译：`read_file` 要么返回一个 `std::string`（文件内容），要么返回"空"（读取失败）。

**utils.cpp 中的实现：**
```cpp
// 失败时返回"空"
if (!file.is_open()) {
    return std::nullopt;   // ← 这就是"空"，相当于"没有值"
}

// 成功时返回真正的值
return buffer.str();        // ← std::string 自动包装进 optional
```

**main.cpp 中的消费：**
```cpp
auto content = utils::read_file(input_path);

if (!content) {             // ← 检查：盒子是空的吗？
    return 1;               //    是的，读取失败，退出
}

const std::string html = wrap_html(input_path, *content);
//                                       ↑
//                          *content 就是"拆盒"，取出里面的 std::string
```

### 核心操作一览

| 操作 | 代码 | 含义 |
|------|------|------|
| 创建空盒子 | `return std::nullopt;` | 没有值 |
| 创建有值盒子 | `return "hello";` | 自动包装 |
| 检查是否有值 | `if (content)` 或 `if (!content)` | 有/无 |
| 取出值（不安全） | `*content` | 空的会 UB，必须先检查 |
| 取出值（安全） | `content.value()` | 空的会抛 `std::bad_optional_access` |
| 取值或默认 | `content.value_or("默认")` | 空的时候给默认值 |

### 为什么比 C 风格好

```cpp
// ❌ C 风格：返回值既表达数据又表达错误
int read_file(const char* path, char* out_buffer, int max_size);
// 返回 -1 表示失败，返回正数表示读取字节数
// 但万一只读了 0 字节呢？0 和 -1 哪个是错误？

// ✅ C++17：数据和状态分离
std::optional<std::string> read_file(const std::string& path);
// 要么给我完整内容，要么告诉我"没有"
// 不存在歧义
```

---

## 九、为什么头文件和源文件要各写一次命名空间

> 记录时间：2026-06-07 · Phase 2 开始前学习

### 这不是"写两次"，而是"声明和定义分离"

这是 C++ 多文件编译的基本机制。

| | `utils.h`（头文件） | `utils.cpp`（源文件） |
|---|---|---|
| 角色 | 接口承诺 | 功能实现 |
| 给谁看 | 调用方（main.cpp） | 编译器+链接器 |
| 内容 | 函数声明 | 函数定义 |
| 引入方式 | `#include "utils.h"` | 被 CMake 编译 |

**头文件 `utils.h`** 说："存在一个叫 `utils` 的命名空间，里面有两个函数，签名如下... 至于具体怎么实现，去别处找。"

```cpp
// utils.h — 这是"承诺"
namespace utils {
    std::optional<std::string> read_file(const std::string& path);  // 只有声明，没有函数体
    bool write_file(const std::string& path, const std::string& content);
}
```

**源文件 `utils.cpp`** 说："我就是 utils 命名空间的实现。函数体在这里。"

```cpp
// utils.cpp — 这是"兑现"
namespace utils {
    std::optional<std::string> read_file(const std::string& path) {
        // 这里是函数体 ← 定义
    }
    bool write_file(...) { ... }
}
```

### 如果漏掉会怎样

```cpp
// utils.cpp — 假设漏掉了 namespace utils
std::optional<std::string> read_file(const std::string& path) {
    // ...
}
```

此时这个 `read_file` 属于**全局命名空间**（`::read_file`），而 `utils.h` 声明的是 `utils::read_file`。

- **编译 `utils.cpp`**：没问题，它定义了一个全局函数 `::read_file`
- **链接阶段**：`main.cpp` 在找 `utils::read_file` 的实现，但整个项目里只有 `::read_file`——**链接错误：undefined reference to `utils::read_file`**

### 类比：快递单号

```
头文件      →  快递单：「收件人：utils 小区，read_file 包裹」
源文件      →  包裹上的标签：「寄往：utils 小区，read_file 包裹」
```

两处的 `namespace utils` 必须一致，包裹才能送达。命名空间是函数全名的一部分，相当于姓。

---

## 十、Phase 2 完成：核心语法解析

> 记录时间：2026-06-08

### 架构设计

Phase 2 引入了 **Parser → 中间表示 → Renderer** 的分层架构：

```
原始 Markdown 字符串
      ↓  parse_markdown()
  std::vector<Block>        ← 中间表示（与 HTML 无关）
      ↓  render_html()
  完整 HTML 文档字符串
      ↓  write_file()
  output.html
```

### Block 数据结构

```cpp
struct Block {
    enum Type { Heading, Paragraph };
    Type type;
    int level;        // 1~6 用于标题，0 用于段落
    std::string text; // 内联标记（**、*）保留，由渲染器处理
};
```

### 解析器（parser.cpp）

逐行读取，状态机逻辑：
1. 遇到 `# ` ~ `###### ` 开头 → 输出 Heading 块
2. 遇到空行 → 结束当前段落，输出 Paragraph 块
3. 其他行 → 积累到段落缓冲区，连续非空行自动合并

同时兼容 Windows 换行符（`\r\n`），去掉行尾 `\r`。

### 渲染器（html_renderer.cpp）

`render_inline()` 函数分两步处理内联格式：
1. **先处理 `**`**：找 `**...**` 配对，替换为 `<strong>...</strong>`
2. **再处理 `*`**：找剩余的单个 `*...*`，替换为 `<em>...</em>`

顺序很重要——如果先处理 `*`，会把 `**` 内部的 `*` 误替换掉。

### 新增文件

| 文件 | 作用 |
|------|------|
| `src/parser.h` | Block 结构体 + parse_markdown 声明 |
| `src/parser.cpp` | 逐行解析实现（约 65 行） |
| `src/html_renderer.h` | render_html 声明 |
| `src/html_renderer.cpp` | HTML 文档拼接 + 内联格式转换（约 80 行） |

### 改动文件

- `src/main.cpp`：移除 `wrap_html` 函数，改为 `read_file → parse → render → write_file` 流水线
- `CMakeLists.txt`：`add_executable` 新增 `parser.cpp` + `html_renderer.cpp`

### 编译验证

```
[ 20%] main.cpp          ✅
[ 40%] utils.cpp         ✅
[ 60%] parser.cpp        ✅
[ 80%] html_renderer.cpp ✅
[100%] md2html.exe       ✅
```

5 个编译单元全部通过，零警告。

### 当前项目结构

```
2026-06-07-cpp-markdown-to-html/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   ├── utils.h / utils.cpp
│   ├── parser.h / parser.cpp              ← Phase 2 新增
│   └── html_renderer.h / html_renderer.cpp ← Phase 2 新增
├── test/
│   └── sample.md
├── Note.md
└── REASONIX.md
```

### 下一步（Phase 3）

- 无序列表 `- item` → `<ul><li>`
- 链接 `[text](url)` → `<a href>`
- 代码块 ` ``` ` → `<pre><code>`

---

## 十一、Phase 3 完成：进阶语法

> 记录时间：2026-06-08

### Block 类型扩展

Phase 3 向 Block 枚举新增了两种类型：

```cpp
struct Block {
    enum Type { Heading, Paragraph, UnorderedList, CodeBlock };
    Type type;
    int level;                          // 1~6 用于标题
    std::string text;                   // 标题/段落/代码块内容
    std::vector<std::string> items;     // 无序列表的列表项
};
```

### 无序列表解析

- 识别规则：以 `- `（减号+空格）开头的行
- 连续的 `- ` 行自动归入同一个 `<ul>` 块
- 遇到非 `- ` 行或空行时结束列表
- 列表项内部支持内联格式（`**粗体**`、`*斜体*`、`[链接]`）

```markdown
- 第一项：学习 **C++ 工程化**
- 第二项：掌握 *CMake* 构建系统
```
→
```html
<ul>
  <li>第一项：学习 <strong>C++ 工程化</strong></li>
  <li>第二项：掌握 <em>CMake</em> 构建系统</li>
</ul>
```

### 链接解析

在 `render_inline` 中新增第三步（`**` → `*` → `[text](url)`）：

```
查找 '[' → 找匹配的 ']' → 检查后面是否 '(' → 找 ')' → 替换为 <a>
```

```markdown
[Markdown 语法指南](https://www.markdownguide.org)
```
→
```html
<a href="https://www.markdownguide.org">Markdown 语法指南</a>
```

### 代码块解析

- 识别规则：以 ` ``` ` 开头的行为代码块开始/结束标记
- 中间的每一行原样保留，不解析任何 Markdown
- 渲染时对 `<` `>` `&` 做 HTML 实体转义（防止被浏览器当成标签）
- 未闭合的代码块在文件末尾自动收尾

```cpp
#include <iostream>
```
→
```html
<pre><code>#include &lt;iostream&gt;
</code></pre>
```

### 状态机演进

parser.cpp 现在有 4 个并行状态：

| 状态 | 变量 | 作用 |
|------|------|------|
| 段落积累 | `paragraph_buf` + `in_paragraph` | 连续非空行合并为 `<p>` |
| 列表积累 | `list_items` + `in_list` | 连续 `- ` 行合并为 `<ul>` |
| 代码块 | `code_buf` + `in_code_block` | ` ``` ` 之间的内容原样保留 |
| 标题 | 无状态，立即输出 | `# ` 开头直接生成 Heading 块 |

状态切换规则：
- 遇到标题 → 先 flush 段落和列表
- 遇到空行 → flush 段落和列表
- 遇到 `- ` → flush 段落，开始/继续列表
- 遇到普通文本 → flush 列表，开始/继续段落
- 遇到 ` ``` ` → flush 段落和列表，切换代码块模式

### 编译验证

```
[ 20%] main.cpp          ✅
[ 40%] parser.cpp        ✅
[ 60%] html_renderer.cpp ✅
[100%] md2html.exe       ✅
```

4 个编译单元全部通过，零警告。

### 下一步（Phase 4：收尾）

- 内联代码 `` `code` `` → `<code>`
- 水平线 `---` → `<hr>`
- 引用 `> text` → `<blockquote>`
- 完善 HTML 实体转义（段落/标题中的 `<` `>` `&`）

---

## 十二、Phase 4 完成：收尾 — 项目完结 🎉

> 记录时间：2026-06-08

### 新增 Block 类型

```cpp
enum Type { Heading, Paragraph, UnorderedList, CodeBlock, HorizontalRule, Blockquote };
```

### 水平线解析

判断逻辑 `is_horizontal_rule()`：
- 行仅由空格 + 同一字符（`-` `*` `_` 之一）组成
- 该字符至少出现 3 次
- 例如：`---`、`- - -`、`***`、`___`

### 引用块解析

- 以 `>` 开头的行（`> ` 或 `>`）
- 连续的 `>` 行自动合并为一个 blockquote
- 去掉前缀后的文本保留换行

### render_inline 最终顺序

```
1. 全局转义 < > &   →  &lt; &gt; &amp;   （保护用户文本中的 HTML 字符）
2. `代码`            →  <code>...</code>  （必须在粗体/斜体之前）
3. **粗体**          →  <strong>
4. *斜体*            →  <em>
5. [text](url)       →  <a href>
```

**为什么这个顺序？**
- 先转义：防止正文中的 `<` 被浏览器当标签解析
- 再内联代码：代码内容已经是转义过的文本，安全嵌入 `<code>`
- 最后粗体/斜体/链接：`**` `*` `[` 不受转义影响，正常匹配

### 代码块 vs 内联代码的区别

| | 代码块 ` ``` ` | 内联代码 `` ` `` |
|---|---|---|
| 解析层 | parser（块级） | renderer（行内） |
| 转义方式 | 独立转义，不走 render_inline | render_inline 第一步已转义 |
| 嵌套格式 | 不支持 | 不支持（代码内容原样保留） |

### 引用块嵌套

引用块支持完整的 inline 格式：`> **粗体** `代码` *斜体* [链接]`

```html
<blockquote>
<p><strong>引用块也支持内联格式</strong>：可以包含 <code>代码</code>、
<strong>粗体</strong>、<em>斜体</em> 和 <a href="...">链接</a>。</p>
</blockquote>
```

### CSS 新增

```css
blockquote { border-left: 4px solid #ccc; color: #666; }
hr { border-top: 2px solid #eee; margin: 2em 0; }
code { background: #f0f0f0; padding: 0.2em 0.4em; border-radius: 3px; }
```

### 编译验证

```
[ 20%] main.cpp          ✅
[ 40%] parser.cpp        ✅
[ 60%] html_renderer.cpp ✅
[100%] md2html.exe       ✅
```

零警告，零错误。

### 🎉 项目全阶段完成总结

```
Phase 1 ✅  骨架：CMake + 文件读写 + 静态链接
Phase 2 ✅  核心：标题/段落/粗体/斜体 + Parser-Renderer 架构
Phase 3 ✅  进阶：无序列表/链接/代码块
Phase 4 ✅  收尾：内联代码/水平线/引用块/全局实体转义
```

### 最终项目结构

```
2026-06-07-cpp-markdown-to-html/
├── CMakeLists.txt
├── src/
│   ├── main.cpp                           # CLI 入口，调度流水线
│   ├── utils.h / utils.cpp                # 文件读写
│   ├── parser.h / parser.cpp              # Markdown 解析器（6 种 Block 类型）
│   └── html_renderer.h / html_renderer.cpp # HTML 渲染器（5 步内联处理）
├── test/
│   └── sample.md                          # 全功能测试样本
├── Note.md                                # 本文件（12 章学习笔记）
└── REASONIX.md                            # Agent 权威参考
```

### 技术收获

| 技能 | 算竞习惯 | 工程习惯 |
|------|----------|----------|
| 项目组织 | 单文件 `main.cpp` | 5 个模块，头文件/源文件分离 |
| 构建 | `g++ main.cpp -o a.exe` | CMake + 静态链接 |
| 错误处理 | 不管边界 | `std::optional` |
| 字符串 | `char[]` | `std::string` + `std::string_view` |
| 代码结构 | 过程式 | 状态机 + 中间表示（Block） |
| 命名空间 | 无 | `namespace utils` |
| 内联格式 | N/A | 正则式查找替换，注意顺序 |

---

## 十三、前端可视化探索（WASM 受阻 → Express 方案）

> 记录时间：2026-06-08

### 初始方向：C++ → WebAssembly

尝试用 Emscripten 把 md2html 编译为 `.wasm`，在浏览器中直接运行 C++ 代码。

**遇到的问题：**
- `emcc` 不可用，需通过 emsdk 安装
- emsdk 需要 Python（当前 Windows 环境仅 WindowsApps stub，无法使用）
- 完整安装需下载 LLVM + Binaryen + Node.js（数 GB）
- GitHub HTTPS 被墙，改用 SSH clone 成功，但 Python 缺失导致后续安装失败

**结论：** Emscripten 工具链在当前环境搭建成本过高，不适合快速原型。

### 最终方案：Express 后端 + C++ 二进制

```
浏览器                     Node.js 服务器              C++
┌──────────┐  POST /api   ┌──────────────┐  spawn    ┌──────────────┐
│ textarea │ ──────────►  │ server.js    │ ────────► │ md2html.exe  │
│          │              │              │           │              │
│ iframe   │ ◄──────────  │ temp 文件 I/O │ ◄──────── │ parser+render│
└──────────┘  HTML 返回   └──────────────┘           └──────────────┘
```

**优势：**
- 使用已编译好的 `md2html.exe`，零额外依赖
- 复用现有 Node.js / Express 知识（Todo Kanban 项目经验）
- 真正的 C++ 代码在跑，不是 JS 模拟
- 服务器 50 行代码即可实现

**已完成（2026-06-08）：**
- ✅ `web/server.js` — Express 5 后端，50 行
- ✅ `web/index.html` — 暗色主题，左右分栏，400ms 防抖自动转换
- ✅ 启动：`cd web && npm install && npm start` → http://localhost:3001

### 实现细节

**server.js 架构：**
- `POST /api/convert` 接收 `{ markdown: "..." }` JSON
- 创建临时目录 → 写入 `.md` → spawn `../build/md2html.exe` → 读取 `.html` → 清理临时文件 → 返回 HTML
- 10 秒超时保护
- 启动时检查 `md2html.exe` 是否存在

**index.html 特性：**
- 暗色主题（`#1a1a2e`），左右分栏布局
- 移动端自动切换为上下布局
- 状态指示灯：绿=就绪，橙=转换中，红=错误
- Tab 键插入 4 空格缩进
- 内置示例 Markdown，开箱即用
- `iframe srcdoc` 安全渲染，避免 XSS

### 数据流

```
用户输入 Markdown
    │  400ms 防抖
    ▼
fetch POST /api/convert { markdown }
    │
    ▼
server.js 写临时 .md 文件
    │
    ▼
spawn md2html.exe input.md output.html  ← 真正的 C++ 在跑
    │
    ▼
读取 output.html，返回 JSON { html }
    │
    ▼
preview.srcdoc = html  ← iframe 实时预览
```

### 为什么不用 WASM

最初计划用 Emscripten 编译为 WebAssembly，但遇到多个阻碍：
1. `emcc` 未安装，需通过 emsdk 安装
2. emsdk 需要 Python（当前环境仅 WindowsApps stub）
3. 完整工具链需数 GB 下载（LLVM + Binaryen + Node.js）

相比之下，Express + spawn C++ 二进制方案：
- 使用已编译好的 `md2html.exe`，零额外依赖
- 复用现有 Node.js 知识
- 真正的 C++ 代码在跑，性能无折扣
- 50 行后端代码即实现
