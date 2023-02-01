	.file	"x86sum_inline.c"
	.globl	n
	.data
	.align 4
	.type	n, @object
	.size	n, 4
n:
	.long	1000
	.globl	Sum
	.bss
	.align 4
	.type	Sum, @object
	.size	Sum, 4
Sum:
	.zero	4
	.section	.rodata
.LC0:
	.string	"The sum from 0 to %d is %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$4, %esp
#APP
# 13 "x86sum_inline.c" 1
	movl n, %ebx
L1:
	addl %ebx, Sum
	decl %ebx;cmpl $0, %ebx
	jng  L2
	movl $L1, %eax
	jmp *%eax
L2:
# 0 "" 2
#NO_APP
	movl	Sum, %eax
	subl	$4, %esp
	pushl	%eax
	pushl	$1000
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 4.9.2-10+deb8u2) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
