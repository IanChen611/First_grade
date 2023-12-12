#include<stdio.h>
#include<stdbool.h>

int main(){
    
    char number[16]; //一開始輸入的位置
    int converted_number[30]; //存轉換後的數字
    int before_radix, after_radix; //要轉換數字的進制、欲轉成之進位制
    unsigned long long num = 0; //轉換後的整數(10進位)
    bool error = false;
    char table[17] = "0123456789ABCDEF";

    //輸入
    scanf("%s", number);
    scanf("%d", &before_radix);
    scanf("%d", &after_radix);

    //check the radix
    if(before_radix>16 || before_radix<2 || after_radix>16 || after_radix<2) error = false;

    //check Number
    for(int i=0;number[i]!='\0';i++){
        for(int j=0;j<16;j++){
            if(j>=before_radix && table[j]==number[i]){
                error = true;
                break;
            }
        }
        if(error) break;
    }
    if(error) printf("ERROR\n");
    else{
        //轉成10進制
        for(int i=0;number[i]!='\0';i++){
            for(int j=0;j<16;j++){
                if(number[i]==table[j]){
                    num = num*before_radix + j;
                    break;
                }
            }
        }
        //printf("%d\n", num);
        int index = 0; //converted number現在輸入到哪了
        while(num>after_radix){
            converted_number[index] = num % after_radix;
            num = num / after_radix;
            index++;
        }
        converted_number[index] = num;
        for(int i=index;i>=0;i--){
            //converted_number[index] < 9時
            if(converted_number[i]<9){
                printf("%c" ,converted_number[i] + '0');
            }
            else{
                printf("%c", converted_number[i] + 'A' - 10);
            }
        }
    }
}