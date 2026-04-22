/**
 * test5.c
 * 演示如何使用 Person 类的栈对象和堆对象。
 */

#include "person.h"

int main(void) {
    /* ==================== 方式1：栈上对象 ==================== */
    Person p1;

    /* 调用初始化函数，分配私有数据、绑定函数指针 */
    Person_init(&p1);

    /* 通过函数指针调用成员函数 */
    p1.setName(&p1, "张三");
    p1.setAge(&p1, 18);
    p1.print(&p1);   /* 输出：年龄：18，姓名：张三 */

    /* 清理私有数据（不释放 p1 自身） */
    Person_cleanup(&p1);

    /* ==================== 方式2：堆上对象 ==================== */
    Person* p2 = Person_newWith(20, "李四");
    if (p2 != NULL) {
        p2->print(p2);
        p2->destroy(p2);   /* destroy 会释放私有数据和自身 */
    }

    return 0;
}