#include<stdio.h>
#include<stdbool.h>

int card_type(int arr[]); // 找出該組牌的最大牌型

int main()
{
    char Face[] = {'2','3','4','5','6','7','8','9',' ','J','Q','K','A'}; // 把10略過可以讓陣列保持一維，另外作判斷看數字是否為10
    char Suit[] = {'C','D','H','S'};
    char set[10][5]; // 以字串方式儲存牌組
    int  set_int[10] = {0}; // 把牌組存成整數
    int  set_1_int[5], set_2_int[5]; // 第一組牌, 第二組牌
    int type1 = 0, type2 = 0;
    bool is_Duplicate = false;
    // 輸入兩組牌
    //printf("請輸入第一組牌：");
    scanf("%s %s %s %s %s",set[0],set[1],set[2],set[3],set[4]);
    //printf("請輸入第二組牌：");
    scanf("%s %s %s %s %s",set[5],set[6],set[7],set[8],set[9]);
    // 把牌組轉換成對應數字 Face * 10 + Suit 
    for(int i = 0; i < 10; i++) //每次迴圈分別計算每張牌的對應數字
    {
        for(int j = 0; j < 13; j++ )
        {
            if(set[i][0] == Face[j]) //判斷牌面點數是否是 2, 3, ..., 9 或 J, Q, K, A
            {
                for(int k = 0; k < 4;k++) //判斷花色( C, D, H, S )
                {
                    if(set[i][1] == Suit[k]) //判斷陣列第二個字元是否等於當前花色
                    {
                        set_int[i] = (j + 2) * 10 + k ; //將牌面轉換為整數，最小值為 20 (對應牌面: 2C)
                    }
                }
                if(set[i][2] != '\0')
                {
                    printf("Error input");
                    return 0;
                }
            }
            else if(set[i][0] == '1' && set[i][1] == '0') //判斷牌面點數是否為10
            {
                for(int k = 0; k < 4;k++) //判斷花色
                {
                    if(set[i][2] == Suit[k]) //判斷陣列第二個字元是否等於當前花色
                    {
                        set_int[i] = 10 * 10 + k ; //將牌面轉換為整數
                    }
                }
            }
        }
    
        if(set_int[i] == 0) //判斷是否缺少牌面數字轉換
        {
            printf("Error input");
            return 0;
        }
        else
        {
            for(int j = 0; j < i; j++) //判斷當前牌面與其他牌面對應數字是否相同，若相同表示有重複發牌
            {
                if(set_int[i] == set_int[j])
                {
                    is_Duplicate = true;
                }
            }
        }
    
    }
    if(is_Duplicate == true) //判斷是否重複發牌
    {
        printf("Duplicate deal");
        return 0;
    }
    // 把set_int分成兩個字串set_1_int、set_2_int                    
    for(int i = 0; i < 10; i++)
    {
        if(i < 5) //將前五張牌轉換後的整數存進set_1_int，作為第一組牌
        {
            set_1_int[i] = set_int[i];
        }
        else //將後五張牌轉換後的整數set_2_int，作為第二組牌
        {
            set_2_int[i-5] = set_int[i];
        }
    }
    // 用泡泡排序法把set_1_int、set_2_int由小到大排序
    int temp;
    for (int i = 0; i < 4; i++)   //循環N-1次
    {      
        for (int j = 0; j < 4 - i; j++) //每次循環要比較的次數
        { 
            if (set_1_int[j] > set_1_int[j + 1])       //比大小後交換
            {
                temp = set_1_int[j];
                set_1_int[j] = set_1_int[j + 1];
                set_1_int[j + 1] = temp;
            }
            if (set_2_int[j] > set_2_int[j + 1])       //比大小後交換
            {
                temp = set_2_int[j];
                set_2_int[j] = set_2_int[j + 1];
                set_2_int[j + 1] = temp;
            }
        }
    }
    // 把set_1_int、set_2_int丟到card_type，取得各自的最大牌型編號
    type1 = card_type(set_1_int);
    type2 = card_type(set_2_int);
    
    // 比較哪個牌型較大，輸出最大牌型編號
    if(type1 > type2)
    {
        printf("%d",type1);
    }
    else
    {
        printf("%d",type2);
    }

    return 0;
}

int card_type(int arr[])
{
    int set[5]; // 儲存傳入的陣列
    bool is_type[10] = {false}; // 牌組是否形成牌型
    int same_num[4] = {0}; // 從index後面算有幾張是相同的數字

    is_type[1] = true; // 無牌型為散牌
    
    for(int i = 0; i < 5; i++)
    {
        set[i] = arr[i];
    }
    // 判斷是否為 順子(5)
    for(int i = 0; i < 4; i++)
    {
        //分別判斷是否有一般的順子或有分段的順子
        if( (set[i] / 10 + 1) != (set[i+1] / 10) && (set[i] / 10 + 9) != (set[i+1] / 10) ) 
        {
            is_type[5] = false;
            break;
        }
        is_type[5] = true;
    }

    // 判斷是否為 同花(6)
    for(int i = 0; i < 4; i++)
    {           
        //取餘得到兩張牌的花色
        int r1 = set[i] % 10;
        int r2 = set[i+1] % 10;
        if( r1 != r2) //判斷前一張牌的花色是否與後一張牌的花色不同
        {
            is_type[6] = false;
            break;
        }
        is_type[6] = true;
    }
    // 判斷是否為 同花順(9) = 同花(6) + 順子(5)
    if(is_type[5] == true && is_type[6] == true)
    {
        return 9;
    }
    // 計算牌組中有多少張點數一樣的牌, 例如: 2D 2H 5C 5H 8D, same_num[] = {1,0,1,0}
    for(int i=0;i<4;i++) //判斷是否有重複點數 ( 4 + 3 + 2 + 1 ) 次，因為比過的不用重複比
    {
        for(int j = i + 1; j <= 4; j++)
        {
            if(set[i] / 10 == set[j] / 10) //判斷目前指定牌的數字是否與後面其他張牌的點數相同
            {
                same_num[i]++;
            }
        }
        i += same_num[i]; //i = i + same_num[i];
    }

    // 根據same_num可以判斷是否為四條(8)、三條(4)、兩對(3)、一對(2), 若是四條直接回傳 4
    int pair = 0; // Pair的數量

    for (int i = 0; i < 4; i++)
    {
        if(same_num[i] > 0)
        {
            pair++;
            if(same_num[i] == 3) //與其他 3 張牌重複，確定是四條(8)，回傳牌組編號
            {
                return 8;
            }
            else if(same_num[i] == 2) //判斷是否為三條(4)
            {
                is_type[4] = true;
            }
            else if(same_num[i] == 1) //判斷是否為一對(2)
            {
                is_type[2] = true;
            }
        }
    }
    // 判斷是否為兩對(3)
    if(pair == 2)
    {
        is_type[3] = true;
    }

    // 判斷是否為 葫蘆(7) = 三條(4) + 一對(2)
    // 判斷是否為 葫蘆(7) = 三條(4) + 一對(2), , 若是直接回傳7
    if(is_type[4] == true && is_type[2] == true)
    {
        return 7;
    }

    // 若是牌型 7、8、9 前面已return，且要輸出最大牌型，所以從牌型6開始由大到小檢查是否符合
    for(int i = 6; i > 0; i--)
    {
        if(is_type[i] == true)
        {
            return i;
        }
    }
}  