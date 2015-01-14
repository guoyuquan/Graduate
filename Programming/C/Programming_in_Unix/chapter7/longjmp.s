	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp2:
	.cfi_def_cfa_offset 16
Ltmp3:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp4:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	leaq	_jmpbuffer(%rip), %rdi
	movl	$0, -4(%rbp)
	movl	$2, -8(%rbp)
	movl	$3, -12(%rbp)
	movl	$4, -16(%rbp)
	callq	_setjmp
	cmpl	$0, %eax
	je	LBB0_2
## BB#1:
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	leaq	L_.str1(%rip), %rdi
	movl	_globval(%rip), %esi
	movl	-8(%rbp), %edx
	movl	-12(%rbp), %ecx
	movl	-16(%rbp), %r8d
	movl	_main.statval(%rip), %r9d
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movl	$0, %edi
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	callq	_exit
LBB0_2:
	movl	$95, _globval(%rip)
	movl	$96, -8(%rbp)
	movl	$97, -12(%rbp)
	movl	$98, -16(%rbp)
	movl	$99, _main.statval(%rip)
	movl	-8(%rbp), %edi
	movl	-12(%rbp), %esi
	movl	-16(%rbp), %edx
	movl	_main.statval(%rip), %ecx
	callq	_f1
	movl	$0, %edi
	callq	_exit
	.cfi_endproc

	.align	4, 0x90
_f1:                                    ## @f1
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp7:
	.cfi_def_cfa_offset 16
Ltmp8:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp9:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	leaq	L_.str2(%rip), %rax
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movq	%rax, %rdi
	movb	$0, %al
	callq	_printf
	leaq	L_.str3(%rip), %rdi
	movl	_globval(%rip), %esi
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %ecx
	movl	-12(%rbp), %r8d
	movl	-16(%rbp), %r9d
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	callq	_f2
	addq	$32, %rsp
	popq	%rbp
	ret
	.cfi_endproc

	.align	4, 0x90
_f2:                                    ## @f2
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp12:
	.cfi_def_cfa_offset 16
Ltmp13:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp14:
	.cfi_def_cfa_register %rbp
	leaq	_jmpbuffer(%rip), %rdi
	movl	$1, %esi
	callq	_longjmp
	.cfi_endproc

	.section	__DATA,__data
	.align	2                       ## @main.statval
_main.statval:
	.long	5                       ## 0x5

.zerofill __DATA,__bss,_jmpbuffer,148,4 ## @jmpbuffer
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"after longjmp:\n"

L_.str1:                                ## @.str1
	.asciz	"gloabal value=%d, auto=%d, register=%d, volatile=%d, static=%d\n"

	.section	__DATA,__data
	.align	2                       ## @globval
_globval:
	.long	1                       ## 0x1

	.section	__TEXT,__cstring,cstring_literals
L_.str2:                                ## @.str2
	.asciz	"in f1(): \n"

L_.str3:                                ## @.str3
	.asciz	"global=%d, auto =%d, register = %d, volatile = %d, static = %d\n"


.subsections_via_symbols
