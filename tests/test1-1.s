.arch armv8-a
.text
.text

.align 1
.global main
.type main, %function
main:
	str x29,[sp, #-8]!
	sub sp,sp,248
	mov x29,sp
	mov x0,#0
	str x0,[x29]
	mov x0,#1
	str x0,[x29,#8]
	mov x0,#2
	str x0,[x29,#16]
	mov x0,#3
	str x0,[x29,#24]
	mov x0,#4
	str x0,[x29,#32]
	mov x0,#5
	str x0,[x29,#40]
	mov x0,#6
	str x0,[x29,#48]

	ldr x0,[x29,#24]
	str x0,[x29,#56]
	mov x0,#2
	ldr x1,[x29,#56]
	add x2,x0,x1
	str x2,[x29,#64]
	ldr x0,[x29,#64]
	mov x1,#6
	cmp x0,x1
	cset x2,lt
	str x2,[x29,#72]
	ldr x0,[x29,#72]
	mov x1,#1
	and x2,x0,x1
	str x2,[x29,#80]
	ldr x0,[x29,#80]
	cmp x0,#0
	b.ne .L1
	b 1
.L1:

	ldr x0,[x29,#40]
	str x0,[x29,#88]
	ldr x0,[x29,#8]
	str x0,[x29,#96]
	mov x0,#0
	ldr x1,[x29,#96]
	add x2,x0,x1
	str x2,[x29,#104]
	ldr x0,[x29,#104]
	mov x1,#0
	add x2,x0,x1
	str x2,[x29,#112]
	ldr x0,[x29,#88]
	ldr x1,[x29,#112]
	orr x2,x0,x1
	str x2,[x29,#120]
	ldr x0,[x29,#120]
	cmp x0,#0
	b.ne .L3
	b 2
.L3:

	mov x0,#9
	mov x1,#2
	cmp x0,x1
	cset x2,gt
	str x2,[x29,#128]
	mov x0,#0
	ldr x1,[x29,#128]
	and x2,x0,x1
	str x2,[x29,#136]
	ldr x0,[x29,#136]
	cmp x0,#0
	b.ne 3
	b .L5
.L5:

	ldr x0,[x29,#40]
	str x0,[x29,#144]
	mov x0,#0
	ldr x1,[x29,#144]
	and x2,x0,x1
	str x2,[x29,#152]
	ldr x0,[x29,#152]
	cmp x0,#0
	b.ne 4
	b .L7
.L7:

	ldr x0,[x29,#8]
	str x0,[x29,#160]
	mov x0,#2
	ldr x1,[x29,#160]
	add x2,x0,x1
	str x2,[x29,#168]
	ldr x0,[x29,#168]
	mov x1,#2
	cmp x0,x1
	cset x2,ge
	str x2,[x29,#176]
	ldr x0,[x29,#176]
	cmp x0,#0
	b.ne .L9
	b 5
.L9:

	mov x0,#-1
	mov x1,#0
	cmp x0,x1
	cset x2,ge
	str x2,[x29,#184]
	ldr x0,[x29,#184]
	mov x1,#0
	orr x2,x0,x1
	str x2,[x29,#192]
	ldr x0,[x29,#192]
	cmp x0,#0
	b.ne 6
	b .L11
.L11:

	mov x0,#1
	cmp x0,#0
	b.ne .L13
	b 7
.L13:

	ldr x0,[x29,#16]
	str x0,[x29,#200]
	ldr x0,[x29,#200]
	mov x1,#20
	add x2,x0,x1
	str x2,[x29,#208]
	ldr x0,[x29,#208]
	mov x1,#10
	cmp x0,x1
	cset x2,gt
	str x2,[x29,#216]
	ldr x0,[x29,#216]
	cmp x0,#0
	b.ne .L15
	b 8
.L15:

	ldr x0,[x29,#48]
	str x0,[x29,#224]
	mov x0,#0
	ldr x1,[x29,#224]
	add x2,x0,x1
	str x2,[x29,#232]
	ldr x0,[x29,#232]
	cmp x0,#0
	b.ne 9
	b 10
	mov x0,#1
	mov sp,x29
	add sp,sp,248
	ldr x29,[sp], #8
	ret
