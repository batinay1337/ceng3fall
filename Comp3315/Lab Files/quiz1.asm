.data
arr: .word 9,-1,4,-2,8,-6
.text
.globl main

main:
addi $t2,$0,0 #i=0
addi $t3,$0,6 #n
la $t7,arr #arr atadik
la $s5,arr # yazdirmak için arr


loop : 
beq $t2,$t3,end #i < 9
sll $t4,$t2,2 #t4=t2*4=i*4
add $t5,$t7,$t4 #adress(arr)+i*4
lw $s0,0($t7) #lw




jal func #call func


add $t1,$0,$v0


sw $v0,0($t5)               #array[i] = func(array[i]);

addi $v0, $0, 1
add $a0, $t1, $0      #integer yazdirma ve bitirme
syscall



addi $t2,$t2,1 #i++




j loop


end:

li $v0, 10
syscall


func:

#mark: check if negative
li $t4, 3 # t3 = 3
bgt $s0, $0, pozitif

mul $s0, $s0, $t3


pozitif:

addi $t0, $zero, 2    # Store 2 in $t0
div $t0, $s0, $t0     # Divide input by 2
mfhi $s1              # Save remainder in $s1


bne $s1, $0, cift

add $s3, $0, $s0
sll $s0, $s3, 1




cift:

add $v0,$0,$s3


jr $ra #return