#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct node_s {
    int num; //係數
    int exp; //次方
    struct node_s * next;//(次數-1)的node
} node; //一列多項式

node* find_exp(node *first, int exp){
    node *now = first;
    bool f = false;
    if(now->exp = exp) return now;
    while(now!=NULL){
        if(now->exp = exp){
            f = true;
            return now;
        }
        now = now->next;
    }
    if(!f) return NULL;
}

//將新的node加在前面
node* add_node_front(node *first, int num){
    node *new;
    new = (node *)malloc(sizeof(node));
    new->next = first;
    new->num = num;
    new->exp = first->exp + 1;
    return new;
}

void add_node_last(node *first, int num, int exp){
    node *new, *now = first;
    new = (node *)malloc(sizeof(node));
    while(now->next!=NULL){
        now = now->next;
    }
    now->next = new;
    new->next = NULL;
    new->num = num;
    new->exp = exp;
}

void print_all(node *first){
    node *now = first;
    while(now!=NULL){
        if(now->num>=0) printf("+%dx^(%d)", now->num, now->exp);
        else printf("%dx^(%d)", now->num, now->exp);
        now = now->next;
    }
    printf("\n");
}

node* add(node *first_x, node *first_y, node *first_z){
    node *greater, *less;
    if(first_x->exp >= first_y->exp){
        greater = first_x;
        less = first_y;
    }
    else{
        greater = first_y;
        less = first_x;
    }
    //開始新增
    node *new, *now = first_z;
    
    //print_all(first_x);
    //print_all(first_y);
    //print_all(greater);
    for(int i=(greater->exp);i>(less->exp);i--){
        now->exp = i;
        now->num = greater->num;
        //printf("greater->num = %d\n", greater->num);
        greater = greater->next;
        new = (node *)malloc(sizeof(node));
        now->next = new;
        if(now->exp != less->exp) now = new;
    }
    //printf("now->exp = %d\n", now->exp);
    //print_all(first_z);

    for(int i=less->exp;i>=0;i--){
        now->exp = i;
        now->num = greater->num + less->num;
        greater = greater->next;
        less = less->next;
        if(now->exp != 0){
            new = (node *)malloc(sizeof(node));
            now->next = new;
            now = new;
        }
    }
    now->next = NULL;
    return first_z;
}

node* minus(node *first_x, node *first_y, node *first_z){
    node *greater, *less;
    bool x_is_greater = true;

    if(first_x->exp >= first_y->exp){
        greater = first_x;
        less = first_y;
    }
    else{
        greater = first_y;
        less = first_x;
        x_is_greater = false;
    }
    //printf("test\n");
    //開始新增
    node *new, *now = first_z;
    
    //print_all(first_x);
    //print_all(first_y);
    //print_all(greater);
    for(int i=(greater->exp);i>(less->exp);i--){
        now->exp = i;
        now->num = greater->num;
        if(!x_is_greater) (now->num)*=-1;
        //printf("greater->num = %d\n", greater->num);
        greater = greater->next;
        new = (node *)malloc(sizeof(node));
        now->next = new;
        if(now->exp != less->exp) now = new;
    }
    //printf("now->exp = %d\n", now->exp);
    //print_all(first_z);

    for(int i=less->exp;i>=0;i--){
        now->exp = i;
        now->num = greater->num - less->num;
        if(!x_is_greater) (now->num)*=-1;
        greater = greater->next;
        less = less->next;
        if(now->exp != 0){
            new = (node *)malloc(sizeof(node));
            now->next = new;
            now = new;
        }
    }
    now->next = NULL;
    return first_z;
}

void print_answer(node *first){
    node *now = first;
    while(now->next != NULL){
        printf("%d %d ", now->num, now->exp);
        //printf("\n now->next->num = %d", now->next->num);
        now = now->next;
    }
    //printf("test22\n");
    printf("%d %d\n", now->num, now->exp);
    //printf("test2\n");
}

void Free(node *first){
    while(first!=NULL){
        node *tem = first;
        tem = tem->next;
        free(first);
        first = tem;
    }
}

int main(){
    int n1, n2, tem;
    node *first_x, *first_y, *first_z, first, *now;
    first_x = (node *)malloc(sizeof(node));
    first_x->next = NULL;
    first_y = (node *)malloc(sizeof(node));
    first_y->next = NULL;
    first_z = (node *)malloc(sizeof(node));
    first_z->next = NULL;
    
    //處理第一組多項式
    scanf("%d", &n1);
    now = first_x;
    for(int i=0;i<n1;i++){
        scanf("%d", &tem);
        now->num = tem;
        now->exp = n1-i-1;
        if(i!=n1-1){
            node *next;
            next = (node *)malloc(sizeof(node));
            now->next = next;
            now = next;
            now->next = NULL;
        }
    }
    //print_all(first_x);


    //處理第二組多項式
    scanf("%d", &n2);
    now = first_y;
    for(int i=0;i<n2;i++){
        scanf("%d", &tem);
        now->num = tem;
        now->exp = n2-1-i;
        if(i!=n2-1){
            node *next;
            next = (node *)malloc(sizeof(node));
            now->next = next;
            now = next;
            now->next = NULL;
        }
    }
    //print_all(first_y);

    //相加的部分
    first_z = add(first_x, first_y, first_z);
    //print_all(first_z);
    print_answer(first_z);
    Free(first_z);
    first_z = (node *)malloc(sizeof(node));
    first_z->next = NULL;

    
    first_z = minus(first_x, first_y, first_z);
    print_answer(first_z);
    Free(first_z);
    first_z = (node *)malloc(sizeof(node));
    first_z->next = NULL;


    return 0;
}