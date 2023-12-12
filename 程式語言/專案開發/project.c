#include<stdio.h>
#include<stdbool.h>
#include<string.h>

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
    return get_last_path(n->path, n);//找該path上至node n的時間
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
    node *list, now_ptr, now_child_ptr;//nodearray, 目前要處理的node, 該子節點
    path root_path, nowpath_ptr;
    int n;//有幾個專案=>有幾個node
    scanf("%d", &n);
    //將list初始化為0
    list = malloc(n * sizeof(node));
    memset(list, 0, n*sizeof(node));
    //list 中 0 跳過
    //所以num為編號1~n
    for(int i=1;i<=n;i++){
        int time, many;
        scanf("%d %d", &time, &many);
        now_ptr = list[i];
    }
}