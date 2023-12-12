         BR      main
output:  .WORD   0x0000
count1:  .WORD   0x0000      ; count = 0 
result:  .WORD   0x0000
count2:  .WORD   0x0000
k1:      .WORD   0x0000
k2:      .WORD   0x0000
a:       .BLOCK  2           ; a is 2byte
b:       .BLOCK  2           ; b is 2byte
;DECI a, d input a
;DECO a, d output a
main:    DECI    a,d         ;input a
         DECI    b,d         ;input b
         LDWA    0,i
         STWA    count1,d      ;count1 = 0 
         LDWA    1,i;
         STWA    output,d    ;output = 1
;output = output*a
loop:    LDWA    output,d
         STWA    k1,d
         LDWA    a,d
         STWA    k2,d
         BR      mu
check:   LDWA    result,d
         STWA    output,d
         ;DECO    output,d
         LDWA    count1,d
         ADDA    1,i
         STWA    count1,d
         CPWA    b,d         ;if(b==count1) finish the program
         BREQ    finish
         BR      loop        ;else output = output * a

;int mu(k1, k2)
;result = k1*k2 = k1 + k1 + k1 + .... add k2 times
mu:      LDWA    0,i
         STWA    result,d
         LDWA    0,i
         STWA    count2,d
         BR      mu_loop

mu_loop: LDWA    result,d
         ADDA    k1,d
         STWA    result,d
         LDWA    count2,d
         ADDA    1,i
         STWA    count2,d
         CPWA    k2,d
         BREQ    mu_over
         BR      mu_loop
mu_over: BR      check

finish:  DECO    output,d
         STOP
         .END

         