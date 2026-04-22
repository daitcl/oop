/**
 * test6.c
 * C 语言模拟继承：每个对象独立存储函数指针。
 * 
 * 设计思路：
 * 1. 基类 Person 包含数据成员和函数指针成员（print_、greet_）。
 * 2. 派生类 Student 将 Person 作为第一个成员（base_），实现结构继承。
 * 3. 构造函数中显式绑定函数指针：子类可重写 print_，也可直接复用父类的 greet_。
 * 4. 调用时通过 obj->base_.print_(obj) 实现行为分发（静态绑定，无虚表）。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --------------------------------------------------------------------------
 * 基类：Person（人类）
 * -------------------------------------------------------------------------- */
typedef struct Person {
    char name_[50];                 /**< 姓名 */
    int age_;                       /**< 年龄 */
    void (*print_)(void* self);     /**< 打印信息 */
    void (*greet_)(void* self);     /**< 打招呼 */
} Person;

/* Person 构造函数 */
Person* Person_new(void);
Person* Person_newWith(const char* name, int age);

/* Person 行为实现（供函数指针绑定） */
void Person_print_impl(void* self);
void Person_greet_impl(void* self);

/* --------------------------------------------------------------------------
 * 派生类：Student（学生类）
 * -------------------------------------------------------------------------- */
typedef struct Student {
    Person base_;           /**< 继承父类的属性和函数指针 */
    char school_[50];       /**< 子类新增属性：学校 */
} Student;

/* Student 构造函数 */
Student* Student_new(void);
Student* Student_newWith(const char* name, int age, const char* school);

/* Student 重写的行为（只重写 print_，greet_ 继承自父类） */
void Student_print_impl(void* self);
/* 注意：不定义 Student_greet_impl，直接继承父类的 greet_ */

/* --------------------------------------------------------------------------
 * 主函数：演示继承与重写
 * -------------------------------------------------------------------------- */
int main(void) {
    /* 创建父类对象 */
    Person* person = Person_newWith("Alice", 30);
    if (person) {
        person->print_(person);   /* 调用 Person_print_impl */
        person->greet_(person);   /* 调用 Person_greet_impl */
        free(person);
    }

    /* 创建子类对象 */
    Student* student = Student_newWith("Bob", 20, "XYZ University");
    if (student) {
        /* 通过继承来的函数指针调用
         * print_ 已被子类构造函数重写为 Student_print_impl
         * greet_ 继承自父类，指向 Person_greet_impl */
        student->base_.print_(student);   /* 输出包含学校信息 */
        student->base_.greet_(student);   /* 输出父类风格的问候 */
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

    /* 初始化数据成员 */
    self->name_[0] = '\0';
    self->age_ = 0;

    /* 绑定函数指针（每个对象独立存储一份） */
    self->print_ = Person_print_impl;
    self->greet_ = Person_greet_impl;

    return self;
}

Person* Person_newWith(const char* name, int age) {
    Person* self = Person_new();
    if (!self) return NULL;

    /* 安全复制姓名 */
    strncpy(self->name_, name, sizeof(self->name_) - 1);
    self->name_[sizeof(self->name_) - 1] = '\0';
    self->age_ = age;
    return self;
}

void Person_print_impl(void* self) {
    Person* p = (Person*)self;
    printf("[Person] 姓名：%s，年龄：%d\n", p->name_, p->age_);
}

void Person_greet_impl(void* self) {
    Person* p = (Person*)self;
    printf("[Person] 你好，我是%s！\n", p->name_);
}

/* ==========================================================================
 * Student 派生类实现
 * ========================================================================== */

Student* Student_new(void) {
    Student* self = (Student*)malloc(sizeof(Student));
    if (!self) return NULL;

    /* 初始化基类部分 */
    self->base_.name_[0] = '\0';
    self->base_.age_ = 0;
    self->school_[0] = '\0';

    /* 关键：初始化函数指针
     * print_ 重写为子类版本（多态）
     * greet_ 继承父类版本（直接赋值为父类函数） */
    self->base_.print_ = Student_print_impl;
    self->base_.greet_ = Person_greet_impl;   /* 行为继承 */

    return self;
}

Student* Student_newWith(const char* name, int age, const char* school) {
    Student* self = Student_new();
    if (!self) return NULL;

    /* 设置基类成员 */
    strncpy(self->base_.name_, name, sizeof(self->base_.name_) - 1);
    self->base_.name_[sizeof(self->base_.name_) - 1] = '\0';
    self->base_.age_ = age;

    /* 设置子类成员 */
    strncpy(self->school_, school, sizeof(self->school_) - 1);
    self->school_[sizeof(self->school_) - 1] = '\0';
    return self;
}

void Student_print_impl(void* self) {
    Student* s = (Student*)self;
    printf("[Student] 姓名：%s，年龄：%d，学校：%s\n",
           s->base_.name_, s->base_.age_, s->school_);
}