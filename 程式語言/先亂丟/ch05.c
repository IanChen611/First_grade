#include<stdio.h>
#include<stdbool.h>

int main(){
    //0都空著
    int fighter_score[10][3];//[安打數, 到本壘數][1~9號球員]
    int fighter_f[10][5];
    int b;
    //reset
    for(int i=1;i<10;i++){
        fighter_score[i][2] = i;
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
                //fighter_score[i][0]+=1;
                //printf("%d %d\n", i, fighter_score[i][0]);
            }
            else if(in[0]=='2'){
                fighter_f[i][k] = 2;
                //fighter_score[i][0]+=1;
                //printf("%d %d\n", i, fighter_score[i][0]);
            }
            else if(in[0]=='3'){
                fighter_f[i][k] = 3;
                //fighter_score[i][0]+=1;
                //printf("%d %d\n", i, fighter_score[i][0]);
            }
            else if(in[0]=='O'){
                fighter_f[i][k] = 0;
            }
            else if(in[0]=='H'){
                fighter_f[i][k] = 4;
                //fighter_score[i][0]+=1;
                //printf("%d %d\n", i, fighter_score[i][0]);
            }
        }
    }
    //for sure no mistake
    /*for(int k=1;k<10;k++){
        printf("%d ", fighter_score[k][1]);
    }*/
    //printf("\n");

    scanf("%d", &b);
    //printf("b = %d\n", b);
    //Start game
    int index_one = 1; //球員誰上場
    int index_two = 0; //第幾順位的出擊
    int out_num = 0;//出局多少人
    int base[4] = {0, 0, 0, 0};//壘包
    bool re = false;
    while(out_num<b){
        if(fighter_f[index_one][index_two]>=1){
            //printf("player=%d, fighter_f[index_one][index_two] = %d\n", index_one, fighter_f[index_one][index_two]);
            if(fighter_f[index_one][index_two]>=1 && fighter_f[index_one][index_two]<=4){
                fighter_score[index_one][0]+=1;
                for(int j=3;j>0;j--){
                    if(base[j-1]!=0){
                        base[j] = base[j-1];
                    }
                    else base[j] = 0;
                }
                if(base[3]!=0){
                    fighter_score[base[3]][1]+=1;
                    base[3] = 0;
                }
                base[0] = index_one;
                for(int i=0;i<fighter_f[index_one][index_two]-1;i++){
                    for(int j=3;j>0;j--){
                        if(base[j-1]!=0) base[j] = base[j-1];
                        else base[j] = 0;
                    }
                    base[0] = 0;
                    if(base[3]!=0){
                        fighter_score[base[3]][1]+=1;
                        base[3] = 0;
                    }
                }
            }
        }
        else if(fighter_f[index_one][index_two]==0){
            out_num+=1;
            re=true;
        }
        //printf("Player = %d", index_one);
        /*for(int i=0;i<3;i++){
            printf("%d");
        }*/
        if(out_num%3==0  && re){
            for(int i=0;i<4;i++) base[i] = 0;
            re = false;
        }
        index_one+=1;
        if(index_one>9){
            index_two+=1;
            index_one = 1;
        }
    }
    

    //sort 
    
    for(int i=1;i<10;i++){
        for(int j=1;j<10-i;j++){
            if(fighter_score[j][1]>fighter_score[j+1][1]){
                for(int c=0;c<3;c++){
                    int tem = fighter_score[j][c];
                    fighter_score[j][c] = fighter_score[j+1][c];
                    fighter_score[j+1][c] = tem;
                }
            }
            else if(fighter_score[j][1]==fighter_score[j+1][1] && fighter_score[j][2]<fighter_score[j+1][2]){
                for(int c=0;c<3;c++){
                    int tem = fighter_score[j][c];
                    fighter_score[j][c] = fighter_score[j+1][c];
                    fighter_score[j+1][c] = tem;
                }
            }
        }
    }
    int sum = 0;
    for(int i=1;i<10;i++){
        sum+=fighter_score[i][1];
    }
    //Print result
    printf("%d\n", sum);
    for(int i=9;i>=7;i--){
        printf("%d %d %d\n", fighter_score[i][2], fighter_score[i][0], fighter_score[i][1]);
    }

}
