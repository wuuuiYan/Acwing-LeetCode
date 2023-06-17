//日期：20230617
//内容：栈的应用_逆波兰表达式求值
/*
1.逆波兰表示法：又称为后缀表示法，是一种将操作数写在前面、运算符写在后面的表达式表示法
  例：表达式 "(1+2)*(3-4)" 用逆波兰表示法表示为 "12+34-*"，优点是不需要用圆括号限定计算优先级
2.计算过程：(1+2)*(3-4) -> 12+34-*  -> 334-*  -> 3-1*，可以使计算机严格从左到右计算结果
  遇到运算符时弹出栈顶的两个操作数，计算完成之后再把这一步的计算结果压入栈中继续读取逆波兰表达式
3.本程序只考虑10以内数字的加减乘法运算，对于其他复杂情况暂不考虑
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
    int n1, n2;
    int i, n;

    printf("Please enter a reverse polish expression: ");
    gets(str);
    n = strlen(str);

    for (int i = 0; i < n; i ++)
    {
        if (str[i] >= '0' && str[i] <= '9')
            push(str[i] - '0'); //以字符串的形式读取表达式，但是栈中存放的是整数
        else
        {
            n2 = pop(); //注意弹出的顺序，一定是减数在栈顶，被减数还在栈顶的下方
            n1 = pop();
            switch (str[i])
            {
                case '+':
                    push(n1 + n2);
                    break;
                case '-':
                    push(n1 - n2);
                    break;
                case '*':
                    push(n1 * n2);
                    break;
                default:
                    break;
            }

        }
    }
    printf("result = %d\n", pop());

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