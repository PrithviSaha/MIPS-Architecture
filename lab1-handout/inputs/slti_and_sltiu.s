	.text
__start:  li $t0, -10
          li $t1, 20
          slti $t2, $t0, 15

          li $t3, -10
          li $t4, 20
          sltiu $t5, $t4, 25

          li $v0,10
          syscall

