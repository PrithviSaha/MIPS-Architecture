.text

main:
     addi $t1,$zero,20
     addi $t2,$zero,4
     addi $t8,$zero,-11
     bltz $t8,multiplicationOperationLabel
     div $t1,$t2
     j end

multiplicationOperationLabel:
     nop
     add $t3,$t1,$t2
     j end

end:
    addi $v0,$zero,10
    syscall
