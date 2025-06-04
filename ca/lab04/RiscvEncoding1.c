.text
start:
    lui     s0, 0x10010        
    xori    s1, zero, 12       
    sw      s1, 0(s0)          

    lui     t0, 0x30000        
    addi    t1, zero, 3        
    srli    t0, t0, 16         

    lw      s1, 0(s0)          
    sll     t1, t1, s1         

    beq     t0, t1, ok         
    jal     zero, done         

ok:
    auipc   t2, 0              
    addi    t2, t2, -4         
    jalr    zero, 0(t2)       

done:
    ori     a7, zero, 10      
    ecall
