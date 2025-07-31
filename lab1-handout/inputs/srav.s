.text

main:
   li $t0,0xf0
   li $t1,0xe5

   srav $v1,$t0,$t1

   j end

end:
   li $v0,10
   syscall

