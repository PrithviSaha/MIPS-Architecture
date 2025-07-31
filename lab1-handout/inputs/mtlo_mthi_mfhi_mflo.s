         .text
__start:li $t0, -1             # Load -1 (0xFFFFFFFF)
        li $t1, -2             # Load -2 (0xFFFFFFFE)

        mthi $t0               # HI = -1
        mtlo $t1               # LO = -2

        mfhi $t2               # $t2 = -1
        mflo $t3               # $t3 = -2
        li      $v0, 10
        syscall

