        .text
        .globl main
main:
        li      a7,5
        ecall
        mv      t0,a0
        blt     t0,x0,neg
pos:
        li      t1,0
        beqz    t0,print
        li      t3,10
loop:
        rem     t2,t0,t3
        add     t1,t1,t2
        div     t0,t0,t3
        bnez    t0,loop
print:
        mv      a0,t1
        li      a7,1
        ecall
        li      a0,10
        li      a7,11
        ecall
        li      a7,10
        ecall
neg:
        sub     t0,x0,t0
        j       pos
