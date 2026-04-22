# Makefile for test5 (Person class with private data encapsulation)

# 编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -Wextra -std=c99 -g

# 目标可执行文件名
TARGET = test5

# 源文件
SRCS = test5.c person.c

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

# 编译 .c 为 .o
%.o: %.c person.h
	$(CC) $(CFLAGS) -c $< -o $@

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 清理编译产物
clean:
	rm -f $(OBJS) $(TARGET)

# 声明伪目标
.PHONY: all run clean