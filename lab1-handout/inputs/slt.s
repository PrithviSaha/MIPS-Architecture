.text

main:
    li $t0,0x1f43
    li $t1,0x5612

    slt $v0,$t0,$t1

    beq $v0,1,xorOperationLabel

    j andOperationLabel


xorOperationLabel:
   nop
   xor $t8,$t0,$t1
   j end


andOperationLabel:
   nop
   and $t8,$t0,$t1
   j end


end:
   li $v0,10
   syscall

