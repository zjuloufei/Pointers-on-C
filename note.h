//1.避免头文件重复包含，重复包含增加编译工作量；2.若在头文件定义全局变量，则会引起重复定义。
#ifndef POINTERS_ON_C_NOTE_H
#define POINTERS_ON_C_NOTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>


#if 1 //1.1
#define MAX_COLS 20  //预处理指令
#define MAX_INPUT 1000

int read_column_numbers(int columns[], int max);  //函数原型：参数的名字并非必需
void rearrange(char *output, char const *input, int n_columns, int const columns[]);
#endif  //1.1


#if 0  //17.2 实现堆栈
#define STACK_TYPE int

void push(STACK_TYPE value);
void pop(void);
STACK_TYPE top(void);

void creat_stack(size_t size);
void destroy_stack(void);

int is_empty(void);
int is_full(void);
#endif  //17.2

#endif //POINTERS_ON_C_NOTE_H
