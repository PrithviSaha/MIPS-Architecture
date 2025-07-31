.text

main:
        lui $t0, 0xb104
	ori $t0, $t0, 0xeff1
        li $t1, -5000000

        mult $t0,$t1
        j end

end : addiu $v0,$zero,10
      syscall

