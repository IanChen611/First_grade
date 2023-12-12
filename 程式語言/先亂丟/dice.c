#include<stdio.h>
#include<stdlib.h>

//骰子變動
void change(int a, int b, int one[], int two[]);

int main(){
    int ma; // 修正次數
    int A1[]={3, 1, 4, 6, 2, 5}; // {前，上，後，下，右，左}
    int A2[]={3, 1, 4, 6, 2, 5}; // {前，上，後，下，右，左}
    int B1[]={3, 1, 4, 6, 2, 5}; // {前，上，後，下，右，左}
    int B2[]={3, 1, 4, 6, 2, 5}; // {前，上，後，下，右，左}
    int a, b; // 修正的步驟

    // 處理A Dice
    scanf("%d", &ma);
    for(int i=0; i<ma; i++){
        scanf("%d %d", &a, &b);
        change(a, b, A1, A2);
    }
    //處理B Dice
    scanf("%d", &ma);
    for(int i=0; i<ma; i++){
        scanf("%d %d", &a, &b);
        change(a, b, B1, B2);
    }


    //把A1顯示用出來
    for(int i=0; i<6; i++){
        printf("%d ", A1[i]);
    }
    printf("\n");
    //把A2顯示用出來
    for(int i=0; i<6; i++){
        printf("%d ", A2[i]);
    }
    printf("\n");
    //把B1顯示用出來
    for(int i=0; i<6; i++){
        printf("%d ", B1[i]);
    }
    printf("\n");
    //把B2顯示用出來
    for(int i=0; i<6; i++){
        printf("%d ", B2[i]);
    }
    printf("\n");

    int suma = 0;
    int sumb = 0;
    if(A1[1]!=A2[1]){
        suma = A1[1]+A2[1];
    }
    if(B1[1]!=B2[1]){
        sumb = B1[1]+B2[1];
    }

    if(suma>sumb){
        printf("A win");
    }
    else if(suma<sumb){
        printf("B win");
    }
    else{
        printf("Tie");
    }
}

void change(int a, int b, int one[], int two[]){
    //array =  {前，上，後，下，右，左}
    //變數a 代表one該怎麼變
    //變數b 代表two該怎麼變
    //1代表向前滾
    //2代表向右滾
    if(a==1){
        int tem_forword = one[0];
        int tem_up = one[1];
        int tem_back = one[2];
        int tem_down = one[3];
        one[0] = tem_up;//原本的上面換成現在的前面
        one[1] = tem_back;//原本的後面換成現在的上面
        one[2] = tem_down;//原本的下面換成現在的後面
        one[3] = tem_forword;//原本的前面換成現在的下面面
    }
    if(b==1){
        int tem_forword = two[0];
        int tem_up = two[1];
        int tem_back = two[2];
        int tem_down = two[3];
        two[0] = tem_up;
        two[1] = tem_back;
        two[2] = tem_down;
        two[3] = tem_forword;
    }
    if(a==2){
        int tem_left = one[5];
        int tem_up = one[1];
        int tem_right = one[4];
        int tem_down = one[3];
        one[5] = tem_down;//原本的下面換成現在的左邊
        one[1] = tem_left;//原本的左邊換成現在的上面
        one[4] = tem_up;//原本的上面換成現在的右邊
        one[3] = tem_right;//原本的右邊換成現在的下面
    }
    if(b==2){
        int tem_left = two[5];
        int tem_up = two[1];
        int tem_right = two[4];
        int tem_down = two[3];
        two[5] = tem_down;
        two[1] = tem_left;
        two[4] = tem_up;
        two[3] = tem_right;
    }
}