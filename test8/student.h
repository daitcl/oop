/**
 * student.h
 * Student 派生类的公有接口声明。
 * 继承自 Person，并重写部分虚函数。
 */

#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"

/**
 * 派生类 Student
 * 通过将 Person 作为第一个成员实现继承。
 */
typedef struct Student {
    Person base_;       /**< 继承自 Person */
    char school_[50];   /**< 子类新增属性：学校 */
} Student;

/* 构造函数 */
Student* Student_new(void);
Student* Student_newWith(const char* name, int age, const char* school);

/* 重写行为（供虚表绑定） */
void Student_print_impl(void* self);
void Student_greet_impl(void* self);
void Student_destroy_impl(void* self);

#endif /* STUDENT_H */