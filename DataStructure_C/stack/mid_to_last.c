//日期：20230617
//内容：栈的应用_中缀表达式转后缀表达式
/*
1.从左到右处理整个表达式
2.当遇到左括号时，忽略它；当遇到操作数时，直接输出；
  当遇到运算符时，将运算符入栈，寻找下一个操作数；当遇到右括号时，说明某一次操作数已全部输出将栈顶的运算符出栈输出
3.程序只考虑10以内数字的加减乘法运算，对于其他复杂情况暂不考虑
*/

#include <stdio.h>
#include <string.h>

char stack[512]; //用数组模拟栈
int top = 0; //栈顶指针，始终指向为空的位置

void push(char c);
char pop();
int is_empty();

int main()
{
    char str[100];
    int n = strlen(str);

    printf("Please enter a calculate expression: ");
    gets(str);
    for (int i = 0; i < n; i ++)    
        printf("%c", str[i]);
    
    for (int i = 0; i < n; i ++)
    {
        if (str[i] == '(')
            continue;
        else if (str[i] >= '0' && str[i] <= '9')
            printf("%c", str[i]);
        else if (str[i] == '+' || str[i] == '-' || str[i] == '*')
            push(str[i]);
        else if (str[i] == ')')
            printf("%c", pop());
    }
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