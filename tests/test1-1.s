.arch armv8-a
.text
.align 1
.global main
.type main, %function
main:
	stp x16,fp,[sp, #-16]!
	sub sp,sp,#4
	add fp,sp,#0
	mov x0,#10
	str x0,[fp]
	b .L0
.L0:
	ldr x0,[fp]
	add fp,fp,#4
	mov sp,fp
	ldp x16,fp,[sp], #16
	ret
