#include<stdio.h>
#include<string.h>
#include<stdbool.h>

typedef struct ln{
    int point_index ;
    int int_number[120];
    int last_po;
    int sign;
}ln;


int main(){
    char t_one[122];
    char t_two[122];
    scanf("%s", t_one);
    scanf("%s", t_two);
    printf("%s\n", t_one);
    ln one, two;
    int index;
    //將t_one放入one
    bool point = true;
    for(int i=0;i<122;i++){
        index = i;
        if(i==0 && t_one[0]=='-'){
            one.sign = 1;
        }
        else if(i==0) one.sign = 0;
        
        if(t_one[i]=='.'){
            one.point_index = i;
            i++;
            point = false;
        }
        if()
    }
    

}