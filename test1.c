/**
 * test1.c
 * 最简单的 C 语言结构体用法，数据与函数分离。
 * 演示栈对象和堆对象的创建、使用与销毁。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 结构体：Person，表示人的基本信息 */
typedef struct Person {
    int age_;           /**< 年龄 */
    char name_[50];     /**< 姓名（最多 49 个有效字符 + '\0'） */
} Person;

/**
 * @brief 在堆上创建 Person 对象（无参构造）
 * @return 成功返回指向 Person 的指针，失败返回 NULL
 */
Person* Person_new(void) {
    Person* self = (Person*)malloc(sizeof(Person));
    if (self == NULL) {
        return NULL;    /* 内存分配失败 */
    }

    /* 初始化为安全的默认值 */
    self->age_ = 0;
    self->name_[0] = '\0';
    return self;
}

/**
 * @brief 在堆上创建 Person 对象，并用指定参数初始化
 * @param age  年龄
 * @param name 姓名（C 字符串）
 * @return 成功返回指向 Person 的指针，失败返回 NULL
 */
Person* Person_newWith(int age, const char* name) {
    Person* self = Person_new();   /* 复用无参构造 */
    if (self == NULL) {
        return NULL;
    }

    self->age_ = age;

    /* 安全复制姓名，防止缓冲区溢出 */
    strncpy(self->name_, name, sizeof(self->name_) - 1);
    self->name_[sizeof(self->name_) - 1] = '\0';   /* 确保以 '\0' 结尾 */
    return self;
}

/**
 * @brief 打印 Person 对象的信息
 * @param self 指向 Person 对象的指针
 */
void Person_print(Person* self) {
    if (self != NULL) {
        printf("年龄：%d，姓名：%s\n", self->age_, self->name_);
    }
}

/**
 * @brief 让 Person 对象打招呼
 * @param self 指向 Person 对象的指针
 */
void Person_sayHello(Person* self) {
    if (self != NULL) {
        printf("%s说：你好！\n", self->name_);
    }
}

/**
 * @brief 销毁堆上创建的 Person 对象（释放内存）
 * @param self 指向待销毁对象的指针
 */
void Person_delete(Person* self) {
    free(self);
}

int main(void) {
    /* ---------- 方式 1：栈上对象 ---------- */
    Person p1 = {18, "张三"};       /* 直接初始化 */
    Person_print(&p1);              /* 传递栈对象的地址 */

    /* ---------- 方式 2：堆上对象 ---------- */
    Person* p2 = Person_newWith(20, "李四");
    if (p2 != NULL) {
        Person_print(p2);
        Person_delete(p2);          /* 必须手动释放，防止内存泄漏 */
    }

    return 0;
}