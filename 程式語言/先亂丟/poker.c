#include<stdio.h>
#include<stdbool.h>
#include<string.h>

typedef struct player{
    int point;
    bool life;
    int bet;
    int score;
}P;

typedef struct computer{
    int point;
    int score;
}C;

int findindex(char *p){
    char face[14][2] = {" ", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    for(int i=1;i<14;i++){
        if(p[0]==face[i][0]){
            if(i<=10) return i*10;
            else return 5;
        }
    }
}

int main(){
    P p[3];
    C c;
    int player_num;
    scanf("%d", &player_num);
    for(int i=0;i<player_num;i++){
        scanf("%d", &p[i].bet);
        //printf("p[%d].bet = %d\n", i, p[i].bet);
    }
    scanf("\n");
    char buffer[15], *q;
    gets(buffer);
    q = strtok(buffer, " ");
    c.point = findindex(q);
    q = strtok(NULL, " ");
    for(int i=0;i<player_num;i++){
        p[i].life = true;
        p[i].score = 0;
        p[i].point = findindex(q);
        q = strtok(NULL, " ");
    }
    //開始決定要不要要牌
    char yn, card;
    for(int i=0;i<player_num;i++){
        int time = 0;
        while(true){
            time++;
            yn = getchar();
            getchar();
            if(yn=='N') break;
            card = getchar();
            getchar();
            p[i].point+=findindex(&card);
            if(p[i].point>105){
                p[i].score = p[i].bet*-1;
                p[i].life = false;
                break;
            }
            else if(p[i].point==105 || time==4){
                p[i].life = false;
                p[i].score = p[i].bet;
                break;
            }
            //printf("yn = %c, card = %c\n", yn, card);
        }
        //printf("i = %d over\n", i);
    }

    //找活著且最小的
    int min = 105;
    for(int i=0;i<player_num;i++){
        if(min>p[i].point && p[i].life){
            min = p[i].point;
        }
    }
    //computer要牌
    if(min>c.point && min!=105){
        //printf("ready\n");
        while(true){
            card = getchar();
            getchar();
            c.point+=findindex(&card);
            if(c.point>=min || c.point>=105) break;
        }
    }

    //檢查
    for(int i=0;i<player_num;i++){
        if(p[i].life){
            if(c.point>=p[i].point && c.point<=105){
                p[i].score = p[i].bet*-1;
                p[i].life = 0;
            }
            else{
                p[i].score = p[i].bet;
                p[i].life = 0;
            }
        }
    }
    c.score = 0;
    for(int i=0;i<player_num;i++){
        c.score += p[i].score;
        printf("Player%d ", i+1);
        if(p[i].score>0) printf("+%d\n", p[i].score);
        else printf("%d\n", p[i].score);
    }
    c.score*=(-1);
    printf("Computer ");
    if(c.score>0) printf("+%d\n", c.score);
    else printf("%d\n", c.score);
    

}
/*
3
2 10 5
3 Q 3 10
Y 2
Y 7
N
Y 8
Y Q
7
*/
// -2 -10 +5 +7



/*
2
7 4
10 9 8
Y A
N
Y 2
N
*/
//-7 -4 +11

/*
3
4 5 6
A 2 3 4
Y A
Y 2
Y 3
Y 2
Y 7
Y K
Y 6
Y A
*/
//+4 +5 -6 -3

/*
3
4 5 6
A 4 3 2
N
N
N
2
*/
//+4 -5 -6 +7

/*
3
2 3 4
A 5 6 7
Y 5
N
Y 4
N
Y 3
N
8
3
*/

//10
//10
//10


//+2 +3 +4 -9