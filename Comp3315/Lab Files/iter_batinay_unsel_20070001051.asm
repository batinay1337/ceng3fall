

.globl main
main:
	li 		$t0,0 #int sum=0;
	li 		$t1,7 # int a=7;
	li 		$t2,15 #int b=15;S
	li 		$t4, 0 #int summ=0;

	jal iterFunc     #call addFunc.
	add 		$t4,$0,$v0  #ifunctiondan gelen değeri sum içine atıyorum.

	addi 		$v0,$0,1   #integer yazd?rma
	add 		$a0,$0,$t4
	syscall
	
	li 	$v0, 10              #run and exit
	syscall 

iterFunc: #inner function

	loop:
		ble 		$t2,$t1,end
		add 		$t0,$t0,$t1
		addi	 	$t1,$t1,1
		j loop

	end:
		add 		$t0, $t0, $t2
		add 		$v0,$0,$t0
		jr 		$ra
