// 平衡二叉搜索树：左右子树的高度差不超过1，且其中以每个节点为根节点而二叉树也都是平衡二叉搜索树
// 最小不平衡子树：从插入节点向根节点寻找的最小非平衡二叉搜索树，其根节点称为失衡点

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

struct AVLTree_node
{
    unsigned int elem;
    struct AVLTree_node *ltree;
    struct AVLTree_node *rtree;
};

struct AVLTree_node *create_avltree(unsigned int *arr, unsigned int size);
struct AVLTree_node *insert_avltree(struct AVLTree_node *root, unsigned int elem);
void in_order(struct AVLTree_node *root);
int getAVLTreeHeight(struct AVLTree_node *root);
struct AVLTree_node *LL_rotation(struct AVLTree_node *root);
struct AVLTree_node *RR_rotation(struct AVLTree_node *root);
struct AVLTree_node *LR_rotation(struct AVLTree_node *root);
struct AVLTree_node *RL_rotation(struct AVLTree_node *root);
bool search_avltree(struct AVLTree_node *root, unsigned int n);
struct AVLTree_node *delete_avltree(struct AVLTree_node *root, unsigned int n);
struct AVLTree_node *getMax(struct AVLTree_node *root);
struct AVLTree_node *getMin(struct AVLTree_node *root);

int main()
{
    unsigned int num;
    unsigned int arr[SIZE] = {37, 22, 11, 82, 67, 9, 45, 91, 33, 52};
    
    struct AVLTree_node *mytree = NULL;
    
    mytree = create_avltree(arr, SIZE);
    in_order(mytree);
    printf("\n");

    printf("Please enter a number you want to find in the AVLTree: ");
    scanf("%d", &num);
    if (search_avltree(mytree, num))
    {
        printf("The number %d is in mytree.\n", num);
    }
    else
    {
        printf("The number %d is not in mytree.\n", num);
    }

    printf("Please enter a number you want to insert to the AVLTree: ");
    scanf("%d", &num);
    mytree = insert_avltree(mytree, num);
    in_order(mytree);
    printf("\n");

    // printf("mytree->elem = %d\n", mytree->elem);
    // printf("mytree->ltree->elem = %d\n", mytree->ltree->elem);
    // printf("mytree->rtree->elem = %d\n", mytree->rtree->elem);
    // printf("mytree->ltree->ltree->elem = %d\n", mytree->ltree->ltree->elem);
    // printf("mytree->ltree->rtree->elem = %d\n", mytree->ltree->rtree->elem);
    // printf("mytree->rtree->ltree->elem = %d\n", mytree->rtree->ltree->elem);
    // printf("mytree->rtree->rtree->elem = %d\n", mytree->rtree->rtree->elem);
    // printf("mytree->ltree->ltree->ltree->elem = %d\n", mytree->ltree->ltree->ltree->elem);
    // printf("mytree->rtree->ltree->rtree->elem = %d\n", mytree->rtree->ltree->rtree->elem);
    // printf("mytree->rtree->rtree->ltree->elem = %d\n", mytree->rtree->rtree->ltree->elem);
    // printf("mytree->rtree->rtree->rtree->elem = %d\n", mytree->rtree->rtree->rtree->elem);

    printf("Please enter a number you want to delete from the AVLTree: ");
    scanf("%d", &num);
    mytree = delete_avltree(mytree, num);
    in_order(mytree);
    printf("\n");

    printf("mytree->elem = %d\n", mytree->elem);
    printf("mytree->ltree->elem = %d\n", mytree->ltree->elem);
    // printf("mytree->rtree->elem = %d\n", mytree->rtree->elem);
    printf("mytree->ltree->ltree->elem = %d\n", mytree->ltree->ltree->elem);
    printf("mytree->ltree->rtree->elem = %d\n", mytree->ltree->rtree->elem);

    return 0;
}

struct AVLTree_node *create_avltree(unsigned int *arr, unsigned int size)
{
    struct AVLTree_node *root = NULL;
    unsigned int i = 0;
    for (i = 0; i < size; i++)
    {
        root = insert_avltree(root, arr[i]);
    }
    return root;
};

// 平衡二叉搜索树在插入节点时要检查是否平衡，但只会引发一处不平衡
struct AVLTree_node *insert_avltree(struct AVLTree_node *root, unsigned int elem)
{
    if (root == NULL)
    {
        root = (struct AVLTree_node *)malloc(sizeof(struct AVLTree_node));
        root->elem = elem;
        root->ltree = NULL;
        root->rtree = NULL;
    }
    else
    {
        if (elem < root->elem) //向左子树中添加节点
        {
            root->ltree = insert_avltree(root->ltree, elem);
            if (getAVLTreeHeight(root->ltree) - getAVLTreeHeight(root->rtree) > 1)
            {
                // 1) LL型
                // 从失衡点到新插入节点的前两个路径如果是左子树、左子树，成为LL型失衡，使用右旋平衡方法
                if (elem < root->ltree->elem)
                {
                    root = LL_rotation(root);
                }

                // 3) LR型
                // 从失衡点到新插入节点的前两个路径如果是左子树、右子树，成为LR型失衡
                // 先对不平衡子树的左子树部分使用左旋平衡方法，再对整个不平衡子树进行右旋
                if (elem > root->ltree->elem)
                {
                    root = LR_rotation(root);
                }
            }
        }
        else if (elem > root->elem) //向右子树中添加节点
        {
            root->rtree = insert_avltree(root->rtree, elem);
            if (getAVLTreeHeight(root->rtree) - getAVLTreeHeight(root->ltree) > 1)
            {
                // 2) RR型
                // 从失衡点到新插入节点的前两个路径如果是右子树、右子树，成为RR型失衡，使用左旋平衡方法
                if (elem > root->rtree->elem)
                {
                    root = RR_rotation(root);
                }

                // 4) RL型
                // 从失衡点到新插入节点的前两个路径如果是右子树、左子树，成为LR型失衡
                // 先对不平衡子树的右子树部分使用右旋平衡方法，再对整个不平衡子树进行左旋
                if (elem < root->rtree->elem)
                {
                    root = RL_rotation(root);
                }
            }
        }
        else // elem = root->elem
        {
            printf("The element %d is already in the tree.\n", elem);
            exit(0);
        }
    }
    return root;
}

void in_order(struct AVLTree_node *root)
{
    if (root == NULL) return;
    in_order(root->ltree);
    printf("%d ", root->elem);
    in_order(root->rtree);
}

int getAVLTreeHeight(struct AVLTree_node *root)
{
    if (root == NULL) return 0;
    int leftHeight = getAVLTreeHeight(root->ltree);
    int rightHeight = getAVLTreeHeight(root->rtree);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

struct AVLTree_node *LL_rotation(struct AVLTree_node *root)
{
    if (root == NULL) return NULL;

    struct AVLTree_node *temp;
    temp = root->ltree;
    root->ltree = root->ltree->rtree;
    temp->rtree = root;

    return temp;
}

struct AVLTree_node *RR_rotation(struct AVLTree_node *root)
{
    if (root == NULL) return NULL;

    struct AVLTree_node *temp;
    temp = root->rtree;
    root->rtree = root->rtree->ltree;
    temp->ltree = root;

    return temp;
}

struct AVLTree_node *LR_rotation(struct AVLTree_node *root)
{
    root->ltree = RR_rotation(root->ltree);
    root = LL_rotation(root);
    return root;
}

struct AVLTree_node *RL_rotation(struct AVLTree_node *root)
{
    root->rtree = LL_rotation(root->rtree);
    root = RR_rotation(root);
    return root;
}

// 二叉搜索树的查找性能取决于树的高度
bool search_avltree(struct AVLTree_node *root, unsigned int n)
{
    if (root == NULL) return false;
    if (root->elem == n) return true;
    if (root->elem > n) return search_avltree(root->ltree, n);
    if (root->elem < n) return search_avltree(root->rtree, n);
}

// 删除二叉搜索树中的一个节点可以会引发多处不平衡，因此要一直向上检查到根节点为止
// 但因为这个函数本身是递归调用的，所以也不需要用循环检查
struct AVLTree_node *delete_avltree(struct AVLTree_node *root, unsigned int n)
{ 
    // if (root == NULL)
    if (root == NULL || !search_avltree(root, n))
    {
        printf("Not exist %d node.\n", n);
        exit(0);
    }
    if (root->elem == n) 
    {
        if (root->ltree == NULL && root->rtree == NULL)
            return NULL;
        if (root->ltree == NULL) return root->rtree;
        if (root->rtree == NULL) return root->ltree;
        struct AVLTree_node *leftMax = getMax(root->ltree);
        leftMax->ltree = delete_avltree(root->ltree, leftMax->elem);
        if (getAVLTreeHeight(root->rtree) - getAVLTreeHeight(root->ltree) > 1)
        {
            // 引发不平衡：右子树比左子树高，肯定是RR型或RL型中的一种
            struct AVLTree_node *temp = root->rtree;
            if (getAVLTreeHeight(temp->rtree) >= getAVLTreeHeight(temp->ltree)) //RR型
                root = RR_rotation(root);
            else //RL型
                root = RL_rotation(root);
        }
        leftMax->rtree = root->rtree;
        root = leftMax;
        // struct AVLTree_node *rightMin = getMin(root->rtree);
        // rightMin->ltree = root->ltree;
        // rightMin->rtree = delete_avltree(root->rtree, rightMin->elem);
        // root = rightMin;
    }

    if (root->elem > n) 
    {
        root->ltree = delete_avltree(root->ltree, n);
        if (getAVLTreeHeight(root->rtree) - getAVLTreeHeight(root->ltree) > 1)
        {
            // 引发不平衡：右子树比左子树高，肯定是RR型或RL型中的一种
            struct AVLTree_node *temp = root->rtree;
            if (getAVLTreeHeight(temp->rtree) >= getAVLTreeHeight(temp->ltree)) //RR型
                root = RR_rotation(root);
            else //RL型
                root = RL_rotation(root);
        }
    }

    if (root->elem < n) 
    {
        root->rtree = delete_avltree(root->rtree, n);
        if (getAVLTreeHeight(root->ltree) - getAVLTreeHeight(root->rtree) > 1)
        {
            // 引发不平衡：左子树比右子树高，肯定是LL型或LR型中的一种
            struct AVLTree_node *temp = root->ltree;
            if (getAVLTreeHeight(temp->ltree) >= getAVLTreeHeight(temp->rtree)) //LL型
                root = LL_rotation(root);
            else //LR型
                root = LR_rotation(root);
        }
    }
    return root;
}

struct AVLTree_node *getMax(struct AVLTree_node *root)
{
    while (root->rtree != NULL)
        root == root->rtree;
    return root;
}

struct AVLTree_node *getMin(struct AVLTree_node *root)
{
    while (root->ltree != NULL)
        root == root->ltree;
    return root;
}