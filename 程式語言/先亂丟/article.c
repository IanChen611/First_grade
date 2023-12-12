#include<stdio.h>
#include<string.h>
#include<stdbool.h>

// 計算單字頻率
void count_freq(int a_len, char a[], int *word_num,char words[][15], int freq[]); 
// 找出頻率最高的單字位置
void find_max_position(int word_num,int freq[],int *max_a_idx, char words[][15]);
// 刪除單字
void delete_word(int A_len, int P_len, char A_str[], char P_str[], char A_substr[]);

int main(){
    char a[150] = {'\0'};//a字串
    char a_copy[150] = {'\0'};//紀錄a的小字串，為了用在strcmp
    char p[150] = {'\0'};//p字串
    char q[150] = {'\0'};//q字串
    int n, c;//題目的n, c
    int a_idx = 0;//a的index
    int a_len, p_len, q_len;//各自串的長度
    int max_p = 0;//出現的最大頻率的單字
    int word_num = 0;//計算word陣列已有幾個字串了
    char words[30][15] = {'\0'};//出現過的單字存在這裡
    char low_feq_words[30][15] = {'\0'};//頻率小於N的單字
    int freq[30] = {0};//單字出現的次數
    //strcmp(A, b)
    //若回傳數值等於0，代表A B字串一樣

    scanf("%[^\n]", a);
    a_len = strlen(a);
    scanf("%s", p);
    p_len = strlen(p);
    scanf("%s", q);
    q_len = strlen(q);
    scanf("%d", &n);
    scanf("%d", &c);

    // C==1時將A中的P字串以Q字串取代
    // C==2在文句A中P字串前插入Q字串
    if(c==1 || c==2){
        while(a_idx<a_len){ //a_idx小於a的長度就繼續跑
            if(a[a_idx] == p[0]){ //當前字元與p的第一個字元相同
                if((a_idx!=0 && a[a_idx-1]!=' ') || (a[a_idx+p_len]!=' ' && a[a_idx+p_len]!='\0')){
                    a_idx++;
                    continue;;
                }
                //複製此子字串比較看看相不相等
                for(int i=0;i<p_len;i++){
                    a_copy[i] = a[a_idx+i];
                }
                //相等的話
                if(strcmp(p, a_copy)==0){
                    //將a字串從idx後面的資料往後移q字串的距離
                    for(int i=a_len+q_len;i>a_idx;i--){
                        a[i] = a[i-q_len-1];
                    }
                    for(int i=0;i<q_len;i++){
                        a[a_idx] = q[i];
                        a_idx++;
                    }
                    a_len += q_len+1;
                    a_idx += q_len;
                }
            }
            a_idx++;
        }
        if(c==1) delete_word(a_len, p_len, a, p, a_copy);
        printf("%s", a);
    }
    // C==3將文句A中刪除P字串
    else if(c==3){
        delete_word(a_len, p_len, a, p, a_copy);
        printf("%s", a);
    }
    // C==4
    //統計文句A中英文字出現的頻率前2名
    //頻率由高到低排，若頻率相同則以字母大小排序，大寫較小寫前面
    //用:隔開單字與頻率，一個單字與頻率一行
    //wish:11
    //the:4
    else if(c==4){
        //計算每個單字出現次數，存進word_num
        //printf("test\n");
        count_freq(a_len, a, &word_num, words, freq);
        /*for(int i=0;i<word_num;i++){
            printf("%s:%d\n", words[i], freq[i]);
        }
        */
        //找到出現次數最多的單字位置
        find_max_position(word_num, freq, &max_p, words);
        //把最大變為0
        freq[max_p] = 0;
        printf("\n");
        //再做一次即可找到第二高的
        find_max_position(word_num, freq, &max_p, words);
    }
    // C==5 將出現頻率小於N的單字刪掉
    else if(c==5){
        count_freq(a_len, a, &word_num, words, freq);
        int count = 0;//有幾個次數小於n的單字
        for(int i=0;i<word_num;i++){
            if(freq[i]<n){//該單字小於n 
                for(int j=0;j<15;j++){
                    low_feq_words[count][j] = words[i][j];
                }
                count++;
            }
        }
        //刪除次數低於n的單字
        for(int i=0;i<count;i++){
            a_len = strlen(a);
            p_len = strlen(low_feq_words[i]);
            delete_word(a_len, p_len, a, low_feq_words[i], a_copy);

            for(int j=0;j<10;j++){//刪除a_copy
                a_copy[j] = '\0';
            }
        }
        printf("%s", a);
    }
    return 0;
}

// 計算單字頻率
void count_freq(int a_len, char a[], int *word_num, char words[][15], int freq[]){
    int a_index = 0;
    bool same = false;//目前單字是否與words陣列中有一樣的
    while(a_index < a_len){
        //printf("此時a_index = %d, 字元為%c\n", a_index, a[a_index]);
        same = false;
        if(a[a_index]!=' '){    //當前字元不等於空白
            for(int i=0;i<*word_num;i++){//跟word陣列中的單字比較是否有相同的
                for(int j=0;j<15;j++){
                    //檢查的位置檢查到了空格處或是結束字元
                    if((a[a_index+j]==' ' || a[a_index+j]=='\0') && words[i][j] == '\0'){
                        //printf("與word中的第%d個相同, 結束檢查\n", i);
                        same = true;
                        a_index = a_index + j;
                        break;
                    }
                    //檢查到目前相同，繼續
                    if(a[a_index+j]==words[i][j]){
                        same = true;
                    }
                    //檢查字元與words中的第i個單字不同，跳出j迴圈
                    else{
                        same = false;
                        break;
                    }
                }
                if(same){
                    freq[i]++;
                    break;
                }
            }
            if(!same){
                //printf("same = false\n");
                for(int j=0;j<15;j++){
                    //printf("j = %d\n", j);
                    if(a[a_index]==' ' || a[a_index]=='\0'){
                        words[*word_num][j] = '\0';
                        //printf("已將%s加進第%d個\n", words[*word_num], *word_num);
                        break;
                    }
                    words[*word_num][j] = a[a_index];
                    a_index++;
                }
                freq[*word_num]++;
                *word_num+=1;
            }
        }
        a_index++;
    }
}
// 找出頻率最高的單字位置
void find_max_position(int word_num, int freq[], int *max_a_idx, char words[][15]){
    for(int i=0;i<word_num;i++){
        if(freq[i]>freq[*max_a_idx]){
            *max_a_idx = i;
        }
    }
    printf("%s:%d", words[*max_a_idx], freq[*max_a_idx]);
}
// 刪除單字
void delete_word(int a_len, int p_len, char a[], char p[], char a_copy[]){
    int a_index = 0;
    while(a_index < a_len){
        //當前字元與欲刪除字元第一個字相同
        if(a[a_index]==p[0]){
            if((a_index!=0 && a[a_index-1]!=' ') || (a[a_index + p_len]!=' ' && a[a_index + p_len]!='\0')){
                a_index++;
                continue;
            }
            //複製子字串到a_copy中
            for(int i=0;i<p_len;i++){
                a_copy[i] = a[i+a_index];
            }
            //若刪除者剛好為最後一個單字
            //要將此單字前面的空白設為結束字元
            if(strcmp(a_copy, p)==0){
                if(a_len-p_len==a_index){
                    a[a_index-1]='\0';
                }
                //若不是最後一個單字
                else{
                    for(int i=a_index;i<a_len-p_len;i++){
                        if(a[i+p_len]=='\0'){
                            a[i-1] = '\0';
                            break;
                        }
                        else a[i] = a[i+p_len+1];
                    }
                }
                a_len -= p_len;
            }
        }
        a_index++;
    }
}
