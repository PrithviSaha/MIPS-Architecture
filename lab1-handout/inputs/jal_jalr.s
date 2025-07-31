.text

__main:
    j label1

label1:
    li $t0, 1
    jal label2

label2:
    li $t1, 2
    jal label3

label3:
    li $t2, 3
    la $t4, after_jalr
    jalr $t4

after_jalr:
    li $t3, 4
    li $v0, 10
    syscall

