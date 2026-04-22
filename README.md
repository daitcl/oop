# C 语言面向对象编程（OOP）示例合集

从零开始，用纯 C 语言模拟类、封装、成员函数、this 指针、信息隐藏、继承与多态。  
每个示例均包含完整代码与详细注释，适合学习 C 语言底层 OOP 原理。

## 文件结构
```
.
├── test1.c # 基础结构体 + 独立函数
├── test2.c # 结构体内嵌函数指针（模拟成员函数）
├── test3.c # 全局 this 指针 + 宏（无参调用）
├── test4.c # 私有数据封装 + 不透明指针
├── test5/ # 多文件 + 栈/堆对象（推荐工程结构）
│ ├── person.h
│ ├── person.c
│ ├── test5.c
│ └── Makefile
├── test6.c # 简单继承（独立函数指针）
├── test7.c # 虚函数表（vtable）实现多态
├── test8/ # 虚表 + 多文件 + const 保护
│ ├── person.h / .c
│ ├── student.h / .c
│ ├── main.c
│ └── Makefile
└── 教程文档.md # 配套详细教程
```
## 示例速览

| 文件 | 核心知识点 |
|------|-----------|
| `test1.c` | 数据封装、堆/栈对象、构造/析构函数 |
| `test2.c` | 函数指针成员、成员函数绑定 |
| `test3.c` | 全局 `this` 模拟、宏链式调用 |
| `test4.c` | 不透明指针、私有数据隐藏 |
| `test5/` | 多文件组织、`init`/`cleanup` 支持栈对象 |
| `test6.c` | 结构体嵌套实现继承、行为重写与复用 |
| `test7.c` | 虚函数表（vtable）、运行时多态 |
| `test8/` | 虚表工程化、`const` 保护、分发函数 |

## 编译与运行

### 单文件示例（test1~4、6~7）
```bash
gcc test1.c -o test1 && ./test1
```

### 多文件示例（test5、test8）

进入对应目录，使用 `make`：

```bash
cd test5
make          # 编译并运行
make clean    # 清理生成文件
```

或手动编译：

```bash
gcc -c person.c -o person.o
gcc -c test5.c -o test5.o
gcc person.o test5.o -o test5
./test5
```

## 环境要求

- GCC / Clang 或其他支持 C99 的编译器
- GNU Make（可选，用于多文件项目）
- 任何操作系统（Linux、macOS、Windows）
