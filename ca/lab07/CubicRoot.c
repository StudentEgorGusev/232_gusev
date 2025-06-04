        .data
oneD:     .double 1.0
threeD:   .double 3.0
nl:       .byte   10

        .text
        .globl  main

main:
        li      a7,7                
        ecall                       
        fsgnj.d ft0,fa0,fa0         

        li      a7,7
        ecall                       
        fsgnj.d ft1,fa0,fa0         


        feq.d  t0,ft0,ft0           
        flt.d  t0,ft0,ft0           
        flt.d  t0,ft0,ft1           
        fsgnj.d ft2,ft0,ft0         
        flt.d  t0,ft0,ft2           
                                    

        la      t1,oneD
        fld     ft4,0(t1)           
        flt.d   t2,ft2,ft4
        beqz    t2,gt_one
        fmv.d   ft3,ft4             
        j       init_ok
gt_one:
        la      t1,threeD
        fld     ft5,0(t1)           
        fdiv.d  ft3,ft2,ft5         
init_ok:

        li      t3,60               
iter:
        fmul.d  ft6,ft3,ft3         
        fdiv.d  ft7,ft2,ft6         
        fadd.d  ft8,ft3,ft3         
        fadd.d  ft8,ft8,ft7        
        la      t1,threeD
        fld     ft5,0(t1)           
        fdiv.d  ft3,ft8,ft5         

        fmul.d  ft9,ft3,ft3
        fmul.d  ft9,ft9,ft3         
        fsub.d  ft10,ft9,ft2
        fabs.d  ft10,ft10
        fle.d   t4,ft10,ft1
        bnez    t4,done
        addi    t3,t3,-1
        bnez    t3,iter
done:

        beqz    t0,positive
        fneg.d  ft3,ft3
positive:
        fmv.d   fa0,ft3             
        li      a7,3                
        ecall

        lb      a0,nl
        li      a7,11               
        ecall

        li      a7,10               
        ecall
