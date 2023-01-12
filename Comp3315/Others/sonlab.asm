.data
.text

main:
addi $t1, $0, 14
addi $t2, $0, 26

and $t3, $t1, $t2
or $t4, $t1, $t2
add $t5, $t1, $t2
sub $t6, $t1, $t2
xor $t7, $t1, $t2

lui $t9, 0x1001
sw $t0, 0($t9)
sw $t1, 4($t9)
sw $t2, 8($t9)
sw $t3, 12($t9)
sw $t4, 16($t9)
sw $t5, 20($t9)
sw $t6, 24($t9)
sw $t7, 28($t9)
