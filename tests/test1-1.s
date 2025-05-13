.arch armv8-a
.text
.type a, @object
.data
.global a
.align 4
a:
    .word 0
    .size a, 4

.text

.align 1
.global func
.type func, %function
func:
	str x29,[sp, #-48]!
	mov x29,sp
	str x0,[x29]
	ldr x0,[x29]
	mov x1,#1
	sub x2,x0,x1
	str x2,[x29,#16]
	ldr x0,[x29,#16]
	str x0,[x29]
	ldr x0,[x29]
	str x0,[x29,#8]
	b .L0
.L0:
	ldr x0,[x29,#8]
	ldr x29,[sp], #48
	ret

.align 1
.global main
.type main, %function
main:
	stp x29,lr,[sp, #-48]!
	mov x29,sp
	mov x0,#10
	adrp x16,a
	add x16,x16,:lo12:a
	str x0,[x16]
	adrp x0,a
	add x0,x0,:lo12:a
	ldr x0,[x0]
	bl func
	str x0,[x29,#16]
	ldr x0,[x29,#16]
	str x0,[x29,#8]
	ldr x0,[x29,#8]
	str x0,[x29]
	b .L1
.L1:
	ldr x0,[x29]
	ldp x29,lr,[sp], #48
	ret
