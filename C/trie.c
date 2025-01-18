#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHARS 26
#define printstr(s) printf("%s\n", s)
#define printchar(c) printf("%c\n", c)
#define printint(i) printf("%d\n", i)

#define EOS 1
#define NOTEOS 0


typedef struct trie {
    char c;
    int eos;
    struct trie *children[MAXCHARS];    // OK

} trienode;


trienode *newnode(char c, int eos)
{
    trienode *node = (trienode *)malloc(sizeof(trienode));
    node->c = c;
    node->eos = eos;
    memset(node->children, 0, sizeof(node->children));

    return node;
}

void insert (trienode **root, char *s)
{
    /* example: a, aa */
    char temp;
    char *sptr = s;
    trienode *tptr = NULL;

    if (NULL == s) {
        printf("Empty string passed\n");
        return;
    }

    /* init root if null */
    if (NULL == *root)
        *root = newnode(s[0], EOS);

    tptr = *root;

    /* have to be one step ahead in the string */
    sptr++;

    while (*sptr != '\0') {

        char c = sptr[0];

        if (NULL == tptr->children[c - 97]) {
            tptr->children[c - 97] = newnode(c, EOS);
            tptr->eos = NOTEOS;
        }
        tptr = tptr->children[c - 97];
        sptr++;
    }
}

void find (trienode **root, char *s)
{
    int found = 1;
    trienode *p = *root;
    char *sptr = s;

    while (p != NULL && *sptr != '\0')
    {
        if (p->c != *sptr) {
            found = 0;
            break;
        }
        p = p->children[*sptr  - 96];
        sptr++;
    }

    if (*sptr != '\0')
        found = 0;

    printf("String %s : %s\n", s, found == 0 ? "not found" : "found");

}

int main()
{
    trienode *root = NULL;
    char c, input[200];
    int l;

    printf ("Enter string (<200) : ");
    scanf("%s", input);
    insert(&root, input);

    printf ("Enter string (<200) : ");
    scanf("%s", input);
    insert(&root, input);

    printf ("Enter string to find : ");
    scanf("%s", input);
    find(&root, input);
}

