.arch armv8-a
.text
.comm a, 4, 4
.comm b, 4, 4
.align 1
.global main
.type main, %function
main:
	stp x16,fp,[sp, #-16]!
	sub sp,sp,#20
	add fp,sp,#0
	mov x0,#5
	str x0,[fp,#8]
	ldr x0,[fp,#8]
	adrp x1,b
	add x1,x1,:lo12:b
	ldr x1,[x1]
	add x2,x0,x1
	str x2,[fp,#16]
	ldr x0,[fp,#16]
	str x0,[fp]
	b .L0
.L0:
	ldr x0,[fp]
	add fp,fp,#20
	mov sp,fp
	ldp x16,fp,[sp], #16
	ret
