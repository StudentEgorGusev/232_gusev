        .text
        .globl main

main:
        li      a7,5
        ecall
        mv      s0,a0
        li      a7,5
        ecall
        mv      s1,a0
        addi    s2,s1,-1

        mv      a0,s0
        li      a1,'+'
        li      a2,'-'
        jal     ra,printline

        li      t1,0
row_loop:
        bge     t1,s1,finish

        mv      a0,s0
        li      a1,'|'
        li      a2,' '
        jal     ra,printline

        beq     t1,s2,last_border

        mv      a0,s0
        li      a1,'+'
        li      a2,'-'
        jal     ra,printline
        addi    t1,t1,1
        j       row_loop

last_border:
        mv      a0,s0
        li      a1,'+'
        li      a2,'-'
        jal     ra,printline_nonl
        addi    t1,t1,1
        j       row_loop

finish:
        li      a7,10
        ecall

printline:
        mv      t0,a0
pl_loop:
        beqz    t0,pl_end
        mv      a0,a1
        li      a7,11
        ecall
        mv      a0,a2
        li      a7,11
        ecall
        addi    t0,t0,-1
        j       pl_loop
pl_end:
        mv      a0,a1
        li      a7,11
        ecall
        li      a0,10
        li      a7,11
        ecall
        jr      ra

printline_nonl:
        mv      t0,a0
pnl_loop:
        beqz    t0,pnl_end
        mv      a0,a1
        li      a7,11
        ecall
        mv      a0,a2
        li      a7,11
        ecall
        addi    t0,t0,-1
        j       pnl_loop
pnl_end:
        mv      a0,a1
        li      a7,11
        ecall
        jr      ra
