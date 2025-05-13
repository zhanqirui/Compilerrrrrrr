.arch armv8-a
.text
.type a, @object
.data
.global a
.align 4
a:
    .word 0
    .size a, 4

.type b, @object
.data
.global b
.align 4
b:
    .word 0
    .size b, 4

.type c, @object
.data
.global c
.align 4
c:
    .word 0
    .size c, 4

.type d, @object
.data
.global d
.align 4
d:
    .word 0
    .size d, 4

.type e, @object
.data
.global e
.align 4
e:
    .word 0
    .size e, 4

.text

.align 1
.global main
.type main, %function
main:
	stp x29,lr,[sp, #-16]!
	sub sp,sp,320
	mov x29,sp
	mov x0,#0
	str x0,[x29]
	bl getint
	str x0,[x29,#16]
	ldr x0,[x29,#16]
	adrp x16,a
	add x16,x16,:lo12:a
	str x0,[x16]
	bl getint
	str x0,[x29,#24]
	ldr x0,[x29,#24]
	adrp x16,b
	add x16,x16,:lo12:b
	str x0,[x16]
	bl getint
	str x0,[x29,#32]
	ldr x0,[x29,#32]
	adrp x16,c
	add x16,x16,:lo12:c
	str x0,[x16]
	bl getint
	str x0,[x29,#40]
	ldr x0,[x29,#40]
	adrp x16,d
	add x16,x16,:lo12:d
	str x0,[x16]
	bl getint
	str x0,[x29,#48]
	ldr x0,[x29,#48]
	adrp x16,e
	add x16,x16,:lo12:e
	str x0,[x16]
	mov x0,#0
	str x0,[x29,#8]
	adrp x0,a
	add x0,x0,:lo12:a
	ldr x0,[x0]
	str x0,[x29,#56]
	adrp x0,b
	add x0,x0,:lo12:b
	ldr x0,[x0]
	str x0,[x29,#64]
	adrp x0,c
	add x0,x0,:lo12:c
	ldr x0,[x0]
	str x0,[x29,#72]
	ldr x0,[x29,#64]
	ldr x1,[x29,#72]
	mul x2,x0,x1
	str x2,[x29,#80]
	ldr x0,[x29,#56]
	ldr x1,[x29,#80]
	sub x2,x0,x1
	str x2,[x29,#88]
	adrp x0,d
	add x0,x0,:lo12:d
	ldr x0,[x0]
	str x0,[x29,#96]
	adrp x0,a
	add x0,x0,:lo12:a
	ldr x0,[x0]
	str x0,[x29,#104]
	adrp x0,c
	add x0,x0,:lo12:c
	ldr x0,[x0]
	str x0,[x29,#112]
	ldr x0,[x29,#104]
	ldr x1,[x29,#112]
	sdiv x2,x0,x1
	str x2,[x29,#120]
	ldr x0,[x29,#96]
	ldr x1,[x29,#120]
	sub x2,x0,x1
	str x2,[x29,#128]
	ldr x0,[x29,#88]
	ldr x1,[x29,#128]
	cmp x0,x1
	cset x2,ne
	str x2,[x29,#136]
	adrp x0,a
	add x0,x0,:lo12:a
	ldr x0,[x0]
	str x0,[x29,#144]
	adrp x0,b
	add x0,x0,:lo12:b
	ldr x0,[x0]
	str x0,[x29,#152]
	ldr x0,[x29,#144]
	ldr x1,[x29,#152]
	mul x2,x0,x1
	str x2,[x29,#160]
	adrp x0,c
	add x0,x0,:lo12:c
	ldr x0,[x0]
	str x0,[x29,#168]
	ldr x0,[x29,#160]
	ldr x1,[x29,#168]
	sdiv x2,x0,x1
	str x2,[x29,#176]
	adrp x0,e
	add x0,x0,:lo12:e
	ldr x0,[x0]
	str x0,[x29,#184]
	adrp x0,d
	add x0,x0,:lo12:d
	ldr x0,[x0]
	str x0,[x29,#192]
	ldr x0,[x29,#184]
	ldr x1,[x29,#192]
	add x2,x0,x1
	str x2,[x29,#200]
	ldr x0,[x29,#176]
	ldr x1,[x29,#200]
	cmp x0,x1
	cset x2,eq
	str x2,[x29,#208]
	ldr x0,[x29,#136]
	ldr x1,[x29,#208]
	orr x2,x0,x1
	str x2,[x29,#216]
	adrp x0,a
	add x0,x0,:lo12:a
	ldr x0,[x0]
	str x0,[x29,#224]
	adrp x0,b
	add x0,x0,:lo12:b
	ldr x0,[x0]
	str x0,[x29,#232]
	ldr x0,[x29,#224]
	ldr x1,[x29,#232]
	add x2,x0,x1
	str x2,[x29,#240]
	adrp x0,c
	add x0,x0,:lo12:c
	ldr x0,[x0]
	str x0,[x29,#248]
	ldr x0,[x29,#240]
	ldr x1,[x29,#248]
	add x2,x0,x1
	str x2,[x29,#256]
	adrp x0,d
	add x0,x0,:lo12:d
	ldr x0,[x0]
	str x0,[x29,#264]
	adrp x0,e
	add x0,x0,:lo12:e
	ldr x0,[x0]
	str x0,[x29,#272]
	ldr x0,[x29,#264]
	ldr x1,[x29,#272]
	add x2,x0,x1
	str x2,[x29,#280]
	ldr x0,[x29,#256]
	ldr x1,[x29,#280]
	cmp x0,x1
	cset x2,eq
	str x2,[x29,#288]
	ldr x0,[x29,#216]
	ldr x1,[x29,#288]
	orr x2,x0,x1
	str x2,[x29,#296]
	ldr x0,[x29,#296]
	cmp x0,#0
	b.ne .L0
	b .L1
.L0:
	mov x0,#1
	str x0,[x29,#8]
	b .L1
.L1:
	ldr x0,[x29,#8]
	str x0,[x29,#304]
	ldr x0,[x29,#304]
	str x0,[x29]
	ldr x0,[x29]
	str x0,[x29,#312]
	ldr x0,[x29,#312]
	mov sp,x29
	add sp,sp,320
	ldp x29,lr,[sp], #16
	ret
