#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

typedef struct node_s{
    int num; //節點編號
    int time; //該節點需時間多少
    struct node_s *next; //下一個node
    struct path_s *path; //屬於哪條路
}node ;

//需先定義node才可以使用
typedef struct path_s{
    node *first;
    struct path_s *next_path; //下一條路
    int from_time; //路徑一開始已做的時間
}path;

//return last_path 的 指標
path* get_last_path(path *p){
    while(p->next_path != NULL){
        p = p->next_path;
    }
    return p;
}

//計算該path需耗時多少
int cla_path_time(path *p, node *to_n){
    node *now;
    int return_time = p->from_time; //引入原本的耗時

    now = p->first; //now設為該path的第一個node
    while(now!=NULL && now!=to_n){
        return_time += now->time;
        now = now->next;
    }
    //若該path不是最後一個，需要再加上to_node的時間
    if(to_n != NULL){
        return_time = to_n->time;
    }
    return return_time;
}

//取得截至該node的總費時
int get_node_time(node *n){
    if(n->path == NULL){
        return n->time;
    }
    return cla_path_time(n->path, n);//找該path上至node n的時間
}

path* newpath(path *root, node *now, node *from_node){
    path* p;
    if(root->first == NULL){
        p = root;
    }
    else{
        p = malloc(sizeof(path));
        //該path前面還有node 需再加上截至上一個時間
        if(from_node!=NULL){
            p->from_time = get_node_time(from_node);
        }
        //若前面沒有node的話，就代表該node為path第一個
        else{
            p->from_time = 0;
        }
        p->next_path = NULL;
        //將path的最後一個接上目前新的path p
        get_last_path(root)->next_path = p;
    }
    p->first = now;
    now->path = p;
    return p;
}


int main(){
    node *list, *now, *now_1;//nodearray, 目前要處理的node, 該子節點
    path root_path, *p, *tmp_path;
    int N;//有幾個專案=>有幾個node
    char buffer[256], *buffer_pointer;
    scanf("%d", &N);
    //將list和root_path初始化為0
    memset(&root_path, 0, sizeof(root_path));
    list = malloc(N * sizeof(node));
    memset(list, 0, N*sizeof(node));
    //list 中 0 跳過
    //所以num為編號1~n
    for(int i=0;i<N;i++){
        int time, many;
        scanf("%d %d", &time, &many);
        printf("time = %d, many = %d\n", time, many);
        now = &list[i];
        now->num = i;
        now->time = time;
        //now後面沒接東西
        if(now->next==NULL){
            newpath(&root_path, now, NULL);
        }
        for(int j=0;j<many;j++){
            int tem;
            scanf("%d", &tem);
            printf("tem = %d\n", tem);
            now_1 = &list[tem-1];
            if(now->next == NULL){
                //當now->next為空時，但下個又要接東西
                //將now_1歸屬於與now的path同一條
                //再將now的next改成now1
                now->next = now_1;
                now_1->path = now->path;
            }
            else{
                /*父節點有兩條或兩條以上的岔路時
                路徑新增將now_1為新的起點
                該路的時間是根據父節點的時間
                所以參數的父節點放的是now
                */
                newpath(&root_path, now_1, now);
            }
        }
    }

    path *now_2 = &root_path;
    int tt = 0;
    while(now_2!=NULL){
        printf("now_2 num = %d\n", now_2->first->num);
        printf("father_path_time = %d\n", now_2->from_time);
        now_2 = now_2->next_path;
    }

    int longest = 0;
    //將p(class為path*)設為root(path的起點)的地址
    p = &root_path;
    int t;//等等放時間用的
    while(p!=NULL){
        t = cla_path_time(p, NULL);
        if(t>longest) longest = t;
        p = p->next_path;
    }
    printf("%d\n", longest);

    p = root_path.next_path;
    while(p!=NULL){
        tmp_path = p;
        p = p->next_path;
        free(tmp_path);
    }
    free(list);
}

/*
5
6 2 2 3
5 1 4
11 1 5
4 1 5
8 0
*/