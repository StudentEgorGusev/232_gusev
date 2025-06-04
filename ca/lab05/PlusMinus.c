        .text
        .globl  main
main:
        li      a7,5
        ecall
        mv      s0,a0          
        li      t0,0           
        li      t1,0           
loop:
        beq     t0,s0,done
        li      a7,5
        ecall
        mv      t2,a0
        andi    t3,t0,1
        beqz    t3,plus
        sub     t1,t1,t2
        j       nxt
plus:
        add     t1,t1,t2
nxt:
        addi    t0,t0,1
        j       loop
done:
        mv      a0,t1
        li      a7,1
        ecall
        li      a0,10
        li      a7,11
        ecall
        li      a7,10
        ecall
