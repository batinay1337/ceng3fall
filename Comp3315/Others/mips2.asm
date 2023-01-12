
.text
.globl main
        
main:
		#MARK: Put the v0 to t0
        	addi $v0, $zero ,5
        	syscall
        	add $t0,$0, $v0
        	
        	addi $v0, $zero,5
        	syscall
        	add $t1, $zero, $v0
        	
        	
        	mult $t0, $t1
        	mflo $t2
        	add $a0, $0, $t2 
        	addi $v0, $0, 1
        	syscall
        	
        	
        	
        
        