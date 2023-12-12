#include<stdio.h>

int gcd(int a, int b){
    while(a>0 && b>0){
        printf("a = %d, b = %d\n", a, b);
        if(a>b){
            a = a - b;
            printf("++a = %d, b = %d\n", a, b);
            if(a==0){
                return b;
                break;
            }
        }
        else if(a==b) return a;
        else{
            b = b - a;
            printf("--a = %d, b = %d\n", a, b);
            if(b==0){
                return a;
                break;
            }
        }
    }
}

int main(){
    int a = 6, b = 7;
    printf("%d\n", gcd(a, b));
}