#The beq instruction compares the values in registers a1 and a0, and if they are equal, it branches to the subOperationLabel to perform a subtraction. If they are not equal, the program continues with the next instruction to perform an addition.
.text

main:
   addi $a0 ,$zero,1
   addi $a1,$zero,1

   addi $a2,$zero,1000
   addi $a3,$zero,2000

   beq $a0,$a1,subOperationLabel
   add $t0,$a2,$a3
   j end

subOperationLabel :
    nop
    sub $t0,$a2,$a3
    j end

end: addi $v0,$zero,10
     syscall

