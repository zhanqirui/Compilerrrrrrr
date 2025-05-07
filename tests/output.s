	.text
	.file	"test1-1.c"
	.globl	add                             // -- Begin function add
	.p2align	2
	.type	add,@function
add:                                    // @add
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	w0, [sp, #12]
	str	w1, [sp, #8]
	ldr	w8, [sp, #12]
	ldr	w9, [sp, #8]
	add	w0, w8, w9
	add	sp, sp, #16
	ret
.Lfunc_end0:
	.size	add, .Lfunc_end0-add
	.cfi_endproc
                                        // -- End function
	.globl	main                            // -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   // @main
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	wzr, [sp, #12]
	mov	w8, #3
	str	w8, [sp, #8]
	ldr	w8, [sp, #8]
	subs	w8, w8, #1
	b.ne	.LBB1_2
	b	.LBB1_1
.LBB1_1:
	mov	w8, #3
	str	w8, [sp, #12]
	b	.LBB1_3
.LBB1_2:
	str	wzr, [sp, #12]
	b	.LBB1_3
.LBB1_3:
	ldr	w0, [sp, #12]
	add	sp, sp, #16
	ret
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        // -- End function
	.ident	"Ubuntu clang version 14.0.0-1ubuntu1.1"
	.section	".note.GNU-stack","",@progbits
	.addrsig
