#include <stdio.h>
#include <stdbool.h>
 
int main()
{
    char number[16];            // 存待轉換數字
    char converted_number[30];  // 存十進制整數除指定的轉換進制的餘數
    int before_radix;           // 待轉換數字的進制
    int after_radix;            // 指定的轉換進制
    int count = 0;
    unsigned long long num = 0;      // 轉換後的十進制整數
    bool error = false;
    char table[17] = "0123456789ABCDEF";
    // 輸入待轉換數字
    //printf("請輸入待轉換數字 : ");
    scanf("%s",number);

    // 輸入待轉換數字的進制(2~16)
    //printf("待轉換數字的進制(2~16) : ");
    scanf("%d", &before_radix);

    // 輸入指定的轉換進制(2~16)
    //printf("輸入指定的轉換進制(2~16) : ");
    scanf("%d", &after_radix);
    // 判斷待轉換數字的進制和指定的轉換進制是否在2~16內
    if(before_radix < 2 || before_radix > 16 || after_radix < 2 || after_radix >16)
    {
        error = true;
    }
    	
    else
    {
        // 將待轉換數字的進制整數按索引值展開後轉換為十進制整數
        for (int i = 0; number[i] != '\0'; i++) // '\0'在c語言中代表著字串的結束         
        {   
            // 檢查輸入是數字還是字母
            if(number[i] >= '0' && number[i] <= '9') //將字元減掉字元0轉換為數字，並利用檢查輸入是否小於字元9來判斷輸入是數字還是字母
            {
                // 檢查轉換數字與進制是否矛盾
                if(number[i] - '0' >= before_radix)
                {
                    error = true;
                    break;
                }
                else
                    num = num * before_radix + number[i] - '0';
            }
            else
            {
                if(number[i] - 'A' + 10 >= before_radix) //ASCII中英文大寫的編碼從編號65開始
                {
                    error = true;
                    break;
                }
                else
                    num = num * before_radix + number[i] - 'A' + 10;
            }        
        }
    }
    if(error == true)
    {
        printf("ERROR");
    }
    else
    {   
        // 十進制整數採用“除 指定的轉換進制 取餘”轉換為指定的轉換進制整數
        do {                    
 
            converted_number[count] = num % after_radix;
            count++;
        
            num = num / after_radix;
 
        } while (num != 0);
 
        // 將字串converted_number反轉後輸出
        for (int i = count - 1; i >= 0; i--)
        {
            if(converted_number[i] == '\0')
                printf("0");
            else
                printf("%c", table[converted_number[i]]);
        }
 
    }
 
    return 0;
}