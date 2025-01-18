#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct stack {
    int top;
    void *ele[50];
};
typedef struct stack mstack;

void *pop(mstack *ms)
{
    if (ms->top == 0)
        return NULL;

    ms->top--;
    void *ele = ms->ele[ms->top];

    return ele;
}

int push(mstack *ms, void *ptr)
{
    if (ms->top == 50)
        return 0;

    ms->ele[ms->top] = ptr;
    ms->top++;
    return 1;
}

struct mtree {
    int value;
    struct mtree *left;
    struct mtree *right;
};
typedef struct mtree tnode;


int arr[] = {1,2,3,4,5,6,7};

tnode *create_tree(int arr[], int start, int end)
{
    if (start > end)
        return NULL;

    int mid = (start + end)/2;
    tnode *root = malloc(sizeof(tnode));
    root->value = -1;
    root->left = root->right = NULL;
    root->value = arr[mid];
    root->left = create_tree(arr, start, mid -1);
    root->right = create_tree(arr, mid + 1, end);
    printf ("root: %d root-left: %d root-right: %d\n",
            (root == NULL) ? -1 : root->value, 
            (root == NULL) ? -1 : (root->left == NULL) ? -1 : root->left->value,
            (root == NULL) ? -1 : (root->right == NULL) ? -1 :
            root->right->value);
    return root;
}

void preorder(tnode *root)
{
    if (root == NULL)
        return;
    printf("%d\n", root->value);

    preorder(root->left);
    preorder(root->right);
}

void inorder(tnode *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d\n",root->value);
    inorder(root->right);
}

void inorder_iter(tnode *root)
{
    tnode *tmp = root;
    mstack *ms = malloc(sizeof(mstack));
    ms->top = 0;
    int do_loop = 1;

    while (do_loop)
    {
        /* left processing */
        if (tmp != NULL){
            push(ms, tmp);
            tmp = tmp->left;
            continue;
        }
        
        tmp = (tnode *)pop(ms);
        if (tmp == NULL){
            do_loop = 0;
        } else {
            printf("%d \n", tmp->value);
            tmp = tmp->right;
        }
        sleep(1);
    }
}

void preorder_iter(tnode *root)
{
    tnode *tmp = root;
    mstack *ms = malloc(sizeof(mstack));
    ms->top = 0;
    int do_loop = 1;

    while (do_loop)
    {
        if (tmp != NULL){
            push(ms, tmp);
            printf("%d \n", tmp->value);
            tmp = tmp->left;
            continue;
        }
            
        tmp = (tnode *)pop(ms);
        if (tmp == NULL){
            do_loop = 0;
        } else {
            tmp = tmp->right;
        }
        sleep(1);
    }
}

void postorder_iter(tnode *root)
{
    tnode *tmp = root;
    tnode *tmp2 = NULL;
    mstack *ms = malloc(sizeof(mstack));
    ms->top = 0;
    int do_loop = 1;

    while (do_loop)
    {
        if (!(tmp->left == NULL && tmp->right == NULL))
        {
            push(ms, tmp);
            tmp = tmp -> left;
            continue;
        }
        printf("%d\n", tmp->value);

        tmp2 = (tnode *)pop(ms);

        if (tmp2 == NULL)
            do_loop = 0;

        if (tmp == tmp2 -> left) {
            push(ms, tmp2);
            tmp = tmp2 -> right;
            continue;
        }

        if (tmp == tmp2 -> right) {
            printf("%d\n", tmp2->value);
            tmp2 = (tnode *)pop(ms);
            if (tmp2 == NULL)
                do_loop = 0;
            tmp = tmp2->right;
            push(ms, tmp2);
       }
            
        sleep(1);
    }
}

void postorder(tnode *root)
{
    if (NULL == root)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d\n",root->value);
}

int max(int x, int y)
{
    return ((x > y) ? x : y);
}

int height(tnode *root)
{
    if (NULL == root)
        return (0);

    int lh = height(root->left);
    int rh = height(root->right);

    return(1 + max(lh, rh));
}

int diameter(tnode *root)
{
    if (NULL == root)
        return (0);
    
    int lh = height(root->left);
    int rh = height(root->right);

    int dl = diameter(root->left);
    int dr = diameter(root->right);

    return (max(1 + lh + rh, max(dl, dr)));
}

int lastvalue = -1;

int istreeBSTG(tnode *root)
{
    if (root == NULL)
        return 1;


    if (!istreeBSTG(root->left))
        return 0;

    printf("istreeBSTG visiting %d - lastvalue %d\n", root->value, lastvalue);
    if (root->value < lastvalue)
        return 0;
    else
        lastvalue = root->value;

    return (istreeBSTG(root->right));
}

int istreeBST(tnode *root, int arg)
{
    if (root == NULL)
        return 1;

    printf("istreeBST called for %d arg %d\n", root->value, arg);

    if (!istreeBST(root->left, arg))
        return 0;

    printf("istreeBSTG visiting %d - arg %d\n", root->value, arg);
    if (root->value < arg)
        return 0;
    else
        arg = root->value;
    printf("istreeBSTG visited %d - arg %d\n", root->value, arg);

    return (istreeBST(root->right, arg));
}

int svalue=4;
int inorder_successor(tnode *root, int rfound)
{
    int return_val=0;
    int lfound=0;

    if (root == NULL) {
        return 0;
    }

    lfound = inorder_successor(root->left, rfound);
    if (lfound || rfound){
        printf("inorder successor for %d is %d\n",svalue, root->value);
        return 0;
    }

    if (root->value == svalue) {
        return_val = 1;
        rfound=1;
    }  

    rfound = inorder_successor(root->right, rfound);

    return return_val;
}

int find_all_ancestors(tnode *root, int node_value)
{
	if (root == NULL)
		return 0;
	
	if ((root->left && root->left->value == node_value) || 
	    (root->right && root->right->value == node_value) ||
		find_all_ancestors(root->left, node_value) || 
		find_all_ancestors(root->right, node_value)) {
		printf ("---%d---\n", root->value);
		return 1;
	}
	return 0;
}


int main()
{
    tnode *root = create_tree(arr, 0, 6);
    printf("--- PRE ---\n");
    preorder(root);
    printf("--- IN ---\n");
    inorder(root);
    printf("--- POST ---\n");
    postorder(root);
#if 0
    printf("Height: %d\n", height(root));
    printf("Diameter: %d\n", diameter(root));
    printf("istreeBST: %d\n", istreeBST(root, -1));
    printf("istreeBSTG: %d\n", istreeBSTG(root));
    //postorder_successor(root, 0);
    postorder_iter(root);
#endif
	if (!find_all_ancestors(root, 3))
		printf("No ancestors found!\n");
}
