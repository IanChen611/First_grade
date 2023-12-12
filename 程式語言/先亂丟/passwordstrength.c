#include<stdio.h>
#include<string.h>
#include<stdbool.h>

//strchr(a, b) => 查b有沒有在a裡面, 沒有就回傳NULL
float calau(char *s){
    const char *a = "~!@#$%^&*<>_+=";
    float ans = 0;
    int digit_cnt = 0, grp_cnt = 0;
    while(*s){
        //printf("current:%c\n", *s);
        //數字0~9
        if(*s>='0' && *s<='9'){
            ans+=2;
            grp_cnt++;
            if(grp_cnt==1){
                digit_cnt++;
            }
            else if(grp_cnt==2){
                digit_cnt--;
            }
        }
        else{
            grp_cnt = 0;
            if(*s >= 'A' && *s<='Z'){
                ans+=3;
            }
            else if(*s >= 'a' && *s <= 'z'){
                ans+=1;
            }
            else if(strchr(a, *s)!=NULL){
                ans+=4.5;
            }
        }
        s++;
        //printf("ans = %f\n", ans);
    }
    if(digit_cnt>=5){
        ans+=10;
    }
    return ans;
}
int main(){
    char buffer[100], max_char[100], min_char[100];
    float score, max, min;
    max = 0;
    min = 1e9;
    int i = 0;
    while(gets(buffer)){
        //printf("%d\n", ++i);
        if(strcmp(buffer, "-1")==0){
            break;
        }
        score = calau(buffer);
        //printf("score = %f\n", score);
        if(score < min){
            strcpy(min_char, buffer);
            min = score;
        }
        if(score > max){
            strcpy(max_char, buffer);
            max = score;
        }
    }
    printf("%s %.1f\n", max_char, max);
    printf("%s %.1f\n", min_char, min);
}