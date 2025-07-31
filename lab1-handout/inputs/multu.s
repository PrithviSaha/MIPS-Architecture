.text

main:
        addu $t0, $zero, 0xb104eff1
        addu $t1, $zero,  -5000000

        multu $t0,$t1
        j end

end : addiu $v0,$zero,10
      syscall

