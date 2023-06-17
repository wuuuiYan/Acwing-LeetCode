//日期：20230617
//内容：栈的基本原理及实现
/*
1.把栈想象成一个弹夹，栈中存放的内容就是弹夹中的子弹，特点是先入后出
2.栈的最常用也是最基础操作是：入栈、出栈、判断栈是否为空
*/

#include <stdio.h>

char stack[512]; //用数组模拟栈
int top = 0; //栈顶指针，始终指向为空的位置

void push(char c);
char pop();
int is_empty();

int main()
{
    push('a');
    push('b');
    push('c');

    while (!is_empty())
        putchar(pop());
    printf("\n");

    return 0;
}

void push(char c)
{
    stack[top ++] = c;
}

char pop()
{
    return stack[-- top];
}

int is_empty()
{
    if (top == 0)
        return 1;
    else
        return 0;
    // return top == 0;
}