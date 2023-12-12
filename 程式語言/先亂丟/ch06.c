#include<stdio.h>


void function1_1(int n);
void function1_2(int n);
void function2_1(int n);
void function2_2(int n, int k);
void function2_3(int n);
void function2_4(int n);
void function3_1(int n);
void function3_2(int n);
void function3_3(int n);


int main(){
    int gr;//圖形樣式
    int number;//幾層
    scanf("%d", &gr);
    scanf("%d", &number);


    if(gr==1){
        function1_1(number);
        function1_2(number);
    }
    else if(gr==2){
        function2_1(number);
    }
    else if(gr==3){
        function3_1(number);
    }
}






void function1_1(int n){
    for(int i=0;i<n;i++){
        for(int j=-1;j<i;j++){
            printf("%d", j+2);
        }
        printf("\n");
    }
}
void function1_2(int n){
    for(int i=n;i>0;i--){
        for(int j=i;j>0;j--){
            printf("%d", j);
        }
        printf("\n");
    }
}


//原呼叫函式
void function2_1(int n){
    for(int i=1;i<n;i++){
        function2_2(i, n);
        function2_3(i);
        function2_4(i);
        function2_2(i, n);
        printf("\n");
    }


    for(int i=n-1;i>=1;i--){
        function2_2(i, n);
        function2_3(i);
        function2_4(i);
        function2_2(i, n);
        printf("\n");
    }
}


//print "_"
void function2_2(int n, int k){
    for(int i=1;i<(k-n);i++){
        printf("_");
    }
}


//print(倒數的數字)(含1)
void function2_3(int n){
    for(int i=n;i>=1;i--){
        printf("%d", i);
    }
}


//print(正的數字)(不含1)
void function2_4(int n){
    for(int i=2;i<=n;i++){
        printf("%d", i);
    }
}


//3的主函式
void function3_1(int n){
    for(int i=1;i<=n;i++){
        function3_3(i);
        function3_2(i);
        printf("\n");
    }
}
//倒數
void function3_2(int n){
    for(int i=n-1;i>=1;i--){
        printf("%d", i);
    }
}
//正數 含n
void function3_3(int n){
    for(int i=1;i<=n;i++){
        printf("%d", i);
    }
}