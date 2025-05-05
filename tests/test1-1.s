.arch armv8-a
.text
.align 1
.global func
.type func, %function
func:
	stp x16,fp,[sp, #-16]!
	sub sp,sp,#20
	add fp,sp,#0
	str x0,[fp]
	str x1,[fp,#4]
	ldr x0,[fp,#16]
	str x0,[fp,#12]
	ldr x0,[fp]
	str x0,[fp,#8]
	b .L0
.L0:
	ldr x0,[fp,#8]
	add fp,fp,#20
	mov sp,fp
	ldp x16,fp,[sp], #16
	ret
.align 1
.global main
.type main, %function
main:
	stp x16,fp,[sp, #-16]!
	sub sp,sp,#4
	add fp,sp,#0

	ldr x0,[fp]
	add fp,fp,#4
	mov sp,fp
	ldp x16,fp,[sp], #16
	ret
