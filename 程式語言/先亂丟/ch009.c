#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    /*
    106   /   3  =  35 + 1
    106   / (-3) = -35 + 1
    (-106)/   3  = -36 + 2
    (-106)/ (-3) = 36 + 2
    */
    //141978786712730563351144765151826
    //190277493795263785923452478
    char di[40]; //除數
    char died[40]; //被除數
    char di_copy[40]; //除數的複製
    char ans[40]; //商
    bool sign_1 = false;//被除的符號
    bool sign_2 = false;//除數的符號
    bool sign_ans = false;//商的符號
    int len_differ;//(被除數-除數)
    int len_differ_copy; //純粹複製
    bool modiszero = true;
    int mode = 0;//(0代表兩者皆相等)(1代表被除數大於除數)(2代表被除數小於除數)
    int count = 0, index;
    scanf("%s", died);
    scanf("%s", di);
    //printf("died = %s\n", died);
    //printf("di = %s\n", di);


    int len_died = strlen(died) - 1; //被除數的長度
    int len_di = strlen(di) - 1; // 除數的長度
    if(died[0]=='-'){
        sign_1 = true;//died < 0
        for(int i=0;i<len_died;i++){
            died[i] = died[i+1];
        }
        died[len_died] = '\0';
        len_died--;
    }
    if(di[0]=='-'){
        sign_2 = true;//di < 0
        for(int i=0;i<len_di;i++){
            di[i] = di[i+1];
        }
        di[len_di] = '\0';
        len_di--;
    }
    if(sign_1!=sign_2) sign_ans = true;//ans負的

    //複製除數
    len_differ = len_died - len_di;
    len_differ_copy = len_differ;
    //原本被除數為12345
    //除數為123\0
    //則di_copy中就為00123\0
    for(int i=len_died;i>=len_differ;i--){
        di_copy[i] = di[i-len_differ];
    }
    for(int i=len_differ-1;i>=0;i--){
        di_copy[i] = '0';
    }
    for(int i=len_di+1;i<=len_died;i++){
        di[i] = '0';
    }

    //開始檢查每一位數並進行相減
    while(true){
        for(int i=0;i<=len_died;i++){
            if(died[i]>di[i]){
                mode = 1;
                break;
            }
            else if(died[i]<di[i]){
                mode = 2;
                break;
            }
            else{}
        }
        if(mode==0){
            count++;//原本為0
            for(int i=0;i<len_differ;i++){
                count = count * 10;
            }
            if(sign_ans){
                printf("-");
            }
            printf("%d\n0\n", count);
            return 0;
        }

        //mode 1
        else if(mode==1){
            index = len_died;
            while(true){
                if(died[index]>=di[index]){
                    died[index] = died[index] - di[index] + '0';
                }
                else{
                    int borrow = index - 1;
                    while(true){
                        if(died[borrow]>0){
                            died[borrow] = died[borrow] - 1;
                            for(int i=borrow+1;i<index;i++){
                                died[i] = '9';
                            }
                            died[index] = died[index] - di[index] + 10 + '0';
                            break;
                        }
                        else borrow--;
                    }
                }
                index--;
                if(index<0) break;
            }
            count++;
        }

        //mode = 2
        else if(mode==2){
            //當除數慢慢除10後變成原本的除數時
            if(strncmp(di_copy, di, len_died+1)==0){
                ans[len_differ] = count + '0';
                //已經不能再減了
                //所以跳出迴圈
                break;
            }
            else{
                //除數/10
                for(int i=len_died+1;i>0;i--){
                    di[i] = di[i-1];//往右移一位
                }
                di[0] = '0';
                ans[len_differ] = count + '0';
                count = 0;
                len_differ--;
            }
        }/*
        printf("count = %d, died = ", count);
        bool start = false;
        for(int i=len_differ_copy;i>=0;i--){
            if(ans[i]!='0') start = true;
            if(start) printf("%c", ans[i]);
        }
        printf("\n");*/
    }
    if((sign_1 && sign_2)||(sign_1 && !sign_2)){
        for(int i=0;i<=len_died;i++){
            if(died[i]!='0'){
                modiszero = false;
                break;
            }
        }
        if(!modiszero){
            ans[0] += 1;
            index = len_died;
            while(true){
                if(di[index] >= died[index]){
                    died[index] = di[index] - died[index] +'0';
                }
                else{
                    int borrow = index - 1;
                    while(true){
                        if(di[borrow]>0){
                            di[borrow] = di[borrow] - 1;
                            for(int i=borrow+1;i<index;i++){
                                di[i] = '9';
                            }
                            died[index] = 10 + '0' - died[index] + di[index];
                            break;
                        }
                        else borrow--;
                    }
                }
                index--;
                if(index<0) break;
            }
        }
    }
    bool start = false;
    if(sign_ans) printf("-");
    for(int i=len_differ_copy;i>=0;i--){
        if(ans[i]!='0') start = true;
        if(start) printf("%c", ans[i]);
    }
    printf("\n");
    start = false;
    for(int i=0;i<=len_died;i++){
        if(died[i]!='0') start = true;
        if(start) printf("%c", died[i]);
    }
    if(!start) printf("0\n");
    return 0;
}