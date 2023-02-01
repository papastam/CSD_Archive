        # ECALL x17:mode x10:args
        #x5:arr pointer
        #x6:i
        #x8=8
        #x9 x11 temp reg for the multiplication

        .data
        str1: .asciz "\nPlease enter 8 integers:"
        str2: .asciz "\n------------------------\n\n"
        strsp: .asciz " "

	.align 2
	arr:  .space 32

        .text

main:
	addi x8,x0,8      #x8=n ==8
	la x5, arr        #x5=arr
	addi x6,x0,0      #x6=i ==0

	addi x17, x0, 4   #ecall=printString
	la x10, str1      #load the str1 on the x10 register
	ecall             #print str1

loop:
	addi x17,x0,5     #ecall=readInt
	ecall             #read the corresponding number
	sw x10,(x5)       #save it to the corresponding adress

	addi x5,x5,4      #advance the x5 pointer to the next array adress
	addi x6,x6,1      #i=i+1
	bne x6,x8,loop    #go to loop if i!=8
	#END OF THE (loop)

	addi x17,x0,4     #ecall=printString
	la x10,str2       #load str2 on the x10 register
	ecall             #print the brak

	la x5, arr        #x5=arr
	addi x5,x5,28     #set the array pointer to the end of the array
	addi x6,x0,0      #i=0

prnt:
	lw x9,(x5)	  #x9=arr[i]
	add x10,x9,x9     #x10=2*x9
	add x10,x10,x9    #x10=3*x9
	add x10,x10,x10   #x10=2*x10

	addi x17,x0,1     #ecall=printInt
	ecall

	addi x17,x0,4     #ecall=printString
	la x10,strsp      #x10=" "
	ecall             #print " "

	addi x5,x5,-4     #advance the array pointer to the previous array adress
	addi x6,x6,1      #i=i+1
	bne x6,x8,prnt    #go to prnt if i!=8

	j main            #restart the program

