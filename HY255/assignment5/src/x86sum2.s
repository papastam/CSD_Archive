	.file	"x86sum2.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"The sum from 0 to %d is %d\n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB1:
	.section	.text.startup,"ax",@progbits
.LHOTB1:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB7:
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
	movl	n, %eax
	movl	Sum, %edx
	testl	%eax, %eax
	js	.L3
	.p2align 4,,10
	.p2align 3
.L5:
	addl	%eax, %edx
	subl	$1, %eax
	cmpl	$-1, %eax
	jne	.L5
	movl	%edx, Sum
	movl	$-1, n
.L3:
	subl	$4, %esp
	pushl	%edx
	pushl	$1000
	pushl	$.LC0
	call	printf
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	addl	$16, %esp
	xorl	%eax, %eax
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE1:
	.section	.text.startup
.LHOTE1:
	.globl	Sum
	.bss
	.align 4
	.type	Sum, @object
	.size	Sum, 4
Sum:
	.zero	4
	.globl	n
	.data
	.align 4
	.type	n, @object
	.size	n, 4
n:
	.long	1000
	.ident	"GCC: (Debian 4.9.2-10+deb8u2) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
