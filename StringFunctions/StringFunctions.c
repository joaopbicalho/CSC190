#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *my_strcat(char *dest, char *src){
    int len_src = strlen(src);
    int start_src = strlen(dest);
    int len_final = strlen(dest) + strlen(src);
    for (int i = 0; i < len_final; i++){
        dest[start_src + i] = src[i];
    }
    return dest;
}

int my_strcmp_rec(char *str1, char *str2){
    int i = 0;
    if (*(str1 + i) == '\0' && str2[i] == '\0'){
         return 0;
    }
    else if (str1[i] != str2[i]){
        return (str1[i] - str2[i]);
    }
    else if (str1[i] == str2[i])
    {
        my_strcmp_rec(str1+1, str2 + 1);
    }
}

int my_atoi(char *str){
    int i = 0;
    int sign = 1;
    int num = 0;

    if(str[0] == '-'){
        sign = -1;
        ++i;
    }
    for(; str[i] != '\0' && isdigit(str[i]); i++){
        num = num*10 + (str[i] - '0');
    }
    return sign*num;
}

struct node{
    int data;
    struct node *next;
};

void append(struct node *head, int value, int closed){
    struct node *cur = head;
    struct node *loop = NULL;
    if(closed == 1){
        loop = head->next;
    }
    while(cur->next != NULL){
        cur = cur->next;
    }
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->data = value;
    node->next = loop;
    cur->next = node;
}
int cycle_fnct(struct node *head){
    struct node *tort = head;
    struct node *hare = head;
    int x = 0;
    while(x == 0 && hare->next != NULL && hare->next->next != NULL){
        tort = tort->next;
        hare = hare->next->next;
        if(tort == hare){
            x = 1;
        }
    }
    if(tort == hare){
        return 1;
    }
    else{
        return 0;
    }
}

int main(void){
    char a[10] = "Hi";
    char b[10] = "Hee";
    my_strcat(a , b);
    printf(a);

    char num[] = "-1234567";
    int x = my_atoi(num);
    printf("\n%d", x);   

    struct node *node0 = (struct node *)malloc(sizeof(struct node));
    node0->data = 5;
    node0->next = NULL;
    append(node0, 8, 0);
    append(node0, 12, 0);
    append(node0, 7, 0);
    append(node0, 4, 0);
    append(node0, -2, 1);
    int f = cycle_fnct(node0);
    printf("%d\n", f);

    return 0;
}
