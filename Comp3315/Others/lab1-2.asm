.data 
array: .word 9,3,4,8

.text

 .globl main
 
	main:

	addi $v0, $0, 5
	syscall
	add $t0, $0, $v0
	
	la $t1, array
	
	addi $s7, $0, 4
	multu $t0, $s7
	mflo $s2
	add $t1, $t1, $s2
	
	
	lw $s3, 0($t1)
	
	
	add $a0, $0, $s3 
	addi $v0, $0, 1
        syscall
	
	
	
	
