/**
 * student.c
 * Student 派生类的实现。
 * 包含静态虚表定义和重写的成员函数。
 */

#include "student.h"
#include <stdlib.h>
#include <string.h>

/* 静态虚表（const 保护，所有 Student 实例共享） */
static const VTable Student_vtable = {
    .print   = Student_print_impl,
    .greet   = Student_greet_impl,
    .destroy = Student_destroy_impl
};

Student* Student_new(void) {
    Student* self = (Student*)malloc(sizeof(Student));
    if (!self) return NULL;

    self->base_.vtable_ = &Student_vtable;   /* 绑定派生类虚表（多态关键） */
    self->base_.name_[0] = '\0';
    self->base_.age_ = 0;
    self->school_[0] = '\0';
    return self;
}

Student* Student_newWith(const char* name, int age, const char* school) {
    Student* self = Student_new();
    if (!self) return NULL;

    strncpy(self->base_.name_, name, sizeof(self->base_.name_) - 1);
    self->base_.name_[sizeof(self->base_.name_) - 1] = '\0';
    self->base_.age_ = age;

    strncpy(self->school_, school, sizeof(self->school_) - 1);
    self->school_[sizeof(self->school_) - 1] = '\0';
    return self;
}

/* 重写 print */
void Student_print_impl(void* self) {
    Student* s = (Student*)self;
    printf("[Student] Name: %s, Age: %d, School: %s\n",
           s->base_.name_, s->base_.age_, s->school_);
}

/* 重写 greet */
void Student_greet_impl(void* self) {
    Student* s = (Student*)self;
    printf("[Student] Hello, I'm %s from %s!\n",
           s->base_.name_, s->school_);
}

/* 析构函数（可扩展，目前直接释放） */
void Student_destroy_impl(void* self) {
    free(self);
}