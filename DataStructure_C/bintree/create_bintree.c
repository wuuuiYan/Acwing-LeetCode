/*
1.树是非线性结构(一对多)，之前讲到的数组、链表、栈、队列均是线性结构
2.链表为链式存储，数组、栈、队列为顺序存储，链表、栈、队列均可以使用数组模拟
3.本阶段的课程重点关注树尤其是二叉树，关于B树、B+树、红黑树见高级数据结构部分
4.二叉树有且仅有一个根结点，且任一结点均拥有不超过两个子结点
5.二叉树除根结点之外可分为两个互不交叉的子树，子树也是二叉树(递归的思想)
*/

#include <stdio.h>
#include <stdlib.h>

struct BinTree_node
{
    unsigned char elem;
    struct BinTree_node *ltree, *rtree;
};

struct BinTree_node *create_bintree();

int main()
{
    struct BinTree_node *mytree;
    mytree = create_bintree();

    return 0;
}

struct BinTree_node *create_bintree()
{
    unsigned char flag;
    struct BinTree_node *tree;
    tree = (struct BinTree_node *)malloc(sizeof(struct BinTree_node));

    printf("Please input the node element: ");
    while((tree->elem = getchar()) == '\n');

    printf("Do you want to create l_tree for %c, (Y/N): ", tree->elem);
    while((flag = getchar()) == '\n');
    if (flag == 'Y')
        tree->ltree = create_bintree();
    else
        tree->ltree = NULL;

    printf("Do you want to create r_tree for %c, (Y/N): ", tree->elem);
    while((flag = getchar()) == '\n');
    if (flag == 'Y')
        tree->rtree = create_bintree();
    else
        tree->rtree = NULL;

    return tree;
}