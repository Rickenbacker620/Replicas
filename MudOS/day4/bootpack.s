	.file	"bootpack.c"
	.text
	.globl	MudMain
	.type	MudMain, @function
MudMain:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	subl	$8, %esp
	pushl	$51
	pushl	$4660
	call	write_mem8
	addl	$16, %esp
	movl	$655360, -12(%ebp)
	jmp	.L2
.L3:
	subl	$8, %esp
	pushl	$15
	pushl	-12(%ebp)
	call	write_mem8
	addl	$16, %esp
	addl	$1, -12(%ebp)
.L2:
	cmpl	$720895, -12(%ebp)
	jle	.L3
.L4:
	call	io_hlt
	jmp	.L4
	.cfi_endproc
.LFE0:
	.size	MudMain, .-MudMain
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
