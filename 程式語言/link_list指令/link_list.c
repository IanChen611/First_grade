#include<stdio.h>
#include<stdlib.h>
typedef struct node_s{
    int data;
    struct node_s *next;
}node;

void print_all_node(node *first){
    if(first==NULL){
        printf("None\n");
        return ;
    }
    node *now;
    now = first;
    while(now!=NULL){
        printf("%d ", now->data);
        now = now->next;
    }
}

node *last_add_node(node *first, int d){
    node *now;
    node *new;
    new = (node *)malloc(sizeof(node));
    if(first==NULL){
        first = new;
    }
    else{
        now = first; // (*firts).next
        while(now->next!=NULL){
            now = now->next;
        }
        now->next = new;
    }
    new->data = d;
    new->next = NULL;
    return first;
}

node *delete_node_front(node *first){
    node *p = NULL;
    if(first!=NULL){
        p = first;
        first = first->next;
    }
    free(p);
    return first;
}

node *delete_node_last(node *first){
    node *now;
    node *previous = NULL;
    if(first->next==NULL) return NULL;
    now = first;
    while(now->next!=NULL){
        previous = now;
        now = now->next;
    }
    free(now);
    previous->next = NULL;
    return first;
}

node *delete_node_data(node *first, int x){
    node *now = first;
    node *previous = NULL;
    while(now!=NULL){
        if(now->data == x){
            //該node為first
            if(previous==NULL){
                now = first->next;
                free(first);
                first = now;
            }
            //該node不是first
            else{
                node *tem;
                tem = now;
                previous->next = now->next;
                now = now->next;
                free(tem);
            }
        }
        else{
            previous = now;
            now = now->next;
        }
    }
    return first;
}

node *search_node(node *first, int x){
    node *now = first;
    while(now!=NULL){
        if(now->data == x){
            return now; 
        }
        now = now->next;
    }
    return NULL;
}

void pos_add_data(node *want, int y){
    node *new, *previous, *next;
    if(want==NULL) return;
    new = (node *)malloc(sizeof(node));
    previous = want;
    next = previous->next;
    if(next==NULL){
        //該previous最後一個
        //等於在最後面插入y
        last_add_node(previous, y);
    }
    else{
        previous->next = new;
        new->data = y;
        new->next = next;
    }
}

node *reverse_node(node *first){
    node *previous = NULL;
    node *now = first;
    node *dealing = first->next;
    while(dealing!=NULL){
        now->next = previous;
        previous = now;
        now = dealing;
        dealing = dealing->next;
    }
    now->next = previous;
    first = now;
    return first;
}

int main(){
    int n;
    scanf("%d", &n);
    node *first, *current, *previous;
    for(int i=0;i<n;i++){
        int d;
        current = (node *)malloc(sizeof(node));
        scanf("%d", &d);
        current->data = d;//此行意義為 (*current).data = d;
        //printf("current data = %d\n", current->data);
        if(i==0) first = current;//第一個為起點
        else previous->next = current;//把先前的設定成這次的
        current->next = NULL;//把每次當成最後一個，若後面還有，每次for迴圈會更新
        previous = current; //下個迴圈的previous為這次的node
    }
    //printf("first->data = %d\n", first->data);
    //創建node array完成
    int op;
    //printf("start edit\n");
    scanf("%d", &n);
    //printf("n = %d", n);
    //printf("start edit\n");

    for(int i=0;i<n;i++){
        scanf("%d", &op);
        int x, y;
        //op==1 最後加入資料
        if(op==1){
            scanf("%d", &x);
            //printf("op == %d\n", op);
            first = last_add_node(first, x);
        }
        //op==2 刪除最前面的節點
        else if(op==2 && first!=NULL){
            //printf("op == %d\n", op);
            first = delete_node_front(first);
            //printf("test2\n");
        }
        //op==3 刪除最後面的節點
        else if(op==3 && first!=NULL){
            //printf("op == %d\n", op);
            first = delete_node_last(first);
            //printf("Test:");
            //print_all_node(first);
            //printf("\n");
        }
        //op==4 刪除list中，資料為x的node
        else if(op==4){
            scanf("%d", &x);
            //printf("op == %d\n", op);
            first = delete_node_data(first, x);
            //print_all_node(first);
            //printf("\n");
        }
        //op==5 搜尋x值的node，並在此node後加入y
        else if(op==5){
            scanf("%d %d", &x, &y);
            //printf("op == %d\n", op);
            node *want;
            want = search_node(first, x);
            pos_add_data(want, y);
            //print_all_node(first);
            //printf("\n");
        }
        //op==6 反轉
        else if(op==6){
            //printf("op == %d\n", op);
            first = reverse_node(first);
        }
        //op==7交換x、y
        else if(op==7){
            scanf("%d %d", &x, &y);
            //printf("op == %d\n", op);
            node *pos_x, *pos_y;
            pos_x = search_node(first, x);
            pos_y = search_node(first, y);
            if(pos_x!=NULL && pos_y!=NULL){
                pos_x->data = y;
                pos_y->data = x;
            }
        }
        /*
        if(first!=NULL){
            printf("first data = %d\n", first->data);
        }*/
    }
    print_all_node(first);
}