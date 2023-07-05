#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
bool search_bstree(struct BSTree_node *root, unsigned int n);
struct BSTree_node *delete_bstree(struct BSTree_node *root, unsigned int n);
struct BSTree_node *getMax(struct BSTree_node *root); //获取二叉搜索树的最大节点
struct BSTree_node *getMin(struct BSTree_node *root); //获取二叉搜索树的最小节点

int main()
{
    unsigned int num;
    unsigned int arr[SIZE] = {37, 22, 11, 82, 67, 9, 45, 91, 33, 52};
    
    struct BSTree_node *mytree = NULL;
    
    mytree = create_bstree(arr, SIZE);
    in_order(mytree);
    printf("\n");

    printf("Please enter a number you want to find int the BSTree: ");
    scanf("%d", &num);
    if (search_bstree(mytree, num))
    {
        printf("The number %d is in mytree.\n", num);
    }
    else
    {
        printf("The number %d is not in mytree.\n", num);
    }

    printf("Please enter a number you want to insert to the BSTree: ");
    scanf("%d", &num);
    mytree = insert_bstree(mytree, num);
    in_order(mytree);
    printf("\n");

    printf("Please enter a number you want to delete from the bstree: ");
    scanf("%d", &num);
    // num = 22;
    mytree = delete_bstree(mytree, num);
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

// 二叉搜索树的查找性能取决于树的高度
bool search_bstree(struct BSTree_node *root, unsigned int n)
{
    if (root == NULL) return false;
    if (root->elem == n) return true;
    if (root->elem > n) return search_bstree(root->ltree, n);
    if (root->elem < n) return search_bstree(root->rtree, n);
}

/*
bool search_bstree(struct BSTree_node *root, unsigned int n)
{
    while (root != NULL)
    {
        if (root->elem == n) return true;
        if (root->elem > n) root = root->ltree;
        if (root->elem < n) root = root->rtree;
    }
    return false;
}
*/

/*
struct BSTree_node *delete_bstree(struct BSTree_node *root, unsigned int n)
{
    // if (root == NULL || !search_bstree(root, n))
    if (root == NULL)
    {
        printf("Not exist %d node.\n", n); //FIXME，为什么某些节点删除会提示不存在？
        exit(0);
    }
    if (root->elem == n) 
    {
        // if (root->ltree == NULL && root->rtree == NULL)
        //     return NULL;
        if (root->ltree == NULL) return root->rtree;
        if (root->rtree == NULL) return root->ltree;
        struct BSTree_node *leftMax = getMax(root->ltree);
        root->ltree= delete_bstree(root->ltree, leftMax->elem);
        leftMax->ltree = root->ltree;
        leftMax->rtree = root->rtree;
        root = leftMax;
        // struct BSTree_node *rightMin = getMin(root->rtree);
        // root->rtree = delete_bstree(root->rtree, rightMin->elem);
        // rightMin->ltree = root->ltree;
        // rightMin->rtree = root->rtree;
        // root = rightMin;
    }
    if (root->elem > n) root->ltree = delete_bstree(root->ltree, n);
    if (root->elem < n) root->rtree = delete_bstree(root->rtree, n);
    // else root->rtree = delete_bstree(root->rtree, n);
    return root;
}
*/


struct BSTree_node *delete_bstree(struct BSTree_node *root, unsigned int n)
{
	if(root == NULL)
	{
		printf("Not exist %d node.\n",	n);
		exit(0);
	}

	// 选择后继点的元素作为替换该节点的元素
	if(root->elem == n)
	{
		if(root->rtree == NULL) //当右子树为空时，直接上提左子树
		{
			struct BSTree_node *temp = root;
			root = root->ltree;
			free(temp);
		}
		else // 当右子树不为空时，右子树的最左节点即为该根节点的后继节点
		{
			struct BSTree_node *temp = root->rtree;
			while(temp->ltree)
				temp = temp->ltree;
			root->elem = temp->elem;

			//删除二叉搜索树中重复的节点
			root->rtree = delete_bstree(root->rtree, root->elem);
		}
	}
	else if(root->elem > n)
		root->ltree = delete_bstree(root->ltree, n);
	else //T->elem < elem
		root->rtree = delete_bstree(root->rtree, n);

	return root;
}


struct BSTree_node *getMax(struct BSTree_node *root)
{
    while (root->rtree != NULL)
        root == root->rtree;
    return root;
}

struct BSTree_node *getMin(struct BSTree_node *root)
{
    while (root->ltree != NULL)
        root == root->ltree;
    return root;
}