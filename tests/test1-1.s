.arch armv8-a
.text
.align 1
.global main
.type main, %function
main:
	stp x16,fp,[sp, #-16]!
	sub sp,sp,#36
	add fp,sp,#0
	mov x0,#3
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
	str x0,[fp]
	b .L0
.L0:
	ldr x0,[fp]
	add fp,fp,#36
	mov sp,fp
	ldp x16,fp,[sp], #16
	ret
