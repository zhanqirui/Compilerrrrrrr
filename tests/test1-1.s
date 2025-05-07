.arch armv8-a
.text
.align 1
.global main
.type main, %function
main:
	stp x16,fp,[sp, #-16]!
	sub sp,sp,#40
	add fp,sp,#0
	mov x0,#4
	str x0,[fp,#8]
	mov x0,#10
	str x0,[fp,#16]
	ldr x0,[fp,#8]
	ldr x1,[fp,#16]
	add x2,x0,x1
	str x2,[fp,#32]
	ldr x0,[fp,#32]
	str x0,[fp,#24]

	ldr x0,[fp,#8]
	ldr x1,[fp,#16]
	cmp x0,x1
	cset x2,gt
	str x2,[fp,#36]
	ldr x0,[fp,#36]
	cmp x0,#0
	b.ne .L1
	b .L2
.L1:
	mov x0,#10
	str x0,[fp]
	b .L3
.L2:
	mov x0,#0
	str x0,[fp]
	b .L3
.L3:
	ldr x0,[fp]
	add fp,fp,#40
	mov sp,fp
	ldp x16,fp,[sp], #16
	ret
