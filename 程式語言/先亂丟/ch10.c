#include<stdio.h>
#include<stdbool.h>

int f1(){
    int n;
    scanf("%d", &n);
    if(n<1 || n>30) printf("Error\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<i+1;j++){
            printf("*");
        }
        for(int j=n-i;j>0;j--){
            printf("%d", j);
        }
        printf("\n");
    }
}

int f2(){
    int n1, n2;
    scanf("%d", &n1);
    scanf("%d", &n2);
    bool o = false;
    if(n1<1 || n1>3) o = true;
    else if(n2<1 || n2>29 || n2%2!=1) o = true;
    //right triangle
    else if(n1==1){
        for(int i=0;i<n2;i++){
            for(int j=0;j<=i;j++){
                printf("*");
            }
            printf("\n");
        }
    }
    //left Triangle diagram
    else if(n1==2){
        for(int i=0;i<n2/2+1;i++){
            for(int j=n2/2-i;j>0;j--){
                printf("#");
            }
            for(int j=0;j<=i;j++){
                printf("*");
            }
            printf("\n");
        }
        for(int i=n2/2;i>=0;i--){
            for(int j=n2/2-i;j>0;j--){
                printf("#");
            }
            for(int j=0;j<=i;j++){
                printf("*");
            }
            printf("\n");
        }
    }

    else if(n1==3){
        for(int i=1;i<=n2/2+1;i++){
            for(int j=0;j<n2/2-i+1;j++){
                printf("#");
            }
            for(int j=0;j<i*2-1;j++){
                printf("*");
            }
            printf("\n");
        }
        for(int i=n2/2;i>0;i--){
            for(int j=0;j<(n2-i)/2;j++){
                printf("#");
            }
            for(int j=0;j<i*2-1;j++){
                printf("*");
            }
            printf("\n");
        }
    }
    if(o) printf("Error\n");
}

int main(){
    while(true){
        int n;
        scanf("%d", &n);
        if(n==1) f1();
        else if(n==2) f2();
        else if(n==0) break;
        else{
            printf("Error\n");
            break;
        }
    }
}