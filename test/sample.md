# 欢迎使用 md2html

这是**第一个**段落，用于测试基本的 Markdown 转换功能。

## 第二阶段计划

目前 Phase 1 只是把原文包裹成 HTML，不做任何解析。

### 待实现功能

- 标题 → h1~h6
- 段落 → p 标签
- 粗体 / 斜体
- 以及更多……

> 这是我学习 C++ 工程的第一个项目喵。

---

## Phase 3 测试：无序列表

- 第一项：学习 **C++ 工程化**
- 第二项：掌握 *CMake* 构建系统
- 第三项：理解编译链接原理

## Phase 3 测试：链接

这是一个 [Markdown 语法指南](https://www.markdownguide.org) 的链接。

也可以访问 [GitHub](https://github.com) 查看源码。

## Phase 3 测试：代码块

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, md2html!" << std::endl;
    return 0;
}
```

---

## Phase 4 测试：内联代码

使用 `std::string` 类型来存储文本，记得 `#include <string>`。

注意 `5 < 10` 的比较——尖括号应该被转义。

## Phase 4 测试：引用块嵌套格式

> **引用块也支持内联格式**：可以包含 `代码`、**粗体**、*斜体* 和 [链接](https://example.com)。
