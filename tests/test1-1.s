	.arch armv8-a
	.text
	.global a
	.section	.rodata
	.align 4
	.type a, %object
	.size a, 20

a:
    .word 0
    .word 1
    .word 2
    .word 3
    .word 4
.text

.align 1
.global main
.type main, %function
main:
	str x29,[sp, #-8]!
	sub sp,sp,56
	mov x29,sp
	mov x0,#0
	str x0,[x29]
	
	adrp x0,a
	add x0,x0,:lo12:a
	ldr x0,[x0]
	add x0,x0,16
	str x0,[x29,#16]
	ldr x0,[x29,#16]
	ldr x0,[x0, #0]
	str x0,[x29,#24]
	ldr x0,[x29,#24]
	str x0,[x29]
	ldr x0,[x29]
	str x0,[x29,#32]
	ldr x0,[x29,#32]
	mov sp,x29
	add sp,sp,56
	ldr x29,[sp], #8
	ret
