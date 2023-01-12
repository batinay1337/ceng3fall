#                        20070001051
.data
.text
     main:
       addi $t1, $zero, 7 	# a=7
       addi $t2, $zero, 15 	# b=15

       jal recfunc

       #########################print {

       addi $v0, $zero, 1
       add $a0, $t0, $zero #print t0
       syscall
       
	###############}
	
	
       
       li $v0, 10 #exit
       syscall

         recfunc:
              subu $sp, $sp, 8
              sw $ra,($sp) #call value
              sw $s0,4($sp) #sum 

              #base case
              bgt $t1,$t2, recurDone #when 15<16 go to recurDone


              add $s0, $s0, $t1 #add t1(7+i) to "s0" stack pointer

              sw $s0,4($sp)
              addi $t1, $t1, 1
              
              
		lw $s5, 4($sp)#in the end; 4. stack point we have 99, so load to s5
              
              addi $t0, $s5, 0 #to return value = add s5 to t0.
              jal recfunc
		
              recurDone:
                         lw $ra, ($sp) # when we are done here, load to based ra
                         lw $s0, 4($sp)# when we are done here, load to last number in 4. stack point
                         addu $sp, $sp, 8 # when we are done here, gonna release stack
                         jr $ra