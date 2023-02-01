.data 
	nline: .asciz "\n" 
	inpt_str: .asciz "Insert a integer:"
	search_str: .asciz "Insert a bottom search limit:"
.text 
main:	
	addi s8,zero,1#constant 1
	
	addi a7,zero,4 
	la a0,inpt_str
	ecall#print inpt_str
	
	jal read_int
	
	bge zero,a0,l1_end3#if  a0>0 (branch if a0<=0)
	add t0,zero,a0 #temporary save the input int
	jal node_alloc 
	sw t0,(a0) #store the int in the new node
	add t0,zero,s1#t0 used to recover last node later
	add s1,zero,a0#renew the tail pointer
	addi s9,s9,1#increase the index
	
	bgt s9,s8,el#if its the first node
	add s0,zero,a0#store the nodes adress in the array pointer
	j main
el:	sw a0,4(t0)#else store the current position in the last node as next node
	j main
	
l1_end: jal search_list
	j l1_end
	
	
read_int:
	addi a7,zero,5 #read int
	ecall
	jr ra,0
	
node_alloc:
	addi a7,zero,9 #node alloc
	addi a0,zero,8
	ecall
	jr ra,0
	
print_node:
	lw t0,(a0) #save node's int in t0
	bgt t0,a1,i2_else #if input<node
	jr ra,0		  #return
i2_else:addi a7,zero,1    #else print node
	add a0,zero,t0	
	ecall
	
	addi a7,zero,4#print a new line
	la a0,nline
	ecall
	jr ra,0

search_list:
	addi a7,zero,4 #print search str
	la a0,search_str
	ecall
	
	addi sp,sp,-12 #increase (decrease) stack pointer by 3 integers
	sw ra,(sp)#save the current return adress
	sw s2,4(sp)#save s2
	sw s3,8(sp)#save s3
		   #s2 and s3 are not used before but had to be saved
	jal read_int
	
i3:	bge a0,zero,i3_else#if input<0 exit
	addi a7,zero,10
	ecall
	
i3_else:add s3,zero,a0#compare int
	add s2,zero,s0#itterator pointer
	
l2:	ble s2,zero,l2_end #if s2>0 (branch if s2<=0) (if you are in the last node s2==0)
	
	add a1,zero,s3#a1 of print_node is the compared int
	add a0,zero,s2#a2 of print_node is the node
	jal print_node
	
	lw s2,4(s2) #advance the itterator to the next node's adress 
	j l2
	
l2_end:	lw ra,(sp)#restore return adress
	lw s2,4(sp)#restore s2
	lw s3,8(sp)#restore s3
	addi sp,sp,12 #return stack pointer in the correct position
	
	jr ra,0
