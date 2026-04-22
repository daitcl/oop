/**
 * person.c
 * Person 类的实现。
 * 私有数据结构体定义在此文件内，对外不可见。
 * 所有成员函数实现均以 static 限定，仅通过公有接口暴露。
 */

#include "person.h"

/* ==================== 私有数据结构体完整定义 ==================== */
struct PersonPrivate {
    int age_;           /**< 年龄 */
    char name_[50];     /**< 姓名 */
};

/* ==================== 静态成员函数（仅文件内可见） ==================== */

static void Person_print_impl(Person* self) {
    if (self == NULL || self->private_ == NULL) return;
    PersonPrivate* priv = self->private_;
    printf("年龄：%d，姓名：%s\n", priv->age_, priv->name_);
}

static void Person_sayHello_impl(Person* self) {
    if (self == NULL || self->private_ == NULL) return;
    PersonPrivate* priv = self->private_;
    printf("%s说：你好！\n", priv->name_);
}

static void Person_destroy_impl(Person* self) {
    if (self == NULL) return;
    if (self->private_ != NULL) {
        free(self->private_);
        self->private_ = NULL;
    }
    free(self);
}

static void Person_setAge_impl(Person* self, int age) {
    if (self == NULL || self->private_ == NULL) return;
    self->private_->age_ = age;
}

static int Person_getAge_impl(Person* self) {
    if (self == NULL || self->private_ == NULL) return -1;
    return self->private_->age_;
}

static const char* Person_getName_impl(Person* self) {
    if (self == NULL || self->private_ == NULL) return NULL;
    return self->private_->name_;
}

static void Person_setName_impl(Person* self, const char* name) {
    if (self == NULL || self->private_ == NULL || name == NULL) return;
    strncpy(self->private_->name_, name, sizeof(self->private_->name_) - 1);
    self->private_->name_[sizeof(self->private_->name_) - 1] = '\0';
}

/* ==================== 私有数据分配与释放 ==================== */
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

/* ==================== 构造函数（堆对象） ==================== */

Person* Person_new(void) {
    Person* self = (Person*)malloc(sizeof(Person));
    if (self == NULL) return NULL;

    self->private_ = PersonPrivate_new();
    if (self->private_ == NULL) {
        free(self);
        return NULL;
    }

    /* 绑定函数指针 */
    self->print    = Person_print_impl;
    self->sayHello = Person_sayHello_impl;
    self->destroy  = Person_destroy_impl;
    self->setAge   = Person_setAge_impl;
    self->getAge   = Person_getAge_impl;
    self->getName  = Person_getName_impl;
    self->setName  = Person_setName_impl;

    return self;
}

Person* Person_newWith(int age, const char* name) {
    Person* self = Person_new();
    if (self == NULL) return NULL;

    self->private_->age_ = age;
    strncpy(self->private_->name_, name, sizeof(self->private_->name_) - 1);
    self->private_->name_[sizeof(self->private_->name_) - 1] = '\0';
    return self;
}

/* ==================== 栈对象初始化与清理 ==================== */

void Person_init(Person* self) {
    if (self == NULL) return;

    self->private_ = PersonPrivate_new();
    if (self->private_ == NULL) {
        fprintf(stderr, "栈对象私有内存分配失败\n");
        return;
    }

    /* 绑定函数指针（与堆对象一致） */
    self->print    = Person_print_impl;
    self->sayHello = Person_sayHello_impl;
    self->destroy  = Person_destroy_impl;   /* 栈对象不应调用 destroy */
    self->setAge   = Person_setAge_impl;
    self->getAge   = Person_getAge_impl;
    self->getName  = Person_getName_impl;
    self->setName  = Person_setName_impl;
}

void Person_cleanup(Person* self) {
    if (self == NULL) return;
    if (self->private_ != NULL) {
        PersonPrivate_delete(self->private_);
        self->private_ = NULL;
    }
    /* 注意：不释放 self 本身，因为它在栈上 */
}