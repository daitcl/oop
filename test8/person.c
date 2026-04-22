/**
 * person.c
 * Person 基类的实现。
 * 包含静态虚表定义和成员函数实现。
 */

#include "person.h"
#include <stdlib.h>
#include <string.h>

/* 静态虚表（const 保护，所有 Person 实例共享） */
static const VTable Person_vtable = {
    .print   = Person_print_impl,
    .greet   = Person_greet_impl,
    .destroy = Person_destroy_impl
};

Person* Person_new(void) {
    Person* self = (Person*)malloc(sizeof(Person));
    if (!self) return NULL;

    self->vtable_ = &Person_vtable;   /* 绑定基类虚表 */
    self->name_[0] = '\0';
    self->age_ = 0;
    return self;
}

Person* Person_newWith(const char* name, int age) {
    Person* self = Person_new();
    if (!self) return NULL;

    strncpy(self->name_, name, sizeof(self->name_) - 1);
    self->name_[sizeof(self->name_) - 1] = '\0';
    self->age_ = age;
    return self;
}

/* 分发函数：通过虚表指针间接调用实际函数 */
void Person_print(Person* self) {
    if (self && self->vtable_) {
        self->vtable_->print(self);
    }
}

void Person_greet(Person* self) {
    if (self && self->vtable_) {
        self->vtable_->greet(self);
    }
}

void Person_destroy(Person* self) {
    if (self && self->vtable_) {
        self->vtable_->destroy(self);
    }
}

/* 行为实现 */
void Person_print_impl(void* self) {
    Person* p = (Person*)self;
    printf("[Person] Name: %s, Age: %d\n", p->name_, p->age_);
}

void Person_greet_impl(void* self) {
    Person* p = (Person*)self;
    printf("[Person] Hello, I'm %s!\n", p->name_);
}

void Person_destroy_impl(void* self) {
    free(self);
}