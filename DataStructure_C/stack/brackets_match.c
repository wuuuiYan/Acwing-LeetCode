//日期：20230617
//内容：栈的应用_括号匹配
/*
1.从左到右处理整个表达式，最终输出匹配的括号在整个表达式中的序号
2.遇到左括号不匹配，遇到右括号匹配与其最近的左括号
3.遇到左括号，入栈；遇到操作数或运算符，忽略它；遇到右括号；出栈
*/

#include <stdio.h>
#include <string.h>

int stack[512]; //用数组模拟栈
int top = 0; //栈顶指针，始终指向为空的位置

void push(char c);
char pop();
int is_empty();

int main()
{
    char str[100];
    
    printf("Please enter a calculate expression: ");
    gets(str);
    int n = strlen(str);

    for (int i = 0; i < n; i ++)
    {
        if (str[i] == '(')
            push(i);
        else if (str[i] == ')')
            printf("%d %d\n", pop(), i);
    }

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