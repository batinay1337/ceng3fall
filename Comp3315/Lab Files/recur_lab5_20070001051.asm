#                        20070001051

     main:
       li $a0, 10 	# a = 10
       li $t0, 0 	#  result
	li $s2, 1    
       jal doublefactorial #n!!
	add $t0, $v0, $zero
       #########################print {

       addi $v0, $zero, 1
       add $a0, $t0, $zero #print t0
       syscall
       
	###############}
	
	
       
       li $v0, 10 #exit
       syscall

         doublefactorial:
              subu $sp, $sp, 8
              sw $ra,($sp) #call value
              sw $s0,4($sp) #sum 

              #base case
              li $v0 , 1
              #beq $a0,0, factorialdone 
              #beq $a0,1, factorialdone
              
              ble $a0, $s2, factorialdone
              
              
              move $s0, $a0
              sub $a0, $a0, 2
              

              
             
              jal doublefactorial
	      mul $v0, $s0, $v0
	
              factorialdone:
                         lw $ra, ($sp) # when we are done here, load to based ra
                         lw $s0, 4($sp)# when we are done here, load to last number in 4. stack point
                         addu $sp, $sp, 8 # when we are done here, gonna release stack
                         jr $ra
