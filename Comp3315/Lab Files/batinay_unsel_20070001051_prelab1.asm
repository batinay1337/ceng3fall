.data
array: .word 8, 1, 4, 5, 6, 3, 2, 9, 7 
.text
.globl main 

main:
la	$t0, array
la	$t2, 0         #int i   
la	$t3, 0         #int result

loop:
slti  $t7, $t2, 10 #if $t2+10 >= $t7, then loop over.
beq   $t7, $0,  end
lw    $t4, ($t0)
add $t3, $t3, $t4
addi	$t0, $t0, 4
addi $t2, $t2, 1
j loop
end:


#adding integers
add	$a0, $0, $t3
li	  $v0, 1
syscall
