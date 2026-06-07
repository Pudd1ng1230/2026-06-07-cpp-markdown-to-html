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
