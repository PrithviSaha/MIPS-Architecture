
.text


main:
   addiu $t0,$zero,0x1872

   and $t8,$t0,0x1234
   j end

end:
   addiu $v0,$zero,10
   syscall

