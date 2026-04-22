/**
 * test4.c
 * 将数据成员隐藏到不透明结构体 PersonPrivate 中，对外仅暴露 void* 指针。
 * 配合全局 person_this 实现无参成员函数，进一步模拟 C++ 的 private 封装。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 私有数据结构体（定义在 .c 文件中，此处直接放在同一文件演示）
 * 外部无法直接访问其成员，必须通过公有接口操作。
 */
typedef struct PersonPrivate {
    int age_;           /**< 年龄 */
    char name_[50];     /**< 姓名 */
} PersonPrivate;

typedef struct Person Person;

/* 公有接口结构体 */
struct Person {
    void* private_;     /**< 指向私有数据的指针（封装） */

    /* 函数指针成员（均为无参，依赖全局 person_this） */
    void (*print_)(void);
    void (*sayHello_)(void);
    void (*destroy_)(void);
    void (*setAge_)(int age);
    int  (*getAge_)(void);
    const char* (*getName_)(void);
    void (*setName_)(const char* name);
};

/* 全局 this 指针 */
Person* person_this = NULL;

/* 宏：设置当前对象 */
#define PERSON_CAST(object) (person_this = object)

/* 函数原型 */
void Person_print_impl(void);
void Person_sayHello_impl(void);
void Person_destroy_impl(void);
void Person_setAge_impl(int age);
int  Person_getAge_impl(void);
const char* Person_getName_impl(void);
void Person_setName_impl(const char* name);
Person* Person_new(void);
Person* Person_newWith(int age, const char* name);

/* 私有数据的分配与释放 */
static PersonPrivate* PersonPrivate_new(void) {
    PersonPrivate* priv = (PersonPrivate*)malloc(sizeof(PersonPrivate));
    if (priv != NULL) {
        priv->age_ = 0;
        priv->name_[0] = '\0';
    }
    return priv;
}

static void PersonPrivate_delete(PersonPrivate* priv) {
    free(priv);
}

/**
 * @brief 堆上创建 Person 对象（无参）
 */
Person* Person_new(void) {
    Person* self = (Person*)malloc(sizeof(Person));
    if (self == NULL) return NULL;

    self->private_ = PersonPrivate_new();
    if (self->private_ == NULL) {
        free(self);
        return NULL;
    }

    /* 绑定函数指针 */
    self->print_   = Person_print_impl;
    self->sayHello_= Person_sayHello_impl;
    self->destroy_ = Person_destroy_impl;
    self->setAge_  = Person_setAge_impl;
    self->getAge_  = Person_getAge_impl;
    self->getName_ = Person_getName_impl;
    self->setName_ = Person_setName_impl;

    person_this = self;
    return self;
}

Person* Person_newWith(int age, const char* name) {
    Person* self = Person_new();
    if (self == NULL) return NULL;

    PersonPrivate* priv = (PersonPrivate*)self->private_;
    priv->age_ = age;
    strncpy(priv->name_, name, sizeof(priv->name_) - 1);
    priv->name_[sizeof(priv->name_) - 1] = '\0';
    return self;
}

/* ---------- 成员函数实现 ---------- */
void Person_print_impl(void) {
    if (person_this == NULL) return;
    PersonPrivate* priv = (PersonPrivate*)person_this->private_;
    if (priv != NULL) {
        printf("年龄：%d，姓名：%s\n", priv->age_, priv->name_);
    }
}

void Person_sayHello_impl(void) {
    if (person_this == NULL) return;
    PersonPrivate* priv = (PersonPrivate*)person_this->private_;
    if (priv != NULL) {
        printf("%s说：你好！\n", priv->name_);
    }
}

void Person_destroy_impl(void) {
    if (person_this == NULL) return;
    if (person_this->private_ != NULL) {
        PersonPrivate_delete((PersonPrivate*)person_this->private_);
        person_this->private_ = NULL;
    }
    free(person_this);
}

void Person_setAge_impl(int age) {
    if (person_this == NULL) return;
    PersonPrivate* priv = (PersonPrivate*)person_this->private_;
    if (priv != NULL) priv->age_ = age;
}

int Person_getAge_impl(void) {
    if (person_this == NULL) return -1;
    PersonPrivate* priv = (PersonPrivate*)person_this->private_;
    return priv ? priv->age_ : -1;
}

const char* Person_getName_impl(void) {
    if (person_this == NULL) return NULL;
    PersonPrivate* priv = (PersonPrivate*)person_this->private_;
    return priv ? priv->name_ : NULL;
}

void Person_setName_impl(const char* name) {
    if (person_this == NULL || name == NULL) return;
    PersonPrivate* priv = (PersonPrivate*)person_this->private_;
    if (priv != NULL) {
        strncpy(priv->name_, name, sizeof(priv->name_) - 1);
        priv->name_[sizeof(priv->name_) - 1] = '\0';
    }
}

int main(void) {
    /* ---------- 栈上对象 ---------- */
    Person p1;
    person_this = &p1;

    p1.private_ = PersonPrivate_new();
    if (p1.private_ == NULL) return 1;

    /* 手动绑定函数指针 */
    p1.print_   = Person_print_impl;
    p1.sayHello_= Person_sayHello_impl;
    p1.destroy_ = Person_destroy_impl;
    p1.setAge_  = Person_setAge_impl;
    p1.getAge_  = Person_getAge_impl;
    p1.getName_ = Person_getName_impl;
    p1.setName_ = Person_setName_impl;

    p1.setName_("张三");
    p1.setAge_(18);
    p1.print_();

    /* 释放私有数据（栈对象自身内存不释放） */
    PersonPrivate_delete((PersonPrivate*)p1.private_);
    p1.private_ = NULL;

    /* ---------- 堆上对象 ---------- */
    Person* p2 = Person_newWith(20, "李四");
    if (p2 != NULL) {
        PERSON_CAST(p2)->print_();
        PERSON_CAST(p2)->destroy_();   /* destroy_ 会释放私有数据和自身 */
    }

    return 0;
}