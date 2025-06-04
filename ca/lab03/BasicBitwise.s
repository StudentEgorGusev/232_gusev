        .text
        .globl  main
main:
        li      a7,5
        ecall
        mv      s0,a0
        li      a7,5
        ecall
        mv      s1,a0

        srli    t0,s0,2
        addi    t1,s1,-1
        slli    t1,t1,3
        add     a0,t0,t1
        jal     ra,print_int_nl

        sll     t0,s0,s1
        addi    a0,t0,-10
        jal     ra,print_int_nl

        sra     t0,s0,s1
        addi    a0,t0,10
        jal     ra,print_int_nl

        slli    t0,s0,2
        sub     t0,t0,s1
        addi    t0,t0,5
        srai    a0,t0,1
        jal     ra,print_int_nl

        slli    t0,s0,2
        slli    t1,s0,1
        add     t0,t0,t1
        slli    t2,s1,1
        add     t2,t2,s1
        sub     a0,t0,t2
        jal     ra,print_int_nl

        li      a7,10
        ecall

print_int_nl:
        addi    sp,sp,-8
        sw      ra,4(sp)
        li      a7,1
        ecall
        li      a0,10
        li      a7,11
        ecall
        lw      ra,4(sp)
        addi    sp,sp,8
        jr      ra
