.globl main
main:
      li $a0, 10 # int a=10;
      li $t0, 0 #int sum=0;
      li $s2, 2
      jal iterFactorial
      addi $t0, $v1, 0 #t0 = result
      
      
      li $v0, 1
      addi $a0, $t0, 0 #CALL RESULT
      syscall
      
      
      li $v0, 10 #exit
      syscall
     
  
      iterFactorial:    
       addi $t2, $a0, 0 #restoreing value to t1
       
       # beq $t1, 1 
       addi $v1, $a0, 0 #return
            
            loop:
            
               ble $t2, $s2, end # if i <= 2
               
               addi $t2, $t2, -2 #    i -=  2
               mul $v1, $v1, $t2 #result *= i
               
               j loop
                    
         end:
         
         jr $ra