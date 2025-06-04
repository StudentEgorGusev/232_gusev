        .data
nl:     .byte 10

        .text
        .globl main

main:
        li      a7,5
        ecall
        mv      s0,a0                  

        li      a7,5
        ecall
        mv      s1,a0                  

        li      a7,5
        ecall
        mv      s2,a0                  

        fcvt.d.w ft0,s0
        fcvt.d.w ft1,s1
        fdiv.d   fa0,ft0,ft1           

        mv      a0,s2                  
        jal     ra,round_n             

        li      a7,3                   
        ecall

        lb      a0,nl
        li      a7,11                  
        ecall

        li      a7,10                  
        ecall


round_n:
        mv      t0,a0
        li      t1,1                   
pow_loop:
        beqz    t0,pow_done
        li      t2,10
        mul     t1,t1,t2
        addi    t0,t0,-1
        j       pow_loop
pow_done:
        fcvt.d.w ft2,t1               
        fmul.d   fa0,fa0,ft2          
        fcvt.w.d t2,fa0                
        fcvt.d.w fa0,t2                
        fdiv.d   fa0,fa0,ft2           
        ret
