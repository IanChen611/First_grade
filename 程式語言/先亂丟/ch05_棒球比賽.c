#include<stdio.h>
#include<stdbool.h>

void move(int, int, int [4], int [10][2], int *);

int main(){
    int fighter_score[10][2];//紀錄[安打幾次, 到本壘幾次][0空著][1~9號球員]
    int fighter_f[10][5];//安打與否[0空著][1~9號球員]
    int b;//第幾個出局
    int score = 0;
    //reset
    for(int i=0;i<9;i++){
        for(int j=0;j<2;j++){
            fighter_score[i][j] = 0;
        }
    }

    //input
    for(int i=1;i<10;i++){
        int j;
        scanf("%d", &j);
        for(int k=0;k<j;k++){
            char in[2];
            scanf("%s", in);
            if(in[0]=='1'){
                fighter_f[i][k] = 1;
                fighter_score[i][0]+=1;
            }
            else if(in[0]=='2'){
                fighter_f[i][k] = 2;
                fighter_score[i][0]+=1;
            }
            else if(in[0]=='3'){
                fighter_f[i][k] = 3;
                fighter_score[i][0]+=1;
            }
            else if(in[0]=='O'){
                fighter_f[i][k] = 0;
            }
            else if(in[0]=='H'){
                fighter_f[i][k] = 4;
                fighter_score[i][0]+=1;
            }
        }
        
    }
    scanf("%d", &b);

    //Start
    int index_one = 1; //球員誰上場
    int index_two = 0; //某球員第幾次打
    int out_num = 0;   //出局幾個了
    int base[4] = {0, 0, 0, 0};//壘包
    while(out_num<b){
        if(out_num%3==0 && out_num!=0){
            for(int i=0;i<4;i++) base[i]=0;
        }
        if(index_one>9){
            index_two+=1;
            index_one = 1;
        }
        if(fighter_f[index_one][index_two]){
            move(index_one, fighter_f[index_one][index_two], base, fighter_score, &score);
            for(int i=0;i<4;i++) printf("%d ", base[i]);
            printf("\n");
        }
        else{
            out_num+=1;
        }
        index_one+=1;
    }
    printf("%d\n", score);
    //sort
    
    for(int i=1;i<=3;i++){
        printf("%d %d %d\n", i, fighter_score[i][0], fighter_score[i][1]);
    }
    
}

void move(int player, int num, int base[4], int fighter_score[10][2], int *score){
    if(base[3]){
        fighter_score[base[3]][1]+=1;
        score+=1;
    }
    //printf("Test\n");
    for(int i=3;i>0;i--){
        if(base[i-1]!=0) base[i] = base[i-1];
        else base[i]=0;
    }
    //for(int i=0;i<4;i++) printf("%d ", base[i]);
    //printf("\n");
    //printf("base[1]=%d\n", base[1]);
    base[0] = player;
    num-=1;
    //printf("num = %d\n", num);
    for(int k=0;k<num-1;k++){
        //
        printf("Test\n");
        for(int i=3;i>0;i--){
            if(base[i-1]!=0) base[i] = base[i-1];
            else base[i]=0;
        }
        base[0] = 0;
        if(base[3]!=0){
            fighter_score[base[3]][1]+=1;
            score+=1;
        }
    }
}