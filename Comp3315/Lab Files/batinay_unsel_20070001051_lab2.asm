.data
array: .word   3, 5, 8, 7, 2, 9, 12, 4, 15
size: .word   9
.text

main:   
    la $a0, array
    lw $a1, size
    lw $t3, ($a0) # min
    
    loop:
        beq $a1, $zero, end #end when loop over
        lw $t0, ($a0) # load to element to t0 register
        ble  $t3, $t0 notmin # if (min>element) element is not min, so jump to notmin label
        move $t3, $t0 #else change the min value to element
        notmin: #if its not min 
        addi $a1, $a1, -1 #size-1
        addi $a0, $a0, 4
        j loop
   
    end:
    #print
    li $v0, 1
    move $a0, $t3
    syscall 

    # exit
    li $v0, 10
    syscall