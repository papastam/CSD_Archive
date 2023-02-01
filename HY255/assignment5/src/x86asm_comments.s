# -----------------------------------
# Program x86asm.s
# Compute and print the sum 0+...+N
# -----------------------------------

	.section .data	#initializing the default values 
N:	.long 1000	    # 1000 as the ceiling of the addition
S:	.long 0		    # 0 for S
Msg:	.ascii "The sum from 0 to %d is %d\n\0"


	.section .text	# code ssection
.globl main
main:	
	pushl %ebp	    #save the last base pointer
	movl %esp, %ebp	# and copy the base pointer to the stack pointer

 	# initialize
    movl N, %ebx	# copy the address of N to ebx

 	# compute sum
L1:
	addl %ebx, S	# add N to S
	decl %ebx       # decrease N by 1
	cmpl $0, %ebx   # compare N with 0
	jng  L2	    	# if N<=0 jump to L2
    movl $L1, %eax	# save L1's address to %eax
    jmp *%eax   	# and jump to %eax address (L1)

L2:
	# print result
	pushl S	    	# first argument for the print funtion is S
	pushl N	        # second is N
	pushl $Msg  	# and the third is the print string (Msg)
	call printf 	# call the print function
	popl %eax   	# remove Msg arguement
	popl %eax   	# remove N arguement
	popl %eax   	# remove S argument

	# exit
	movl $0, %eax  	# save 0 to %eax
    leave	    	#make %esp same as %ebp
 	ret             #return
