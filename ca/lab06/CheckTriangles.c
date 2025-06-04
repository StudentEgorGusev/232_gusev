        .text
        .globl  main

main:
read_loop:
        li      a7,5
        ecall
        mv      s0,a0          # a
        li      a7,5
        ecall
        mv      s1,a0          # b
        li      a7,5
        ecall
        mv      s2,a0          # c

        mv      a0,s0
        mv      a1,s1
        mv      a2,s2
        jal     ra,check

        beqz    a0,exit        
        addi    t0,a0,-1
        beqz    t0,print_Y     

print_N:
        li      a0,'N'
        li      a7,11
        ecall
        li      a0,10
        li      a7,11
        ecall
        j       read_loop

print_Y:
        li      a0,'Y'
        li      a7,11
        ecall
        li      a0,10
        li      a7,11
        ecall
        j       read_loop

exit:
        li      a7,10
        ecall


check:
        or      t0,a0,a1
        or      t0,t0,a2
        beqz    t0,ret0        
        add     t1,a1,a2       
        bgt     a0,t1,ret2
        add     t1,a0,a2       
        bgt     a1,t1,ret2
        add     t1,a0,a1       
        bgt     a2,t1,ret2
        li      a0,1
        jr      ra
ret2:   li      a0,2
        jr      ra
ret0:   li      a0,0
        jr      ra
