#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define max_p 100

typedef struct path_struct{
    //二維矩陣 紀錄路徑資訊 紀錄誰到誰為距離多少
    int path[max_p][max_p];
    //是否已經加入最短路徑樹了
    int visit[max_p];
    //紀錄最短路徑經過誰
    int parent[max_p];
    //最後一個城市
    int last;
}path_s;

void dijkstra(path_s *ps, int start){
    int distance[max_p];
    int min_dis, next, dist;
    //reset
    for(int i=0;i<=ps->last;i++){
        distance[i] = ps->path[start][i];//將每個城市距離起點的距離設為path表中已知資訊
        ps->visit[i] = 0;//將每個都先設為沒拜訪過
        //相鄰的話
        //跟起點為父節點
        //不相鄰的話
        //還不知道父節點是誰
        if(distance[i]==1) ps->parent[i] = start;
        else ps->parent[i] = 0;
    }
    ps->visit[start] = 1;//已拜訪過start了
    ps->parent[start] = -1;//start本身沒有上一個父節點
    int idx;
    for(int i=0;i<ps->last;i++){
        //找目前不再最短路徑樹上且距離起點最近的點
        min_dis = 1e9;//先將min_dis設為無限大
        idx = -1;
        for(int j=0;j<=ps->last;j++){
            //如果j城市還未尋訪過且distance中的j資料小於最小路徑
            //將最小路徑min_dis設為j與起點的距離
            //idx設為j
            if(ps->visit[j]==0 && distance[j]<min_dis){
                min_dis = distance[j];
                idx = j;
            }
        }
        //目前的min_dis已為最小
        if(idx==-1) break;
        
        //idx尋訪過了
        ps->visit[idx] = 1;
        //從起點開始走到其他點，看看可否更新起點到其他點的最短路徑
        for(int next = 0;next<=ps->last;next++){
            //dist設為(idx到起點的距離)+(path表中idx到next的距離)
            dist = distance[idx]+ps->path[idx][next];
            //若next為尋訪過且dist小於next到起點的距離
            //那就將next到起點的距離更新成dist
            //再將next的上一個父節點設為idx
            if(ps->visit[next]==0 && dist<distance[next]){
                distance[next] = dist;
                ps->parent[next] = idx;
            }
        }
    }
}
//透過ps->parent找出最短路徑走法
void findPath(path_s *ps, int current, int *p, int *p_size){
    if (ps->parent[current]==-1){ //回溯到起點
        p[(*p_size)++] = current;
        return;
    }
    findPath(ps,ps->parent[current],p,p_size);
    p[(*p_size)++]=current; //從起點開始，依序紀錄路徑
}

int main(){
    int n, x, z, y;
    y = -1;
    char *k, buffer;
    int p[max_p];//最後路徑
    path_s *ps;
    /*
    gets(buffer);
    k = strtok(buffer, " ");
    for(int i=0;i<4;i++){
        if(p==NULL) break;
        else if(i==0) n = k[0];
        else if(i==1) x = k[0];
        else if(i==2) z = k[0];
        else if(i==3) y = k[0];
        k = strtok(NULL, " ");
        printf("n = %d, x = %d\n", n, x);
        printf("z = %d, y = %d\n", z, y);
    }*/
    scanf("%d %d %d%c", &n, &x, &z, &buffer);
    if(buffer==' ') scanf("%d", &y);
    //printf("n = %d, x = %d\n", n, x);
    //printf("z = %d, y = %d\n", z, y);
    ps=(path_s *)malloc(sizeof(path_s));
    for(int i=0;i<max_p;i++){
        for(int j=0;j<max_p;j++){
            if(i==j) ps->path[i][j] = 0;
            else ps->path[i][j] = 1e9;//最大值
        }
    }
    //printf("test\n");
    ps->last = -1;
    while(n--){
        int a, b;
        scanf("%d %d", &a, &b);
        //將兩兩城市設為距離1
        ps->path[a][b] = 1;
        ps->path[b][a] = 1;
        //長到最後一個城市，才可以知道城市編號最後一個為甚麼
        if(ps->last < a) ps->last = a;
        if(ps->last < b) ps->last = b;
    }
    //printf("ps->last = %d\n", ps->last);
    dijkstra(ps, x);
    /*for(int i=1;i<=7;i++){
        for(int j=1;j<=7;j++){
            printf("%d ", ps->path[i][j]);
        }
        printf("\n");
    }*/
    if(y==-1){
        if(ps->visit[z]==0){
            printf("NO\n");
            return 0;
        }
        //從終點往前追溯，找出起點到終點最短路徑
        int p_size = 0;
        findPath(ps, z, p, &p_size);
        //將路徑長印出
        //並把經過的城市一一印出
        printf("%d\n", p_size-1);
        for(int i=0;i<p_size;i++){
            printf("%d ", p[i]);
        }
    }
    else{
        //起點x到必經過點y
        if(ps->visit[y]==0){//若不會經過y的話
            printf("NO\n");
            return 0;
        }
        int p_size = 0;
        findPath(ps, y, p, &p_size);//從中途點y追溯回起點x
        
        dijkstra(ps, y);
        if(ps->visit[z]==0){
            //中途點y不會到終點
            printf("NO\n");
            return 0;
        }

        findPath(ps, z, p, &p_size);

        //print
        printf("%d\n", p_size-2);//要減2是因為y重複
        for(int i=0;i<p_size;i++){
            printf("%d ", p[i]);
            if(p[i]==y) i++;
        }
    }
    return 0;
}