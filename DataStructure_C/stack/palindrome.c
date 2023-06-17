//日期：20230617
//内容：栈的应用_判定回文序列
/*
1.偶数个字符串可直接将整个字符一分为二，奇数个字符以中间字符为分界线划分前后一半
2.将前一半字符依次入栈，然后出栈并与后一半字符进行逐个比较即可，直到栈为空
*/
#include <stdio.h>
#include <string.h>

char stack[512];
int top = 0;

void push(char c);
char pop(void);
int is_empty(void);
int is_palindrome(char *pt);

int main(void)
{
	char str[100];

	printf("Please enter a string: ");
	gets(str);

	if (is_palindrome(str))
		printf("str is a palindrome.\n");
	else
		printf("str is not a palindrome.\n");

	return 0;
}

void push(char c)
{
	stack[top++] = c;
}

char pop(void)
{
	return stack[--top];
}

int is_empty(void)
{
/*
	if(top == 0)
		return 1;
	else
		return 0;
*/
	return top == 0;
}

int is_palindrome(char *pt) //注意形参的数据类型
{
	int len, i;

	len = strlen(pt);

	for (i = 0; i < len/2; i++)
		push(pt[i]);

	if (len % 2 == 1)
		i++;

	while (!is_empty())
	{
		if (pop() == pt[i])
			i++;
		else
			return 0;
	}
	return 1;
}
