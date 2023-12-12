#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int gcd(int, int);
void swap(int *, int *);
int abs(int);

int main(){
    while(1){
        int a_1, a_2, b_1, b_2;
        int out_1, out_2;
        scanf("%d/%d", &a_1, &a_2);
        scanf("%d/%d", &b_1, &b_2);
        char sign[2];
        scanf("%s", sign);
        char co[2];
        scanf("%s", co);

        //分母為0
        if(a_2==0 || b_2==0){
            printf("ERROR\n");
            if(co[0]=='n') break;
            continue;
        }
        // + - 法
        else if(sign[0]=='+' || sign[0]=='-'){
            int g = gcd(a_2, b_2);
            if(sign[0]=='+'){
                out_1 = (a_1 * (b_2/g))+(b_1 * (a_2/g));
                //printf("plus\n");
                //printf("g = %d, out_1 = %d\n", g, out_1);
            }
            else{
                out_1 = (a_1 * (b_2/g))-(b_1 * (a_2/g));
                //printf("minus\n");
                //printf("g = %d, out_1 = %d\n", g, out_1);
            }
            out_2 = a_2 * b_2 / g;
        }
        else{
            if(sign[0]=='/'){
                swap(&b_1, &b_2);
            }
            //printf("b_1 = %d, b_2 = %d\n", b_1, b_2);
            //
            out_1 = a_1 * b_1;
            out_2 = a_2 * b_2;
        }
        if(out_2==0){
            printf("ERROR\n");
            if(co[0]=='n') break;
            continue;
        }
        //printf("out_1 = %d, out_2 = %d\n", out_1, out_2);
        bool carry_bool = false;//帶分數存不存在
        bool out_sign = false;//是不是負數
        if(out_1 == 0){
            printf("0\n");
            if(co[0]=='n') break;
            else continue;
        }

        int new_g = gcd(abs(out_1), abs(out_2));
        out_1 = out_1 / new_g;
        out_2 = out_2 / new_g;
        //printf("out_1 = %d, out_2 = %d\n", out_1, out_2);
        
        //輸出
        if((out_1 < 0 && out_2 > 0) || (out_2 < 0 && out_1 > 0)) out_sign = true;
        out_1 = abs(out_1);
        out_2 = abs(out_2);
        //printf("out_1 = %d, out_2 = %d\n", out_1, out_2);
        //帶分數的部分
        int carry = out_1 / out_2;
        out_1 = out_1 % out_2;
        //printf("carry = %d, out_1 = %d\n", carry, out_1);
        /*if(out_1>out_2){
            while(out_1>=out_2){
                carry+=1;
                out_1 -= out_2;
            }
        }*/
        //負號
        if (out_sign) printf("-");
        //帶分數的整數
        if(carry!=0){
            printf("%d", carry);
            if(out_1!=0) carry_bool = true;
            else{
                printf("\n");
                if(co[0]=='n') break;
                continue;
            }
        }
        if(carry_bool) printf("(%d/%d)\n", out_1, out_2);
        if(!carry_bool) printf("%d/%d\n", out_1, out_2);
        if(co[0]=='n') break;
        
    }
}

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

int gcd(int a, int b){
    while(a>0 && b>0){
        if(a>b){
            a = a - b;
            if(a==0){
                return b;
                break;
            }
        }
        else if(a==b) return a;
        else{
            b = b - a;
            if(b==0){
                return a;
                break;
            }
        }
    }
}

int abs(int a){
    if(a>0) return a;
    else return a*-1;
}