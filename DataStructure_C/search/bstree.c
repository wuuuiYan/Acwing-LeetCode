#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct BSTree_node
{
    unsigned int elem;
    struct BSTree_node *ltree;
    struct BSTree_node *rtree;
};

struct BSTree_node *create_bstree(unsigned int *arr, unsigned int size);
struct BSTree_node *insert_bstree(struct BSTree_node *root, unsigned int elem);
void in_order(struct BSTree_node *root);

int main()
{
    unsigned int arr[SIZE] = {37, 22, 11, 82, 67, 9, 45, 91, 33, 52};
    struct BSTree_node *mytree = NULL;
    mytree = create_bstree(arr, SIZE);
    in_order(mytree);
    printf("\n");
    return 0;
}

struct BSTree_node *create_bstree(unsigned int *arr, unsigned int size)
{
    struct BSTree_node *root = NULL;
    unsigned int i = 0;
    for (i = 0; i < size; i++)
    {
        root = insert_bstree(root, arr[i]);
    }
    return root;
};

struct BSTree_node *insert_bstree(struct BSTree_node *root, unsigned int elem)
{
    if (root == NULL)
    {
        root = (struct BSTree_node *)malloc(sizeof(struct BSTree_node));
        root->elem = elem;
        root->ltree = NULL;
        root->rtree = NULL;
    }
    else
    {
        if (elem < root->elem)
        {
            root->ltree = insert_bstree(root->ltree, elem);
        }
        else if (elem > root->elem)
        {
            root->rtree = insert_bstree(root->rtree, elem);
        }
        else // elem = root->elem
        {
            printf("The element %d is already in the tree.\n", elem);
            exit(0);
        }
    }
    return root;
}

void in_order(struct BSTree_node *root)
{
    if (root == NULL) return;
    in_order(root->ltree);
    printf("%d ", root->elem);
    in_order(root->rtree);
}
