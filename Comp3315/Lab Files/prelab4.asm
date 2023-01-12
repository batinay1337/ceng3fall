.data
Sz: .word 5
arr1:   .word 5, -1, 4, -3, 0
arr2:   .word 0, 0, 0, 0, 0
result: .asciiz  "result is: "
NL: .asciiz " "

.text

main:
lw $s7, Sz  #s7 = size
move $s1, $zero  
la $s2, arr1
la $s0, arr2
la $s4, arr2   # new arr2 address for print

loop:
bge $s1, $s7, loop_end  # s7 is size, so if i == size, then end the loop

################################/ FOR 
#lw $a0, 0($s2) #a0 = array1 0

lw $t5,0($s2)
jal invert
sw $v0,0($s0)

#################################/


addi $s1, $s1, 1  # for increment i
addi $s2, $s2, 4 #for arr1
addi $s0, $s0, 4 #for arr2
j loop 

loop_end:




####################################
		#TODO: i yi 0 yapman lazım +


add $s1, $0, 0

la $a0, result 
li $v0, 4
syscall
##################################### 	PRINT LOOP
print_loop:
slti $s6,$s1,5
beq $s6, $0, print_loop_end 
################################/ FOR PRINTING NUMBER a0

lw $t9,0($s4)
add $a0,$0,$t9
li $v0, 1
syscall
#################################/

#################################/ FOR SPACE
la $a0, NL 
li $v0, 4
syscall
############################/
addi $s1, $s1, 1 
addi $s4, $s4, 4 
j print_loop 

print_loop_end:

li $v0, 10              # terminate program run and exit
syscall 

invert: #invert function returns v0 

addi $s3,$0,-1
mult $t5,$s3
mflo $v0 # (I JUST FOUND OUT!!!) it must be a v0, another register is not working.
jr $ra