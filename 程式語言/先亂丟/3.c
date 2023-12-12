#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    char Dividend[40], Divisor[40],Divisor_copy[40],Quotient[40];
    int a = 0, k = 0, a_k, a_k_copy;
    int  index = 0, count = 0;
    int mode = 0;
    bool start = false;
    bool signed_1 = false, signed_2 = false, signed_Q = false; 
    bool is_zero = true;

    scanf("%s", Dividend);
    scanf("%s", Divisor);

    a = strlen(Dividend) - 1;
    k = strlen(Divisor) - 1;

    if(Dividend[0] == '-')
    {
        signed_1 = true;

        for(int i = 0; i < a; i++)
        {
            Dividend[i] = Dividend[i + 1];
        }

        Dividend[a] = '\0';
        a--;
    }
    
    if(Divisor[0] == '-')
    {
        signed_2 = true;

        for(int i = 0; i < k; i++)
        {
            Divisor[i] = Divisor[i + 1];
        }

        Divisor[k] = '\0';
        k--;
    }

    if((signed_1 == true && signed_2 == false) || (signed_1 == false && signed_2 == true))
        signed_Q = true;

    a_k = a - k;
    a_k_copy = a_k;

    for(int i = a; i >= a-k ; i--)
    {
        Divisor_copy[i] = Divisor[i-(a-k)];
    }

    for(int i = a - k - 1; i >= 0 ; i--)
    {
        Divisor_copy[i] = '0';
    }

    for(int i = k + 1; i <= a; i++)
    {
        Divisor[i] = '0';
    }

    while (1)
    {
        for(int i = 0; i <= a; i++)
        {
            if(Dividend[i] > Divisor[i])
            {
                mode = 1; 
                break;
            }

            else if(Dividend[i] < Divisor[i])
            {
                mode = 2;
                break;
            }

            else{}
        }

        if(mode == 0)//mode 0
        {
            count++;
            
            for(int i = 0; i < a_k;i++)
            {
                count = count * 10;
            }

            if(signed_Q == true)
                printf("-");
            
            printf("%d", count);
            printf("\n0");

            return 0;
        }

        else if(mode == 1)//mode 1
        {
            index = a;
            while (1)
            {
                if(Dividend[index] >= Divisor[index])
                {
                    Dividend[index] = Dividend[index] - Divisor[index] +'0';
                }

                else
                {
                    int borrow = index - 1;
                    while(1)
                    {
                        if(Dividend[borrow] > 0)
                        {
                            Dividend[borrow] = Dividend[borrow] - 1 ;

                            for(int i = borrow + 1; i < index; i++)
                            {
                                Dividend[i] = '9';
                            }

                            Dividend[index] = 10 +'0' - Divisor[index] + Dividend[index];
                            break;
                        }
                        else
                            borrow--;
                    }
                }
                index--;
        
                if(index < 0)
                    break;
            }
            count++;
        }

        else//mode 2
        {
            if(strncmp(Divisor_copy, Divisor, a + 1) == 0)
            {
                Quotient[a_k] = count + '0';
                break;
            }
            else
            {
                for(int i = a; i > 0; i--)
                {
                    Divisor[i] = Divisor[i - 1];
                }
                Divisor[0] = '0';
                Quotient[a_k] = count + '0';
                count = 0;
                a_k--;
            }
        }
    }

    if((signed_1 == true && signed_2 == true) || (signed_1 == true && signed_2 == false))
    {   
        for(int i = 0; i <= a; i++)
        {
            if(Dividend[i] != '0' )
            {
                is_zero = false;
                break;
            }
        }

        if(is_zero == false)
        {
            Quotient[0] += 1;
            index = a;
            while (1)
            {
                if(Divisor[index] >= Dividend[index])
                {
                    Dividend[index] = Divisor[index] - Dividend[index] +'0';
                }

                else
                {
                    int borrow = index-1;
                    while(1)
                    {
                        if(Divisor[borrow] > 0)
                        {
                            Divisor[borrow] = Divisor[borrow] - 1 ;
                            for(int i = borrow + 1; i < index; i++)
                            {
                                Divisor[i] = '9';
                            }
                            Dividend[index] = 10 +'0' - Dividend[index] + Divisor[index];
                            break;
                            }
                        else
                            borrow--;
                    }
                }
                index--;
    
                if(index < 0)
                    break;
            }
        }
    }

    if(signed_Q == true)
        printf("-");
 
    for(int i = a_k_copy; i >= 0; i--)
    {
        if(Quotient[i] != '0' )
            start = true;
 
        if(start == true)
            printf("%c",Quotient[i]);
    }
    printf("\n");
 
    start = false;
 
    for(int i = 0; i <= a; i++)
    {
        if(Dividend[i] != '0')
            start = true;
 
        if(start == true)
            printf("%c",Dividend[i]);
    }

    if(start == false)
        printf("0");
 
    return 0;
}