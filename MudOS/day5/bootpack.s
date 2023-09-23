	.file	"bootpack.c"
	.text
	.section	.text.MudMain,"ax",@progbits
	.globl	MudMain
	.type	MudMain, @function
MudMain:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	call	init_palette
	movl	$655360, -16(%ebp)
	movl	$0, -12(%ebp)
	jmp	.L2
.L3:
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	addl	%edx, %eax
	andl	$15, %ecx
	movl	%ecx, %edx
	movb	%dl, (%eax)
	addl	$1, -12(%ebp)
.L2:
	cmpl	$65535, -12(%ebp)
	jle	.L3
.L4:
	call	io_hlt
	jmp	.L4
	.size	MudMain, .-MudMain
	.section	.text.init_palette,"ax",@progbits
	.globl	init_palette
	.type	init_palette, @function
init_palette:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	subl	$4, %esp
	pushl	$table_rgb.0
	pushl	$15
	pushl	$0
	call	set_palette
	addl	$16, %esp
	nop
	leave
	ret
	.size	init_palette, .-init_palette
	.section	.text.set_palette,"ax",@progbits
	.globl	set_palette
	.type	set_palette, @function
set_palette:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	call	io_load_eflags
	movl	%eax, -16(%ebp)
	call	io_cli
	subl	$8, %esp
	pushl	8(%ebp)
	pushl	$968
	call	io_out8
	addl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	jmp	.L8
.L9:
	movl	16(%ebp), %eax
	movzbl	(%eax), %eax
	shrb	$2, %al
	movzbl	%al, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$969
	call	io_out8
	addl	$16, %esp
	movl	16(%ebp), %eax
	addl	$1, %eax
	movzbl	(%eax), %eax
	shrb	$2, %al
	movzbl	%al, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$969
	call	io_out8
	addl	$16, %esp
	movl	16(%ebp), %eax
	addl	$2, %eax
	movzbl	(%eax), %eax
	shrb	$2, %al
	movzbl	%al, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$969
	call	io_out8
	addl	$16, %esp
	addl	$3, 16(%ebp)
	addl	$1, -12(%ebp)
.L8:
	movl	-12(%ebp), %eax
	cmpl	12(%ebp), %eax
	jle	.L9
	subl	$12, %esp
	pushl	-16(%ebp)
	call	io_store_eflags
	addl	$16, %esp
	nop
	leave
	ret
	.size	set_palette, .-set_palette
	.data
	.align 32
	.type	table_rgb.0, @object
	.size	table_rgb.0, 48
table_rgb.0:
	.string	""
	.string	""
	.string	""
	.string	"\377"
	.string	""
	.string	""
	.string	"\377"
	.string	"\377\377"
	.string	""
	.string	""
	.string	"\377\377"
	.string	"\377"
	.string	"\377\377\377\377\377\306\306\306\204"
	.string	""
	.string	""
	.string	"\204"
	.string	"\204\204"
	.string	""
	.string	""
	.string	"\204\204"
	.string	"\204"
	.ascii	"\204\204\204\204\204"
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
