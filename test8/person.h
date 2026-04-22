/**
 * person.h
 * Person 基类的公有接口声明。
 * 采用虚函数表（vtable）实现多态，虚表指针用 const 保护。
 */

#ifndef PERSON_H
#define PERSON_H

#include <stdio.h>

/* 前向声明 */
typedef struct Person Person;
typedef struct VTable VTable;

/**
 * 虚函数表结构
 * 存储函数指针，每个类有一份静态常量实例。
 */
struct VTable {
    void (*print)(void* self);      /**< 打印信息 */
    void (*greet)(void* self);      /**< 打招呼 */
    void (*destroy)(void* self);    /**< 析构函数 */
};

/**
 * 基类 Person
 * 包含虚表指针和数据成员。
 */
struct Person {
    const VTable* vtable_;  /**< 指向虚表的指针（const 保护，不可修改） */
    char name_[50];         /**< 姓名 */
    int age_;               /**< 年龄 */
};

/* 构造函数（堆对象） */
Person* Person_new(void);
Person* Person_newWith(const char* name, int age);

/* 多态接口函数（通过虚表分发） */
void Person_print(Person* self);
void Person_greet(Person* self);
void Person_destroy(Person* self);

/* 实际行为函数（供虚表绑定） */
void Person_print_impl(void* self);
void Person_greet_impl(void* self);
void Person_destroy_impl(void* self);

#endif /* PERSON_H */