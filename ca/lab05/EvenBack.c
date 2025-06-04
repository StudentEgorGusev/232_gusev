        .data
arr:    .space  8000

        .text
        .globl  main
main:
        li      a7,5
        ecall
        mv      s0,a0
        la      s3,arr
        mv      s2,s3
        li      s1,0

read_loop:
        beqz    s0,after_read
        li      a7,5
        ecall
        mv      t0,a0
        andi    t1,t0,1
        bnez    t1,skip_save
        sw      t0,0(s2)
        addi    s2,s2,4
        addi    s1,s1,1
skip_save:
        addi    s0,s0,-1
        j       read_loop

after_read:
        beqz    s1,only_nl
        addi    t0,s1,-1
        slli    t0,t0,2
        add     s2,s3,t0

print_loop:
        lw      a0,0(s2)
        li      a7,1
        ecall
        li      a0,10
        li      a7,11
        ecall
        addi    s2,s2,-4
        addi    s1,s1,-1
        bnez    s1,print_loop
        j       exit_prog

only_nl:
        li      a0,10
        li      a7,11
        ecall

exit_prog:
        li      a7,10
        ecall
