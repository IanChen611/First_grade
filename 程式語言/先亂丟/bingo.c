#include<stdio.h>
#include<stdbool.h>
#include<string.h>
typedef struct b
{
    int board[99999];
    int line;
}player;

int num_line(player a, int n){
    int rtn = 0;
    bool l = true;
    bool l2 = true;
    bool l3 = true;
    for(int i=0;i<n;i++){
        //橫的檢查
        l = true;
        for(int j=0;j<n;j++){
            if(a.board[i*n+j]!=0){
                l = false;
                break;
            }
        }
        if(l) rtn++;

        //直的檢查
        l = true;
        for(int j=0;j<n;j++){
            if(a.board[i+j*n]!=0){
                l = false;
                break;
            }
        }
        if(l) rtn++;

        //左上右下檢查
        if(a.board[i*(n+1)]!=0) l2 = false;

        //右上左下檢查
        if(a.board[n-1+i*(n-1)]!=0) l3 = false;
    }
    if(l2) rtn++;
    if(l3) rtn++;
    return rtn;
}


int main(){
    int n, m;
    scanf("%d %d\n", &n, &m);
    player a, b;
    char tem[160], *p;

    gets(tem);
    p = strtok(tem, " ");
    for(int i=0;i<n*n;i++){
        if(p[1]-'0'>=0 && p[1]-'0'<=9){
            a.board[i] = p[0] - '0';
            //printf("%d\n", a.board[i]);
            a.board[i]*=10;
            a.board[i]+=(p[1]-'0');
            //printf("%d\n", a.board[i]);
        }
        else a.board[i] = p[0] - '0';
        p = strtok(NULL, " ");
        //printf("i = %d, a.borad[i] = %d\n", i, a.board[i]);
    }
    /*
    for(int i=0;i<9;i++){
        printf("%d ", a.board[i]);
        if(i%3==2) printf("\n");
    }
    */
    gets(tem);
    p = strtok(tem, " ");
    for(int i=0;i<n*n;i++){
        if(p[1]-'0'>=0 && p[1]-'0'<=9){
            b.board[i] = p[0] - '0';
            b.board[i]*=10;
            b.board[i]+=(p[1]-'0');
        }
        else b.board[i] = p[0] - '0';
        p = strtok(NULL, " ");
    }
    gets(tem);
    p = strtok(tem, " ");
    while(p!=NULL){
        int t = p[0] - '0';
        for(int i=0;i<n*n;i++){
            if(a.board[i]==t) a.board[i] = 0;
            if(b.board[i]==t) b.board[i] = 0;
        }
        /*
        for(int i=0;i<n*n;i++){
            printf("%d ", a.board[i]);
            if(i%n==(n-1)) printf("\n");
        }
        printf("\n");
        for(int i=0;i<n*n;i++){
            printf("%d ", b.board[i]);
            if(i%n==(n-1)) printf("\n");
        }
        */
        //判別幾條線
        a.line = num_line(a, n);
        b.line = num_line(b, n);
        //printf("t = %d, a.line = %d, b.line = %d\n", t, a.line, b.line);
        if(a.line>=1 || b.line>=1) break;
        p = strtok(NULL, " ");
    }
    if(a.line == b.line) printf("Tie\n");
    else if(a.line>b.line) printf("A Win\n");
    else printf("B Win\n");
}
/*
3 4
6 1 8 4 7 2 5 9 3
9 6 4 5 1 8 2 7 3
6 1 7 3
*/

/*
3 8
1 2 3 4 5 6 7 8 9
2 3 4 5 1 6 9 7 8
7 2 3 6 9 8 4 1
*/

/*
3 5
1 2 3 4 5 6 7 8 9
5 7 4 6 8 2 1 9 3
1 2 5 4 8
*/

/*
4 8
16 6 11 5 10 4 13 3 14 15 9 12 7 2 8 1
8 1 3 11 12 5 14 9 13 4 6 2 15 16 7 10
9 1 3 5 7 8 10 13
*/