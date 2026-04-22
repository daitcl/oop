# Makefile for test8 (Person/Student inheritance with vtable and polymorphism)

# 编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -Wextra -std=c99 -g

# 目标可执行文件名
TARGET = program

# 源文件
SRCS = main.c person.c student.c

# 目标文件
OBJS = $(SRCS:.c=.o)

# 默认目标：编译并运行
all: $(TARGET)
	@echo "=== Running $(TARGET) ==="
	./$(TARGET)
	@echo "=== Done ==="

# 链接生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 编译规则（自动依赖头文件）
%.o: %.c person.h student.h
	$(CC) $(CFLAGS) -c $< -o $@

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 清理编译产物
clean:
	rm -f $(OBJS) $(TARGET)

# 声明伪目标
.PHONY: all run clean