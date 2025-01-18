#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define MAXCHARS 256

#define INSERTED 0
#define NOTINSERTED 1

#define MODE_INSR 0
#define MODE_SRCH 1

/*
** Compiling:
**      gcc -g -DIEC ternary-search-tree.c utils.c   // if print_tabs is needed
**      gcc -g -DIEC ternary-search-tree.c           // if print_tabs is not needed
*/

typedef struct tst_node {
        char c;
        int eos;
        struct tst_node *lo, *mid, *hi;
}tstnode;

tstnode *ptr_array[100]; //used by print_tst
int ptr_arr_ptr = 0;

tstnode *newnode(char c)
{
    tstnode *temp = (tstnode *)malloc(sizeof(tstnode));
    temp->lo = temp->hi = temp->mid = NULL;
    temp->eos = 0;
    temp->c = c;
    ptr_array[ptr_arr_ptr] = temp;
    ptr_arr_ptr++;

    return temp;
}

int gip(tstnode *addr)
{
    if (NULL == addr)
        return -1;

    for (int count=0; count<100; count++)
    {
        if (ptr_array[count] == addr){
            return count;
        }
    }
}

void print_tst(tstnode *root, int level)
{
    tstnode *temp = root;
    if (level == 0)
        printf("\n-------\n");

    printf("depth: %d, addr: %.3d(%c) ", level, gip(root), root->c);
    if (NULL != root->lo)
        printf("lo: %.3d(%c) ",gip(root->lo), root->lo->c);
    else
        printf("           ");
    if (NULL != root->mid)
        printf("md: %.3d(%c) ",gip(root->mid), root->mid->c);
    else
        printf("           ");
    if (NULL != root->hi)
        printf("hi: %.3d(%c) ",gip(root->hi), root->hi->c);
    else
        printf("           ");
    printf(" eos: %d", root->eos);
    printf("\n");

    if (root->lo)
        print_tst(root->lo, level + 1);
    if (root->mid)
        print_tst(root->mid, level + 1);
    if (root->hi)
        print_tst(root->hi, level + 1);
}

void insert(tstnode **root, char *str)
{
    // Base case: Tree is empty
    if (NULL == *root)
        *root = newnode(*str);

    // If current char is smaller than root's char,
    // then insert this string in left subtree of root
    // NOTE: THE STRING REMAINS THE SAME!!
    if ((*str) < (*root)->c)
        insert(&((*root)->lo), str);
    // If current char is greater than root's char,
    // then insert this string in right subtree of root
    // NOTE: THE STRING REMAINS THE SAME!!
    else if ((*str) > (*root)->c)
        insert(&((*root)->hi), str);
    // If the current character is same as root's character
    // NOTE: THE STRING IS INCREMENTED BY 1, SINCE THIS NODE'S CHAR MATCHES
    //       WE NEED TO CHECK IF NEXT CHAR ONWARDS NEEDS TO BE INSERTED.
    else
    {
        printf("Im here\n");
        if (*(str+1))
            insert(&(*root)->mid, str+1);
        // last character of the string
        else
            (*root)->eos = 1;
    }
}

int search(tstnode *root, char *str)
{
    if (!root)
        return 0;

    // First character of the search string is 'less' than root's data
    // => The string we're searching for could be in this node's lo subtree.
    // NOTE: The search string is passed as is
    if (*str < root->c)
        return search(root->lo, str);
    // First character of the search string is 'greater' than root's data
    // => The string we're searching for could be in this node's hi subtree.
    // NOTE: The search string is passed as is
    else if (*str > root->c)
        return search(root->hi, str);
    else
    {
        // Current node's value matches the current character in the string
        // and next char is null termination. Hoorray! We wouldn't have reached
        // the condition of the last char in the string matching (by following eq) pointers
        // unless each and every char prior to this matched this TST node's parents.
        // Where is the first parent? We don't know that.
        if (*(str+1) == '\0')
            return root->eos;

        // NOTE: Since the root's data and current char in string match
        // This could be the nth char in the string so follow eq/mid pointer and increment string by 1.
        return search(root->mid, str+1);
    }
}

void traverse(tstnode *root, char *buffer, int depth)
{
    if (root)
    {
        // traverse left subtree
        traverse(root->lo, buffer, depth);

        // store the character of this node
        buffer[depth] = root->c;
        if (root->eos)
        {
            buffer[depth+1] = '\0';
            printf("%s\n", buffer);
        }
        // traverse the middle subtree
        traverse(root->mid, buffer, depth+1);
        // traverse the right subtree
        traverse(root->hi, buffer, depth);
    }
}


int main()
{
    tstnode *root = NULL;
    char string[MAXCHARS];

    while (1) {
        printf ("Enter string (\"done\" to exit): ");
        scanf ("%s", string);
        if (strcmp(string, "done") != 0) {
            printf("inserting..\n");
            insert(&root, string);
            print_tst(root, 0);
        } else {
            break;
        }
    }

    strcpy(string, "ndone");

    while(1) {
        printf ("Enter string to search (\"done\" to exit): ");
        scanf ("%s", string);
        if (strcmp(string, "done") != 0)
            printf("String %s was %s\n", string, (search(root, string) == 0) ? "not found" : "found");
        else
            break;
    }
}
