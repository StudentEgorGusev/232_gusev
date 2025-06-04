        .data
buf:    .space  8000

        .text
        .globl  main

main:
        li      a7,5
        ecall
        mv      s0,a0          
        la      s1,buf         
        li      s2,0           

read:
        beqz    s0,finish
        li      a7,5
        ecall
        mv      t0,a0          

        li      t1,0           
        li      t2,0           
chk:
        beq     t1,s2,store
        slli    t3,t1,2
        add     t3,t3,s1
        lw      t4,0(t3)
        beq     t4,t0,dup
        addi    t1,t1,1
        j       chk
dup:
        li      t2,1
store:
        bnez    t2,skip
        slli    t3,s2,2
        add     t3,t3,s1
        sw      t0,0(t3)
        addi    s2,s2,1
        mv      a0,t0
        li      a7,1
        ecall
        li      a0,10
        li      a7,11
        ecall
skip:
        addi    s0,s0,-1
        j       read

finish:
        bnez    s2,exit
        li      a0,10
        li      a7,11
        ecall
exit:
        li      a7,10
        ecall
