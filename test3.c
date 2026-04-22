/**
 * test3.c
 * 引入全局指针 person_this 模拟 C++ 的 this 指针，使成员函数无需显式传参。
 * 通过宏 PERSON_CAST(object) 设置当前对象，支持链式调用。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person Person;

struct Person {
    int age_;
    char name_[50];

    /* 函数指针成员，均为无参函数（依赖全局 person_this） */
    void (*print_)(void);
    void (*sayHello_)(void);
    void (*destroy_)(void);
};

/* 全局 this 指针，指向当前操作的对象 */
Person* person_this = NULL;

/**
 * 宏：PERSON_CAST
 * 将全局 person_this 设置为指定的对象指针，并返回该指针，以支持链式调用。
 * 示例：PERSON_CAST(p2)->print_();
 */
#define PERSON_CAST(object) (person_this = object)

/* 函数原型 */
void Person_print_impl(void);
void Person_sayHello_impl(void);
void Person_destroy_impl(void);
Person* Person_new(void);
Person* Person_newWith(int age, const char* name);

/**
 * @brief 堆上创建 Person 对象（无参）
 */
Person* Person_new(void) {
    Person* self = (Person*)malloc(sizeof(Person));
    if (self == NULL) return NULL;

    self->age_ = 0;
    self->name_[0] = '\0';

    self->print_    = Person_print_impl;
    self->sayHello_ = Person_sayHello_impl;
    self->destroy_  = Person_destroy_impl;

    person_this = self;   /* 自动将新对象设为当前对象 */
    return self;
}

/**
 * @brief 堆上创建 Person 对象（带参）
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
 * @brief 打印信息（无参，通过 person_this 访问对象）
 */
void Person_print_impl(void) {
    if (person_this != NULL) {
        printf("年龄：%d，姓名：%s\n", person_this->age_, person_this->name_);
    }
}

void Person_sayHello_impl(void) {
    if (person_this != NULL) {
        printf("%s说：你好！\n", person_this->name_);
    }
}

void Person_destroy_impl(void) {
    free(person_this);
    /* 注意：未将 person_this 置为 NULL，外部需自行管理 */
}

int main(void) {
    /* ---------- 栈上对象 ---------- */
    Person p1;
    p1.age_ = 18;
    strcpy(p1.name_, "张三");

    p1.print_    = Person_print_impl;
    p1.sayHello_ = Person_sayHello_impl;
    p1.destroy_  = Person_destroy_impl;

    person_this = &p1;   /* 设置当前对象为 p1 */
    p1.print_();         /* 无参调用 */

    /* ---------- 堆上对象 ---------- */
    Person* p2 = Person_newWith(20, "李四");
    if (p2 != NULL) {
        PERSON_CAST(p2)->print_();   /* 通过宏设置 this 并调用 */
        PERSON_CAST(p2)->destroy_();
    }

    return 0;
}