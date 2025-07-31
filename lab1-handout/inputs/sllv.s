.text

main:
   li $t0,-256
   li $t1,0xc5

   sllv $t8,$t0,$t1

   j end

end:
   li $v0,10
   syscall
