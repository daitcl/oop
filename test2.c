/**
 * test2.c
 * 在结构体中添加函数指针成员，模拟 C++ 的成员函数。
 * 每个对象单独存储函数指针（内存开销较大），通过指针调用实现行为绑定。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 前向声明，便于结构体内使用自身类型指针 */
typedef struct Person Person;

/**
 * 结构体：Person
 * 包含数据成员（age_, name_）和函数指针成员（print_, sayHello_, destroy_）。
 */
struct Person {
    int age_;               /**< 年龄 */
    char name_[50];         /**< 姓名 */

    /* 函数指针成员（模拟成员函数） */
    void (*print_)(Person* self);       /**< 打印信息 */
    void (*sayHello_)(Person* self);    /**< 打招呼 */
    void (*destroy_)(Person* self);     /**< 销毁对象（仅用于堆对象） */
};

/* 函数实现的原型声明 */
void Person_print_impl(Person* self);
void Person_sayHello_impl(Person* self);
void Person_destroy_impl(Person* self);

/**
 * @brief 在堆上创建 Person 对象（无参构造）
 * @return 成功返回指向 Person 的指针，失败返回 NULL
 */
Person* Person_new(void) {
    Person* self = (Person*)malloc(sizeof(Person));
    if (self == NULL) return NULL;

    /* 初始化数据成员 */
    self->age_ = 0;
    self->name_[0] = '\0';

    /* 绑定函数指针（每个对象独立存储一份） */
    self->print_    = Person_print_impl;
    self->sayHello_ = Person_sayHello_impl;
    self->destroy_  = Person_destroy_impl;

    return self;
}

/**
 * @brief 在堆上创建 Person 对象，并用指定参数初始化
 * @param age  年龄
 * @param name 姓名
 * @return 成功返回指向 Person 的指针，失败返回 NULL
 */
Person* Person_newWith(int age, const char* name) {
    Person* self = Person_new();
    if (self == NULL) return NULL;

    self->age_ = age;
    strncpy(self->name_, name, sizeof(self->name_) - 1);
    self->name_[sizeof(self->name_) - 1] = '\0';
    return self;
}

/**
 * @brief 打印 Person 对象信息（函数指针绑定的实现）
 * @param self 指向当前对象的指针
 */
void Person_print_impl(Person* self) {
    if (self != NULL) {
        printf("年龄：%d，姓名：%s\n", self->age_, self->name_);
    }
}

/**
 * @brief 打招呼的实现
 */
void Person_sayHello_impl(Person* self) {
    if (self != NULL) {
        printf("%s说：你好！\n", self->name_);
    }
}

/**
 * @brief 销毁堆对象的实现
 */
void Person_destroy_impl(Person* self) {
    free(self);
}

int main(void) {
    /* ---------- 栈上对象：必须手动初始化函数指针 ---------- */
    Person p1;
    p1.age_ = 18;
    strcpy(p1.name_, "张三");

    /* 绑定函数指针（若未绑定直接调用会导致段错误） */
    p1.print_    = Person_print_impl;
    p1.sayHello_ = Person_sayHello_impl;
    p1.destroy_  = Person_destroy_impl;   /* 栈对象通常不应调用 destroy_ */

    p1.print_(&p1);   /* 通过函数指针调用，需显式传入对象自身 */

    /* ---------- 堆上对象：构造函数已自动绑定 ---------- */
    Person* p2 = Person_newWith(20, "李四");
    if (p2 != NULL) {
        p2->print_(p2);
        p2->destroy_(p2);   /* 释放堆内存 */
    }

    return 0;
}