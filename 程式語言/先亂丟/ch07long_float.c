#include <stdio.h>
#include <string.h>

#define MID_POS 60
#define LAST_POS 120

typedef struct LongNumAry{
    int digits[LAST_POS+1]; //digits[0]為符號位，0代表正非0代表負
} LongNum;

//正變負、負變正
void negate(LongNum *ln){  
    //取九補數+1=>10補數
    int i,carry,n;
    //九補數+"1"，視為最低位也有進位
    carry=1;

    for (i=LAST_POS;i>=0;i--){ 
        n=9-ln->digits[i]+carry;
        if (n>9){
            n-=10;
            carry=1;
        }
        else carry=0;
        ln->digits[i]=n;
    }
}
	
//將輸入的字串轉為數字陣列
//ln->digits[0]為符號(0為正、非0為負)
//ln->digits[1..60]為整數、ln->digits[61..120]為小數
//不儲存小數點
void fillNum(char *c, LongNum *ln){
    int i,negative,fillTo;
    char *p;
    
    memset(ln->digits,0,sizeof(LongNum));
    if (*c=='-'){
        negative=1;
        c++;
    }
    else negative=0;
        
    p = strchr(c,'.');  //找到小數點的位置
    if (p==NULL) //沒有小數點，整數
        p = c + strlen(c);  //相當於小數點在最右位
    
    //假設1234.56，p指到小數點的位置(索引0開始，第4位)
    //1填入整數陣列時應填在索引值為57的位置
    //57=60(MID_POS)-4(小數點位置和1的距離)+1
    //大致上是000....0001234|5600....000
    //索引值為0123....(57)(58)(59)(60)|(61)(62).....
    fillTo=MID_POS-(p-c)+1;
    while (*c && fillTo<=LAST_POS){
        if (c!=p) //不儲存小數點
        ln->digits[fillTo++]=*c-'0';
        c++;
    }
    if (negative)
        negate(ln);
}
	
void fillStr(LongNum *ln, char *buffer){
    int negative,i,n;
    negative=(ln->digits[0]!=0);
    if (negative){ 
        *buffer='-';
        buffer++;
        negate(ln); //後面轉為正數輸出
    }
    
    i=1;
    n=0; //判斷已經轉換幾位數了
    while (i<=MID_POS){ //處理整數
        if (ln->digits[i]==0 && n==0){
            i++;
            continue;
        }
        *buffer=ln->digits[i++]+'0';
        buffer++;
        n++;
    }
    if (n==0) //整數部分全為0
        *buffer='0';
        buffer++;
    
    //處理小數部分
    n=0;
    i=LAST_POS;
    while (i>MID_POS){
        if (ln->digits[i]==0 && n==0){
            i--;
            continue;
        }
        n++;
        i--;
    }
    if (n>0){ //有小數部分
        *buffer++='.';
        for (i=0;i<n;i++){
            *buffer++=ln->digits[i+MID_POS+1]+'0';
        }
    }
    *buffer++='\0'; //字串終結
    if (negative)
        negate(ln);  //轉回負數
}
	
void add(LongNum *ln1, LongNum *ln2, LongNum *rtn){
    int carry,i,n;
    carry=0;
    for (i=LAST_POS;i>=0;i--){
        n=ln1->digits[i]+ln2->digits[i]+carry;
        if (n>9){
            n-=10;
            carry=1;
        }
        else
            carry=0;
        rtn->digits[i]=n;
    }
}
	
void multiple(LongNum* ln1, LongNum* ln2, LongNum* rtn){
    int negative1,negative2,i,j,carry,n,m;
    negative1=ln1->digits[0]!=0;
    negative2=ln2->digits[0]!=0;
    
    for (i=0;i<=LAST_POS;i++)  //將結果先填0
        rtn->digits[i]=0;
    
    //一律先轉為正數再計算
    if (negative1)
        negate(ln1);
    if (negative2)
        negate(ln2);
    
    //要乘的兩個數，分別以i,j代表索引值
    //i, j=0: 符號位
    //i, j=1 to LAST_POS 且 num1[i]*num2[j]要加到第[i+j-MID_POS]位
    //1<=i+j-MID_POS<=LAST_POS
    //max(MID_POS-i,1)<=j<=min(LAST_POS+MID_POS-i,LAST_POS)
    for (i=LAST_POS;i>=1;i--){
        if (ln1->digits[i]==0) continue;
        
        //取j的最小值
        n=MID_POS-i;
        if (n<1) n=1;
        //取j的最大值
        m=LAST_POS+MID_POS-i;
        if(m>LAST_POS) m=LAST_POS;
    
        //乘法計算：
        for (j=m;j>=n;j--){
            if (ln2->digits[j]==0) continue;
            rtn->digits[i+j-MID_POS]+=ln1->digits[i]*ln2->digits[j];
        }
    }
    
    //處理進位
    carry=0;
    for (i=LAST_POS;i>=1;i--){
        rtn->digits[i]+=carry;
        if (rtn->digits[i]>=10){
            carry=rtn->digits[i]/10;
            rtn->digits[i]%=10;
        }
        else
            carry=0;
    }
    
    //若本來是負數，計算完將數值轉回原本的
    if (negative1)
        negate(ln1);
    if (negative2)
        negate(ln2);
    //結果為一正一負
    // ^ 是XOR的意思
    if (negative1 ^ negative2)
        negate(rtn);
}
int main(){
    LongNum num1,num2,num3;
    char s1[LAST_POS+1];
    char s2[LAST_POS+1];
    char buffer[LAST_POS+1];
    scanf("%s",s1);
    scanf("%s",s2);
    fillNum(s1,&num1);
    fillNum(s2,&num2);
    
    //加
    add(&num1,&num2,&num3);
    fillStr(&num3,buffer);
    printf("%s\n",buffer);
    //減(加負值)
    negate(&num2);
    add(&num1,&num2,&num3);
    negate(&num2);
    fillStr(&num3,buffer);
    printf("%s\n",buffer);
    //乘
    multiple(&num1,&num2,&num3);
    fillStr(&num3,buffer);
    printf("%s",buffer);
    return 0;
}