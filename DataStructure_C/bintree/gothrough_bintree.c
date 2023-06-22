#include <stdio.h>
#include <stdlib.h>

struct BinTree_node
{
    unsigned char elem;
    struct BinTree_node *ltree, *rtree;
};

struct BinTree_node *create_bintree();
void pre_order(struct BinTree_node *tree);
void in_order(struct BinTree_node *tree);
void pos_order(struct BinTree_node *tree);

int main()
{
    struct BinTree_node *mytree;
    mytree = create_bintree();

    pre_order(mytree);

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

void pre_order(struct BinTree_node *tree)
{
    if (tree)
    {
        printf("%c", tree->elem);
        pre_order(tree->ltree);
        pre_order(tree->rtree);
    }
}

void in_order(struct BinTree_node *tree)
{
    if (tree)
    {
        in_order(tree->ltree);
        printf("%c", tree->elem);
        in_order(tree->rtree);
    }
}

void pos_order(struct BinTree_node *tree)
{
    if (tree)
    {
        pos_order(tree->ltree);
        pos_order(tree->rtree);
        printf("%c", tree->elem);
    }
}