/**
 * test7.c
 * C 语言模拟面向对象：虚函数表（vtable）实现继承与多态。
 * 
 * 设计思路：
 * 1. 定义虚函数表结构 VTable，存储函数指针。
 * 2. 基类 Person 包含指向虚表的指针 vtable，所有派生类共享同一虚表实例。
 * 3. 派生类 Student 将 Person 作为第一个成员，内存布局上 Person 部分在前。
 * 4. 每个类有一个静态虚表实例（Person_vtable、Student_vtable）。
 * 5. 构造函数将对象的 vtable 指针指向所属类的虚表。
 * 6. 通过 obj->vtable->print(obj) 间接调用，实现运行时多态。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --------------------------------------------------------------------------
 * 虚函数表结构
 * -------------------------------------------------------------------------- */
typedef struct VTable {
    void (*print)(void* self);   /**< 打印信息 */
    void (*greet)(void* self);   /**< 打招呼 */
    /* 可扩展：void (*destroy)(void* self); */
} VTable;

/* --------------------------------------------------------------------------
 * 基类：Person
 * -------------------------------------------------------------------------- */
typedef struct Person {
    VTable* vtable;     /**< 指向虚函数表的指针（多态核心） */
    char name[50];      /**< 姓名 */
    int age;            /**< 年龄 */
} Person;

/* --------------------------------------------------------------------------
 * 派生类：Student
 * -------------------------------------------------------------------------- */
typedef struct Student {
    Person base;        /**< 继承自 Person（必须为第一个成员） */
    char school[50];    /**< 子类新增属性：学校 */
} Student;

/* --------------------------------------------------------------------------
 * 函数声明
 * -------------------------------------------------------------------------- */
/* Person 构造函数 */
Person* Person_new(void);
Person* Person_newWith(const char* name, int age);

/* Person 虚函数实现 */
void Person_print_impl(void* self);
void Person_greet_impl(void* self);

/* Student 构造函数 */
Student* Student_new(void);
Student* Student_newWith(const char* name, int age, const char* school);

/* Student 重写的虚函数实现 */
void Student_print_impl(void* self);
void Student_greet_impl(void* self);

/* --------------------------------------------------------------------------
 * 全局静态虚表（每个类一份，所有实例共享）
 * 理想情况应加 const，此处为兼容赋值未加 const
 * -------------------------------------------------------------------------- */
static VTable Person_vtable = {
    .print = Person_print_impl,
    .greet = Person_greet_impl
};

static VTable Student_vtable = {
    .print = Student_print_impl,
    .greet = Student_greet_impl
};

/* --------------------------------------------------------------------------
 * 主函数：演示多态
 * -------------------------------------------------------------------------- */
int main(void) {
    /* 创建基类对象 */
    Person* person = Person_newWith("Alice", 30);
    /* 创建派生类对象 */
    Student* student = Student_newWith("Bob", 20, "XYZ University");

    /* 基类对象调用 */
    if (person) {
        person->vtable->print(person);   /* 实际调用 Person_print_impl */
        person->vtable->greet(person);   /* 实际调用 Person_greet_impl */
        free(person);
    }

    /* 派生类对象调用（多态） */
    if (student) {
        /* 方式一：显式向上转型为 Person* */
        Person* p_student = (Person*)student;
        p_student->vtable->print(p_student);   /* 多态：调用 Student_print_impl */
        p_student->vtable->greet(p_student);   /* 多态：调用 Student_greet_impl */

        /* 方式二：直接通过 base 成员访问虚表（无需转型） */
        student->base.vtable->print(student);   /* 同样多态 */
        student->base.vtable->greet(student);

        free(student);
    }

    return 0;
}

/* ==========================================================================
 * Person 基类实现
 * ========================================================================== */

Person* Person_new(void) {
    Person* self = (Person*)malloc(sizeof(Person));
    if (!self) return NULL;

    self->vtable = &Person_vtable;   /* 绑定基类虚表 */
    self->name[0] = '\0';
    self->age = 0;
    return self;
}

Person* Person_newWith(const char* name, int age) {
    Person* self = Person_new();
    if (!self) return NULL;

    strncpy(self->name, name, sizeof(self->name) - 1);
    self->name[sizeof(self->name) - 1] = '\0';
    self->age = age;
    return self;
}

void Person_print_impl(void* self) {
    Person* p = (Person*)self;
    printf("[Person] 姓名：%s，年龄：%d\n", p->name, p->age);
}

void Person_greet_impl(void* self) {
    Person* p = (Person*)self;
    printf("[Person] 你好，我是%s！\n", p->name);
}

/* ==========================================================================
 * Student 派生类实现
 * ========================================================================== */

Student* Student_new(void) {
    Student* self = (Student*)malloc(sizeof(Student));
    if (!self) return NULL;

    self->base.vtable = &Student_vtable;   /* 绑定派生类虚表（多态关键） */
    self->base.name[0] = '\0';
    self->base.age = 0;
    self->school[0] = '\0';
    return self;
}

Student* Student_newWith(const char* name, int age, const char* school) {
    Student* self = Student_new();
    if (!self) return NULL;

    strncpy(self->base.name, name, sizeof(self->base.name) - 1);
    self->base.name[sizeof(self->base.name) - 1] = '\0';
    self->base.age = age;

    strncpy(self->school, school, sizeof(self->school) - 1);
    self->school[sizeof(self->school) - 1] = '\0';
    return self;
}

void Student_print_impl(void* self) {
    Student* s = (Student*)self;
    printf("[Student] 姓名：%s，年龄：%d，学校：%s\n",
           s->base.name, s->base.age, s->school);
}

void Student_greet_impl(void* self) {
    Student* s = (Student*)self;
    printf("[Student] 你好，我是%s，来自%s！\n",
           s->base.name, s->school);
}