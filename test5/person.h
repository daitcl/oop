/**
 * person.h
 * Person 类的公有接口声明。
 * 采用私有数据封装，支持栈对象初始化与清理。
 */

#ifndef PERSON_H
#define PERSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 前向声明，隐藏私有数据的具体结构 */
typedef struct PersonPrivate PersonPrivate;

/**
 * 公有接口结构体 Person
 * 包含一个指向私有数据的指针和一组函数指针成员。
 */
typedef struct Person {
    PersonPrivate* private_;    /**< 指向私有数据的指针（不透明） */

    /* 公有行为（函数指针） */
    void (*print)(struct Person* self);
    void (*sayHello)(struct Person* self);
    void (*destroy)(struct Person* self);
    void (*setAge)(struct Person* self, int age);
    int  (*getAge)(struct Person* self);
    const char* (*getName)(struct Person* self);
    void (*setName)(struct Person* self, const char* name);
} Person;

/* 构造函数（堆对象） */
Person* Person_new(void);
Person* Person_newWith(int age, const char* name);

/* 栈对象初始化与清理 */
void Person_init(Person* self);
void Person_cleanup(Person* self);

#endif /* PERSON_H */