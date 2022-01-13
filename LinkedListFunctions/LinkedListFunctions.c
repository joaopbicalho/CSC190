#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct nodf{
    void *p_data; //a pointer to data (allocated with malloc)
    int type; //0 if int, 1 if float, 2 if double
    struct nodf *next;
};

void print_list(struct node *head){
    struct node *cur = head;
    printf("%ld", cur->data);
    while(cur->next != NULL){
        cur = cur->next;
        printf(", %ld", cur->data);
    }
    printf("\n"); 
}

void print_list_rec(struct node *head){
    printf("%ld", head->data);
    if(head->next == NULL){
        printf("\n");
        return;
    }
    printf(", ");
    print_list_rec(head->next);
}

void print_lis(struct nodf *head){
    if(head->type == 0){
        int *x = head->p_data;
        printf("%ld", *x);
    }
    else if(head->type == 1){
        float *x = head->p_data;
        printf("%lf", *x);
    }
    else{
        double *x = head->p_data;
        printf("%lf", *x);
    }

    if(head->next == NULL){
        printf("\n");
        return;
    }
    printf("\n");
    print_lis(head->next);

}

void append_int(struct nodf *head, int *value){
    struct nodf *cur = head;
    while(cur->next != NULL){
        cur = cur->next;
    }
    struct nodf *nodf = (struct nodf *)malloc(sizeof(struct nodf));
    nodf->p_data = value;
    nodf->next = NULL;
    nodf->type = 0;
    cur->next = nodf;
}

void append_float(struct nodf *head, float *value){
    struct nodf *cur = head;
    while(cur->next != NULL){
        cur = cur->next;
    }
    struct nodf *nodf = (struct nodf *)malloc(sizeof(struct nodf));
    nodf->p_data = value;
    nodf->next = NULL;
    nodf->type = 1;
    cur->next = nodf;
}

void append_double(struct nodf *head, double *value){
    struct nodf *cur = head;
    while(cur->next != NULL){
        cur = cur->next;
    }
    struct nodf *nodf = (struct nodf *)malloc(sizeof(struct nodf));
    nodf->p_data = value;
    nodf->next = NULL;
    nodf->type = 2;
    cur->next = nodf;
}


int main(void){
    struct node *node0 = (struct node *)malloc(sizeof(struct node));
    node0->data = 5;

    struct node *node1 = (struct node *)malloc(sizeof(struct node));
    node0->next = node1;
    node1->data = 3;

    struct node *node2 = (struct node *)malloc(sizeof(struct node));
    node1->next = node2;
    node2->data = 8;
    node2->next = NULL;
    print_list(node0);
    print_list_rec(node0);

    int *d = (int *)malloc(sizeof(int));
    *d = 5;
    float *f = (float *)malloc(sizeof(float));
    *f = 4.67;
    double *e = (double *)malloc(sizeof(double));
    *e = 7.8903;

    struct nodf *nodf0 = (struct nodf *)malloc(sizeof(struct nodf));
    nodf0->p_data = d;
    nodf0->type = 0;

    struct nodf *nodf1 = (struct nodf *)malloc(sizeof(struct nodf));
    nodf0->next = nodf1;
    nodf1->p_data = e;
    nodf1->type = 2;

    struct nodf *nodf2 = (struct nodf *)malloc(sizeof(struct nodf));
    nodf1->next = nodf2;
    nodf2->p_data = f;
    nodf2->type = 1;

    nodf2->next = NULL;

    print_lis(nodf0);
    int *g = (int *)malloc(sizeof(int));
    *g = 6;
    append_int(nodf0, g);
    float *h = (float *)malloc(sizeof(float));
    *h = 8.68;
    append_float(nodf0, h);
    double *i = (double *)malloc(sizeof(double));
    *i = 6.7425678;
    append_double(nodf0, i);
    print_lis(nodf0);

    return 0;
}
