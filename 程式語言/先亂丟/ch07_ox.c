#include<stdio.h>
#include<stdbool.h>
#include<string.h>

typedef struct OXgame{
    int chess[9];
    int remain;
    int sp;
} OX;


//判斷直橫線還需下的數量
//回傳玩家(1) or computer(2) 還需下幾次
//若return -1即代表無法連線
//如果差一次就連線，該位置會填入game->sp
int judge(int index, int delta, int player, OX *game){
    int c = 0; //還需下的數量
    for(int i=0;i<3;i++){
        if(game->chess[index]==0) c++;
        else if(game->chess[index]!=player) return -1;
        index+=delta;
    }
    //當還需下的數量為1時 = 再下一步就贏了
    if(c==1){
        for(int i=0;i<3;i++){
            index-=delta;//逆回去
            if(game->chess[index]==0){
                game->sp = index;
                break;
            }
        }
    }
    //printf("還需要下的數量為:%d\n", c);
    return c;
}

//judge此函式會找出該線是否會贏
//find_win_ps 會回傳有幾條符合 橫/直/斜 的線
//n = 0是尋找已連線有幾個
//n = 1是即將連線的有幾個 game->sp 即為需要的下的位置

int find_win_ps(int player, int n, OX *game){
    int c = 0;//幾條線符合
    for(int i=0;i<3;i++){
        //判斷橫線
        if(judge(i*3, 1, player, game)==n) c++;
        //判斷直線
        if(judge(i, 3, player, game)==n) c++;
    }
    //左上右下斜線
    if(judge(0, 4, player, game)==n) c++;
    //右上左下斜線
    if(judge(2, 2, player, game)==n) c++;
    //printf("有幾條線符合:%d\n", c);
    return c;
}

int check(OX *game){
    //檢查 三條橫線、三條直線、兩條對角 是否有連線
    //若有連線(即c>=1) 回傳player
    for(int player=1;player<=2;player++){
        if(find_win_ps(player, 0, game)>=1) return player;
    }
    //若沒有連線，檢查棋盤是否下滿，下滿即為平手(3)
    if(game->remain==1){//棋盤差一個空位
        if(find_win_ps(1, 1, game)==0 && find_win_ps(2, 1, game)==0) return 3;
    }
    //4則未分出勝負
    return 4;
}

int sp(OX* game){
    //如果computer下一步可贏
    //回傳下一次可贏的位置
    if(find_win_ps(2, 1, game)>0) return game->sp+1;
    //玩家要贏的話
    //下一步即為對手要贏的那個位置
    if(find_win_ps(1, 1, game)>0) return game->sp+1;
    //若沒有影響勝負
    for(int i=0;i<9;i++){
        if(game->chess[i]==0) return i+1;
    }
}


int main(){
    OX game;
    game.remain = 9;
    memset(game.chess, 0, sizeof(game.chess));
    int m, n;
    scanf("%d %d", &m, &n);
    int current = m;
    int N = n*2;
    int winstate = 4;
    bool error = false;
    while(N--){
        int tem;
        scanf("%d", &tem);
        tem--;
        //printf("\n tem = %d\n", tem);
        //printf("winstate = %d\n", winstate);
        if(winstate!=4) continue;
        else if(tem<0 || tem>8){
            error = true;
            N++;
        }
        else if(game.chess[tem]!=0){
            error = true;
            N++;
        }
        else{
            //printf("current = %d\n", current);
            game.chess[tem] = current;
            game.remain--;
            winstate = check(&game);
            current = 3 - current;
        }
    }
    //if(m!=1 && m!=2) error = true;
    if(error) printf("Error\n");
    else printf("OK\n");

    for(int i=0;i<9;i++){
        printf("%d ", game.chess[i]);
        if(i%3==2) printf("\n");
    }
    printf("%d\n", winstate);
    if(winstate==4) printf("%d\n", sp(&game));
}