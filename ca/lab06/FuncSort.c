        .data
arr:    .space  4000            

        .text
        .globl  main

main:
        li      a7,5
        ecall
        mv      s0,a0           

        la      s1,arr         
        mv      t0,zero         
read_loop:
        beq     t0,s0,call_sort
        li      a7,5
        ecall
        sw      a0,0(s1)
        addi    s1,s1,4
        addi    t0,t0,1
        j       read_loop

call_sort:
        la      a0,arr
        slli    t1,s0,2
        addi    t1,t1,-4
        la      a1,arr
        add     a1,a1,t1        
        jal     ra,sort

print_loop:
        li      t0,0
        la      s1,arr
print_next:
        beq     t0,s0,print_nl
        lw      a0,0(s1)
        li      a7,1
        ecall
        addi    t0,t0,1
        addi    s1,s1,4
        beq     t0,s0,print_next_nospace
        li      a0,32
        li      a7,11
        ecall
print_next_nospace:
        j       print_next

print_nl:
        li      a0,10
        li      a7,11
        ecall
        li      a7,10
        ecall

sort:                           
        addi    sp,sp,-16
        sw      ra,12(sp)
        sw      s2,8(sp)
        sw      s3,4(sp)
        sw      s4,0(sp)

        mv      s2,a0          
        mv      s3,a1          
outer:
        bge     s3,s2,outer_ok
        j       done
outer_ok:
        mv      t0,s2           
        li      s4,0            
inner:
        addi    t1,t0,4
        bgt     t1,s3,after_inner
        lw      t2,0(t0)
        lw      t3,0(t1)
        ble     t2,t3,no_swap
        sw      t3,0(t0)
        sw      t2,0(t1)
        li      s4,1
no_swap:
        mv      t0,t1
        j       inner
after_inner:
        beqz    s4,done
        addi    s3,s3,-4
        blt     s2,s3,outer
done:
        lw      ra,12(sp)
        lw      s2,8(sp)
        lw      s3,4(sp)
        lw      s4,0(sp)
        addi    sp,sp,16
        ret
