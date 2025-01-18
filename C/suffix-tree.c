#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void create_suffixes(char *suffixes[], char *str)
{
    int len = strlen(str);
    int i;
    char *ptr;

    for(i=0; i<=len; i++){
        ptr = str + (len - i);
        suffixes[i] = (char *)malloc((i+2) * sizeof(char)); // one extra for '$'
        strcpy(suffixes[i], ptr);
        suffixes[i][i] = '$';
        suffixes[i][i+1] = '\0';
    }
}

void print_s(char *suffixes[], int len)
{
    int c;
    for(c=0 ; c<len; c++)
        printf("%s ", suffixes[c]);
    printf("\n");
}

void sort_suffixes(char *suffixes[])
{
    int len;
    int i, k;
    for (i=0; i<100; i++) {
        if (suffixes[i] == NULL) {
            len = i;
            break;
        }
    }
#ifdef DEBUG
    print_s(suffixes, len);
#endif

    int cmp;
    char *temp;
    for (i=len-1 ; i>0 ; i--) {
        for (k = 0; k < i; k++) {
            cmp = strcmp(suffixes[k+1], suffixes[k]);
#ifdef DEBUG
            printf("strcmp(%s, %s) == %d\n", suffixes[k], suffixes[k+1], cmp);
#endif
            // choose the most precise condition
            if (cmp < 0) {
#ifdef DEBUG
                printf("Swapping %s %s\n",suffixes[k], suffixes[k+1]);
#endif
                temp = suffixes[k];
                suffixes[k] = suffixes[k+1];
                suffixes[k+1] = temp;
#ifdef DEBUG
                print_s(suffixes, len);
#endif
            }
        }
    }
}

int main()
{
    char input[100];
    char *suffixes[100];    //Array of 100 char pointers

    memset(suffixes, 0, 100*(sizeof(char *)));

    printf("Enter String: ");
    scanf("%s",input);

    create_suffixes(&suffixes[0], input);
    sort_suffixes(&suffixes[0]);

    for(int i = 0; i < 100; i++){
        if (suffixes[i] != NULL) {
            printf("%s\n",suffixes[i]);
        }
    }
}

