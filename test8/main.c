/**
 * main.c
 * 演示多态调用：通过基类接口操作派生类对象。
 */

#include "person.h"
#include "student.h"

int main(void) {
    /* 创建对象 */
    Person* p = Person_newWith("Alice", 30);
    Student* s = Student_newWith("Bob", 20, "XYZ University");

    /* 基类对象调用 */
    Person_print(p);
    Person_greet(p);

    /* 派生类对象调用（需显式向上转型为 Person*） */
    Person_print((Person*)s);   /* 多态：实际调用 Student_print_impl */
    Person_greet((Person*)s);   /* 多态：实际调用 Student_greet_impl */

    /* 销毁对象 */
    Person_destroy(p);
    Person_destroy((Person*)s);

    return 0;
}