#на всякий случай отмечу, что комменты здесь мои личные, не гптшные. когда приступал к выполнению домашек и они еще были простенькие, хотел сделать всё красиво, оформить, но с ростом сложности акосных и скоплением других задач, было решено это опустить. т.к. сейчас просто заливаю код сданных ранее задач с ejudge, решил это упомянуть - примечание редактора.
.text
        .globl  main

main:
        li      a7, 5          
        ecall
        mv      s0, a0         

        li      a7, 5
        ecall
        mv      s1, a0         

# ---------- 1) (x + 5) - (y - 7) ------------------------------
        mv      t0, s0
        addi    t0, t0, 5      
        mv      t1, s1
        addi    t1, t1, -7     
        sub     a0, t0, t1     
        jal     ra, print_int_nl

# ---------- 2) 2 * x * x - 3 * y + 4 --------------------------
        mul     t0, s0, s0     
        add     t0, t0, t0     
        li      t2, 3
        mul     t1, s1, t2     
        sub     t0, t0, t1
        addi    a0, t0, 4      
        jal     ra, print_int_nl

# ---------- 3) (x + 5) / y + 10 / (y - 1) --------------------
        addi    t0, s0, 5      
        div     t0, t0, s1     
        addi    t1, s1, -1    
        li      t2, 10
        div     t1, t2, t1     
        add     a0, t0, t1
        jal     ra, print_int_nl

# ---------- 4) (x / y) * y + x % y ---------------------------
        div     t0, s0, s1     
        mul     t0, t0, s1     
        rem     t1, s0, s1     
        add     a0, t0, t1
        jal     ra, print_int_nl

# ---------- 5) x > y ? 1 : 0 ---------------------------------
        slt     a0, s1, s0     
        jal     ra, print_int_nl

        # ---- завершение ----
        li      a7, 10         
        ecall

print_int_nl:
        addi    sp, sp, -8
        sw      ra, 4(sp)

        li      a7, 1          
        ecall
        li      a0, 10         
        li      a7, 11         
        ecall

        lw      ra, 4(sp)
        addi    sp, sp, 8
        jr      ra
