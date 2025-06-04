        .text
        .globl  main

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

        li      a7,5
        ecall
        mv      s3,a0          

        add     a0,s0,s2       
        li      a7,1
        ecall
        li      a0,10
        li      a7,11
        ecall

        add     a0,s1,s3       
        li      a7,1
        ecall
        li      a0,10
        li      a7,11
        ecall

        li      a7,10
        ecall
