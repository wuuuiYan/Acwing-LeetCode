//日期：20230617
//内容：栈的应用_十进制数转二进制数

#include <stdio.h>

int stack[512]; //用数组模拟栈
int top = 0; //栈顶指针，始终指向为空的位置

void push(char c);
char pop();
int is_empty();

int main()
{
    int num;
    printf("Please enter an integer in decimal: ");
    scanf("%d", &num);

    while (num)
    {
        push(num % 2);
        num /= 2;
    }
    while (!is_empty())
        printf("%d", pop());

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