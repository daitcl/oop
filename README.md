<h2 align="center">C 语言面向对象编程（OOP）示例合集</h2>

<div align="center">
  <a href="https://github.com/daitcl/Qt-demo/blob/main/License"><img src="https://img.shields.io/badge/License-MIT-yellow?style=flat-square" alt="MIT许可证"></a>
  <a href="https://www.daitcc.top"><img src="https://img.shields.io/badge/个人主页-daitcc.top-blue?style=flat-square" alt="个人主页"></a>
  <a href="https://blog.csdn.net/qq_39538318" target="_blank"><img src="https://img.shields.io/badge/CSDN-博客-red?logo=csdn" /></a>
  <a href="https://ifdian.net/a/daitcc" target="_blank"><img src="https://img.shields.io/badge/爱发电-赞助-946ce6?logo=afdian" /></a>
</div>


从零开始，用纯 C 语言模拟类、封装、成员函数、this 指针、信息隐藏、继承与多态。  
每个示例均包含完整代码与详细注释，适合学习 C 语言底层 OOP 原理。

### 文件结构
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
### 示例速览

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

### 编译与运行

#### 单文件示例（test1~4、6~7）
```bash
gcc test1.c -o test1 && ./test1
```

#### 多文件示例（test5、test8）

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

### 环境要求

- GCC / Clang 或其他支持 C99 的编译器
- GNU Make（可选，用于多文件项目）
- 任何操作系统（Linux、macOS、Windows）

### 📄 许可证

>
>协议：[MIT](License) — 允许任何人自由使用、复制、修改、合并、发布、分发、再授权和/或销售软件的副本，前提是保留原始版权声明和许可声明。
>
>免责声明：软件按“原样”提供，不附带任何明示或暗示的保证，包括但不限于适销性、特定用途适用性和非侵权的保证。在任何情况下，作者或版权持有人均不对任何索赔、损害或其他责任负责，无论是在合同诉讼、侵权诉讼或其他诉讼中，由于软件或软件的使用或其他交易引起的。
>

### 🔗 来找我

- **CSDN**：[daitcl的博客](https://blog.csdn.net/qq_39538318) — csdn、技术文章和教程
- **GitHub**：[@daitcl](https://github.com/daitcl) —  个人代码仓库（**gitee/gitcode**同名同步）
- **爱发电**：[爱发电主页](https://ifdian.net/a/daitcc) — 欢迎支持、分享或合作
- **个人主页**：[daitcc.top](https://www.daitcc.top) — 个人主页、技术文章和教程
- **邮箱**：daitcctop@163.com — 欢迎交流、指正或闲聊
- **微信公众号**：扫一扫下方二维码，关注公众号获取更新推送  
  <img src="https://raw.gitcode.com/daitcl/picgo/raw/main/wechat_qrcode.jpg" alt="微信公众号二维码" width="150" />

### ☕ 支持与鼓励

>
> 如果代码对你有所启发，或者单纯想请我喝杯咖啡，可以通过下方的 **爱发电** 或者 **支付宝/微信赞赏码** 来支持我创作。每一份鼓励都是我持续创作的动力。
>

- **爱发电**：[赞助作者](https://ifdian.net/a/daitcc) — 点击链接即可支持  
  <img src="https://raw.gitcode.com/daitcl/picgo/raw/main/ifdian.png" alt="爱发电" width="150" />
  
- **支付宝赞赏**：扫一扫下方二维码  
  <img src="https://raw.gitcode.com/daitcl/picgo/raw/main/alipay.png" alt="支付宝收款码" width="150" />      

- **微信赞赏**：扫一扫下方二维码  
  <img src="https://raw.gitcode.com/daitcl/picgo/raw/main/wechatpay.png" alt="微信赞赏码" width="150" />

>
>“独行快，众行远。” 感谢你的每一次阅读、点赞和分享。  
>期待在技术道路上，与你并肩前行。
