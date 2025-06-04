        .text
        .globl  main
main:
        li      a7,5
        ecall
        mv      s0,a0
        li      a7,5
        ecall
        mv      s1,a0

        li      t0,-1
        slli    t0,t0,2
        and     a0,s0,t0
        jal     ra,print_int_nl

        li      t0,-1
        srli    t0,t0,30
        or      a0,s0,t0
        jal     ra,print_int_nl

        li      t0,1
        sll     t0,t0,s1
        or      a0,s0,t0
        jal     ra,print_int_nl

        li      t0,1
        sll     t0,t0,s1
        not     t0,t0
        and     a0,s0,t0
        jal     ra,print_int_nl

        addi    t1,s1,3
        slt     t0,s0,t1
        slt     t2,t1,s0
        or      a0,t0,t2
        jal     ra,print_int_nl

        li      t2,-5
        slt     t0,t2,s0
        slti    t1,s1,5
        and     a0,t0,t1
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
