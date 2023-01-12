.data
array: .word 7, -4, 5, 0, 8, -2, 1, -3
.text
.globl main 

main:
la	$t0, array
li	$t2, 0         #int i   
li	$t3, 0         #int result

loop:
slti $t7, $t2, 8
beq   $t7, $0,  end
lw    $t4, ($t0)

slt  $s1,$0,$t4      # $s0 >= $s1 as (s0<s1) == 0
beq  $s1,$zero,notpositive     # if $s0 <  $s1, goes to notpositive
add $t3, $t3, $t4

notpositive:
addi	$t0, $t0, 4  #->next
addi $t2, $t2, 1
j loop
end:


#adding integers
add	$a0, $0, $t3
li	  $v0, 1
syscall
