	.arch armv8-a
	.text
	.global MAX_WIDTH
	.section	.rodata
	.align 4
	.type MAX_WIDTH, %object
	.size MAX_WIDTH, 4

MAX_WIDTH:
    .word 1024
	.global MAX_HEIGHT
	.section	.rodata
	.align 4
	.type MAX_HEIGHT, %object
	.size MAX_HEIGHT, 4

MAX_HEIGHT:
    .word 1024
	.global image
	.bss
	.align 4
	.type image, %object
	.size image, 4194304

image:
    .zero 4194304
	.global width
	.bss
	.align 4
	.type width, %object
	.size width, 4

width:
    .zero 4
	.global height
	.bss
	.align 4
	.type height, %object
	.size height, 4

height:
    .zero 4
	.global PI
	.section	.rodata
	.align 4
	.type PI, %object
	.size PI, 4

PI:
    .float 3.141593
	.global TWO_PI
	.section	.rodata
	.align 4
	.type TWO_PI, %object
	.size TWO_PI, 4

TWO_PI:
    .float 6.283185
	.global EPSILON
	.section	.rodata
	.align 4
	.type EPSILON, %object
	.size EPSILON, 4

EPSILON:
    .float 0.000001
.text

.align 1
.global my_fabs
.type my_fabs, %function
my_fabs:
//	@ x:%2:[sp,#0]
//	@ %3:[sp,#8]
//	@ %4:[sp,#16]
//	@ %6:[sp,#24]
//	@ %7:[sp,#32]
//	@ %8:[sp,#40]
//	@ %9:[sp,#48]
//	@ %11:[sp,#56]
//	@ %13:[sp,#64]
//	@ %14:[sp,#72]
//	@ %16:[sp,#80]
	stp x29,x30,[sp, #-16]!
	mov x29,sp
	sub sp,sp,96
	// store float 0x0, float* %3, align 4
	mov w16,#0
	movk w16,#0,lsl #16
	fmov s0,w16
	str s0,[sp,#8]
	// store float %0, float* %2, align 4
	str s0,[sp]
	// br label %5
	b .L0
	// 
5:
.L0:
	// %6 = load float, float* %2, align 4
	ldr s0,[sp]
	str s0,[sp,#24]
	// %7 = sitofp i32 0 to float
	movz x3,#0
	scvtf s0,w3
	str x3,[sp,#32]
	// %8 = fcmp ogt float %6, %7
	ldr s1,[sp,#24]
	ldr s2,[sp,#32]
	fcmp s1,s2
	cset x3,gt
	str x3,[sp,#40]
	// %9 = icmp ne i1 %8, 0
	ldr x3,[sp,#40]
	movz x4,#0
	cmp w3,w4
	cset x5,ne
	str x5,[sp,#48]
	// br i1 %9,  label %10,   label %12
	ldr x3,[sp,#48]
	cmp x3,#0
	b.ne .L1
	b .L2
	// 
10:
.L1:
	// %11 = load float, float* %2, align 4
	ldr s1,[sp]
	str s1,[sp,#56]
	// store float %11, float* %3, align 4
	ldr s1,[sp,#56]
	str s1,[sp,#8]
	// br label %15
	b .L3
	// 
12:
.L2:
	// %13 = load float, float* %2, align 4
	ldr s1,[sp]
	str s1,[sp,#64]
	// %14 = fsub float 0x0, %13
	mov w16,#0
	movk w16,#0,lsl #16
	fmov s1,w16
	ldr s2,[sp,#64]
	fsub s4,s1,s2
	str s4,[sp,#72]
	// store float %14, float* %3, align 4
	ldr s1,[sp,#72]
	str s1,[sp,#8]
	// br label %15
	b .L3
	// 
15:
.L3:
	// %16 = load float, float* %3, align 4
	ldr s1,[sp,#8]
	str s1,[sp,#80]
	// ret float %16
	ldr s0,[sp,#80]
	mov sp,x29
	ldp x29,x30,[sp], #16
	ret

.align 1
.global p
.type p, %function
p:
//	@ x:%2:[sp,#0]
//	@ %3:[sp,#8]
//	@ %4:[sp,#16]
//	@ %5:[sp,#24]
//	@ %6:[sp,#32]
//	@ %7:[sp,#40]
//	@ %8:[sp,#48]
//	@ %9:[sp,#56]
//	@ %10:[sp,#64]
//	@ %11:[sp,#72]
//	@ %12:[sp,#80]
//	@ %13:[sp,#88]
//	@ %14:[sp,#96]
//	@ %15:[sp,#104]
//	@ %17:[sp,#112]
	stp x29,x30,[sp, #-16]!
	mov x29,sp
	sub sp,sp,128
	// store float 0x0, float* %3, align 4
	mov w16,#0
	movk w16,#0,lsl #16
	fmov s1,w16
	str s1,[sp,#8]
	// store float %0, float* %2, align 4
	str s0,[sp]
	// %5 = load float, float* %2, align 4
	ldr s1,[sp]
	str s1,[sp,#24]
	// %6 = sitofp i32 3 to float
	movz x8,#3
	scvtf s1,w8
	str x8,[sp,#32]
	// %7 = fmul float %6, %5
	ldr s2,[sp,#32]
	ldr s5,[sp,#24]
	fmul s6,s2,s5
	str s6,[sp,#40]
	// %8 = load float, float* %2, align 4
	ldr s2,[sp]
	str s2,[sp,#48]
	// %9 = sitofp i32 4 to float
	movz x9,#4
	scvtf s2,w9
	str x9,[sp,#56]
	// %10 = fmul float %9, %8
	ldr s5,[sp,#56]
	ldr s7,[sp,#48]
	fmul s8,s5,s7
	str s8,[sp,#64]
	// %11 = load float, float* %2, align 4
	ldr s5,[sp]
	str s5,[sp,#72]
	// %12 = fmul float %10, %11
	ldr s5,[sp,#64]
	ldr s7,[sp,#72]
	fmul s9,s5,s7
	str s9,[sp,#80]
	// %13 = load float, float* %2, align 4
	ldr s5,[sp]
	str s5,[sp,#88]
	// %14 = fmul float %12, %13
	ldr s5,[sp,#80]
	ldr s7,[sp,#88]
	fmul s10,s5,s7
	str s10,[sp,#96]
	// %15 = fsub float %7, %14
	ldr s5,[sp,#40]
	ldr s7,[sp,#96]
	fsub s11,s5,s7
	str s11,[sp,#104]
	// store float %15, float* %3, align 4
	ldr s5,[sp,#104]
	str s5,[sp,#8]
	// br label %16
	b .L4
	// 
16:
.L4:
	// %17 = load float, float* %3, align 4
	ldr s5,[sp,#8]
	str s5,[sp,#112]
	// ret float %17
	ldr s0,[sp,#112]
	mov sp,x29
	ldp x29,x30,[sp], #16
	ret

.align 1
.global my_sin_impl
.type my_sin_impl, %function
my_sin_impl:
//	@ x:%2:[sp,#0]
//	@ %3:[sp,#8]
//	@ %4:[sp,#16]
//	@ %6:[sp,#24]
//	@ %7:[sp,#32]
//	@ %8:[sp,#40]
//	@ %9:[sp,#48]
//	@ %11:[sp,#56]
//	@ %13:[sp,#64]
//	@ %14:[sp,#72]
//	@ %15:[sp,#80]
//	@ %16:[sp,#88]
//	@ %18:[sp,#96]
	stp x29,x30,[sp, #-16]!
	mov x29,sp
	sub sp,sp,112
	// store float 0x0, float* %3, align 4
	mov w16,#0
	movk w16,#0,lsl #16
	fmov s5,w16
	str s5,[sp,#8]
	// store float %0, float* %2, align 4
	str s0,[sp]
	// br label %5
	b .L5
	// 
5:
.L5:
	// %6 = load float, float* %2, align 4
	ldr s5,[sp]
	str s5,[sp,#24]
	// store float %6, i32* x0, align 4
	ldr s0,[sp,#24]
	// %7 = call float @my_fabs(i32 x0)
	mov x0,x0
	bl my_fabs
	// store i32 x0, float* %7, align 4
	str x0,[sp,#32]
	// %8 = fcmp ole float %7, 0x3eb0c6f7a0000000
	ldr s5,[sp,#32]
	adrp x7,EPSILON
	add x7,x7,:lo12:EPSILON
	ldr s7,[x7]
	fcmp s5,s7
	cset x12,le
	str x12,[sp,#40]
	// %9 = icmp ne i1 %8, 0
	ldr x12,[sp,#40]
	movz x14,#0
	cmp w12,w14
	cset x15,ne
	str x15,[sp,#48]
	// br i1 %9,  label %10,   label %12
	ldr x12,[sp,#48]
	cmp x12,#0
	b.ne .L6
	b .L7
	// 
10:
.L6:
	// %11 = load float, float* %2, align 4
	ldr s5,[sp]
	str s5,[sp,#56]
	// store float %11, float* %3, align 4
	ldr s5,[sp,#56]
	str s5,[sp,#8]
	// br label %17
	b .L8
	// 
12:
.L7:
	// %13 = load float, float* %2, align 4
	ldr s5,[sp]
	str s5,[sp,#64]
	// %14 = fdiv float %13, 0x4008000000000000
	ldr s5,[sp,#64]
	mov w16,#0
	movk w16,#16448,lsl #16
	fmov s7,w16
	fdiv s13,s5,s7
	str s13,[sp,#72]
	// store float %14, i32* x0, align 4
	ldr s0,[sp,#72]
	// %15 = call float @my_sin_impl(i32 x0)
	mov x0,x0
	bl my_sin_impl
	// store i32 x0, float* %15, align 4
	str x0,[sp,#80]
	// store float %15, i32* x0, align 4
	ldr s0,[sp,#80]
	// %16 = call float @p(i32 x0)
	mov x0,x0
	bl p
	// store i32 x0, float* %16, align 4
	str x0,[sp,#88]
	// store float %16, float* %3, align 4
	ldr s5,[sp,#88]
	str s5,[sp,#8]
	// br label %17
	b .L8
	// 
17:
.L8:
	// %18 = load float, float* %3, align 4
	ldr s5,[sp,#8]
	str s5,[sp,#96]
	// ret float %18
	ldr s0,[sp,#96]
	mov sp,x29
	ldp x29,x30,[sp], #16
	ret

.align 1
.global my_sin
.type my_sin, %function
my_sin:
//	@ x:%2:[sp,#0]
//	@ %3:[sp,#8]
//	@ %4:[sp,#16]
//	@ xx:%5:[sp,#24]
//	@ %7:[sp,#32]
//	@ %8:[sp,#40]
//	@ %9:[sp,#48]
//	@ %11:[sp,#56]
//	@ %12:[sp,#64]
//	@ %13:[sp,#72]
//	@ %14:[sp,#80]
//	@ %18:[sp,#88]
//	@ %19:[sp,#96]
//	@ %21:[sp,#104]
//	@ %22:[sp,#112]
//	@ %23:[sp,#120]
//	@ %24:[sp,#128]
//	@ %25:[sp,#136]
//	@ %26:[sp,#144]
//	@ %27:[sp,#152]
//	@ %28:[sp,#160]
//	@ %31:[sp,#168]
//	@ %32:[sp,#176]
//	@ %33:[sp,#184]
//	@ %35:[sp,#192]
//	@ %36:[sp,#200]
//	@ %39:[sp,#208]
//	@ %40:[sp,#216]
//	@ %41:[sp,#224]
//	@ %42:[sp,#232]
//	@ %44:[sp,#240]
//	@ %45:[sp,#248]
//	@ %47:[sp,#256]
//	@ %48:[sp,#264]
//	@ %50:[sp,#272]
	stp x29,x30,[sp, #-16]!
	mov x29,sp
	sub sp,sp,288
	// store float 0x0, float* %3, align 4
	mov w16,#0
	movk w16,#0,lsl #16
	fmov s5,w16
	str s5,[sp,#8]
	// store float %0, float* %2, align 4
	str s0,[sp]
	// br label %6
	b .L9
	// 
6:
.L9:
	// %7 = load float, float* %2, align 4
	ldr s5,[sp]
	str s5,[sp,#32]
	// %8 = fcmp ogt float %7, 0x401921fb60000000
	ldr s5,[sp,#32]
	adrp x7,TWO_PI
	add x7,x7,:lo12:TWO_PI
	ldr s7,[x7]
	fcmp s5,s7
	cset x14,gt
	str x14,[sp,#40]
	// %9 = icmp ne i1 %8, 0
	ldr x14,[sp,#40]
	movz x13,#0
	cmp w14,w13
	cset x8,ne
	str x8,[sp,#48]
	// br i1 %9,  label %15,   label %10
	ldr x8,[sp,#48]
	cmp x8,#0
	b.ne .L11
	b .L10
	// 
10:
.L10:
	// %11 = load float, float* %2, align 4
	ldr s5,[sp]
	str s5,[sp,#56]
	// %12 = fsub float 0x0, 0x401921fb60000000
	mov w16,#0
	movk w16,#0,lsl #16
	fmov s5,w16
	adrp x7,TWO_PI
	add x7,x7,:lo12:TWO_PI
	ldr s7,[x7]
	fsub s15,s5,s7
	str s15,[sp,#64]
	// %13 = fcmp olt float %11, %12
	ldr s5,[sp,#56]
	ldr s7,[sp,#64]
	fcmp s5,s7
	cset x8,lt
	str x8,[sp,#72]
	// %14 = icmp ne i1 %13, 0
	ldr x8,[sp,#72]
	movz x13,#0
	cmp w8,w13
	cset x14,ne
	str x14,[sp,#80]
	// br i1 %14,  label %15,   label %16
	ldr x8,[sp,#80]
	cmp x8,#0
	b.ne .L11
	b .L12
	// 
15:
.L11:
	// store i32 1, i32* %4, align 4
	movz x8,#1
	str x8,[sp,#16]
	// br label %17
	b .L13
	// 
16:
.L12:
	// store i32 0, i32* %4, align 4
	movz x8,#0
	str x8,[sp,#16]
	// br label %17
	b .L13
	// 
17:
.L13:
	// %18 = load i32, i32* %4, align 4
	ldr x8,[sp,#16]
	str x8,[sp,#88]
	// %19 = icmp ne i32 %18, 0
	ldr x8,[sp,#88]
	movz x9,#0
	cmp w8,w9
	cset x3,ne
	str x3,[sp,#96]
	// br i1 %19,  label %20,   label %29
	ldr x3,[sp,#96]
	cmp x3,#0
	b.ne .L14
	b .L15
	// 
20:
.L14:
	// %21 = load float, float* %2, align 4
	ldr s5,[sp]
	str s5,[sp,#104]
	// %22 = fdiv float %21, 0x401921fb60000000
	ldr s5,[sp,#104]
	adrp x7,TWO_PI
	add x7,x7,:lo12:TWO_PI
	ldr s7,[x7]
	fdiv s9,s5,s7
	str s9,[sp,#112]
	// %23 = fptosi float %22 to i32
	ldr s5,[sp,#112]
	fcvtzs s5,s5
	str s5,[sp,#120]
	// store i32 %23, i32* %5, align 4
	ldr x8,[sp,#120]
	str x8,[sp,#24]
	// %24 = load float, float* %2, align 4
	ldr s5,[sp]
	str s5,[sp,#128]
	// %25 = load i32, i32* %5, align 4
	ldr x10,[sp,#24]
	str x10,[sp,#136]
	// %26 = sitofp i32 %25 to float
	ldr x10,[sp,#136]
	scvtf s5,w10
	str x10,[sp,#144]
	// %27 = fmul float %26, 0x401921fb60000000
	ldr s7,[sp,#144]
	adrp x15,TWO_PI
	add x15,x15,:lo12:TWO_PI
	ldr s15,[x15]
	fmul s6,s7,s15
	str s6,[sp,#152]
	// %28 = fsub float %24, %27
	ldr s7,[sp,#128]
	ldr s15,[sp,#152]
	fsub s10,s7,s15
	str s10,[sp,#160]
	// store float %28, float* %2, align 4
	ldr s7,[sp,#160]
	str s7,[sp]
	// br label %29
	b .L15
	// 
29:
.L15:
	// br label %30
	b .L16
	// 
30:
.L16:
	// %31 = load float, float* %2, align 4
	ldr s7,[sp]
	str s7,[sp,#168]
	// %32 = fcmp ogt float %31, 0x400921fb60000000
	ldr s7,[sp,#168]
	adrp x15,PI
	add x15,x15,:lo12:PI
	ldr s15,[x15]
	fcmp s7,s15
	cset x11,gt
	str x11,[sp,#176]
	// %33 = icmp ne i1 %32, 0
	ldr x11,[sp,#176]
	movz x6,#0
	cmp w11,w6
	cset x15,ne
	str x15,[sp,#184]
	// br i1 %33,  label %34,   label %37
	ldr x6,[sp,#184]
	cmp x6,#0
	b.ne .L17
	b .L18
	// 
34:
.L17:
	// %35 = load float, float* %2, align 4
	ldr s7,[sp]
	str s7,[sp,#192]
	// %36 = fsub float %35, 0x401921fb60000000
	ldr s7,[sp,#192]
	adrp x15,TWO_PI
	add x15,x15,:lo12:TWO_PI
	ldr s15,[x15]
	fsub s4,s7,s15
	str s4,[sp,#200]
	// store float %36, float* %2, align 4
	ldr s7,[sp,#200]
	str s7,[sp]
	// br label %37
	b .L18
	// 
37:
.L18:
	// br label %38
	b .L19
	// 
38:
.L19:
	// %39 = load float, float* %2, align 4
	ldr s7,[sp]
	str s7,[sp,#208]
	// %40 = fsub float 0x0, 0x400921fb60000000
	mov w16,#0
	movk w16,#0,lsl #16
	fmov s7,w16
	adrp x15,PI
	add x15,x15,:lo12:PI
	ldr s15,[x15]
	fsub s13,s7,s15
	str s13,[sp,#216]
	// %41 = fcmp olt float %39, %40
	ldr s7,[sp,#208]
	ldr s15,[sp,#216]
	fcmp s7,s15
	cset x9,lt
	str x9,[sp,#224]
	// %42 = icmp ne i1 %41, 0
	ldr x9,[sp,#224]
	movz x15,#0
	cmp w9,w15
	cset x1,ne
	str x1,[sp,#232]
	// br i1 %42,  label %43,   label %46
	ldr x1,[sp,#232]
	cmp x1,#0
	b.ne .L20
	b .L21
	// 
43:
.L20:
	// %44 = load float, float* %2, align 4
	ldr s7,[sp]
	str s7,[sp,#240]
	// %45 = fadd float %44, 0x401921fb60000000
	ldr s7,[sp,#240]
	adrp x15,TWO_PI
	add x15,x15,:lo12:TWO_PI
	ldr s15,[x15]
	fadd s6,s7,s15
	str s6,[sp,#248]
	// store float %45, float* %2, align 4
	ldr s7,[sp,#248]
	str s7,[sp]
	// br label %46
	b .L21
	// 
46:
.L21:
	// %47 = load float, float* %2, align 4
	ldr s7,[sp]
	str s7,[sp,#256]
	// store float %47, i32* x0, align 4
	ldr s0,[sp,#256]
	// %48 = call float @my_sin_impl(i32 x0)
	mov x0,x0
	bl my_sin_impl
	// store i32 x0, float* %48, align 4
	str x0,[sp,#264]
	// store float %48, float* %3, align 4
	ldr s7,[sp,#264]
	str s7,[sp,#8]
	// br label %49
	b .L22
	// 
49:
.L22:
	// %50 = load float, float* %3, align 4
	ldr s7,[sp,#8]
	str s7,[sp,#272]
	// ret float %50
	ldr s0,[sp,#272]
	mov sp,x29
	ldp x29,x30,[sp], #16
	ret

.align 1
.global my_cos
.type my_cos, %function
my_cos:
//	@ x:%2:[sp,#0]
//	@ %3:[sp,#8]
//	@ %4:[sp,#16]
//	@ %5:[sp,#24]
//	@ %6:[sp,#32]
//	@ %7:[sp,#40]
//	@ %9:[sp,#48]
	stp x29,x30,[sp, #-16]!
	mov x29,sp
	sub sp,sp,64
	// store float 0x0, float* %3, align 4
	mov w16,#0
	movk w16,#0,lsl #16
	fmov s7,w16
	str s7,[sp,#8]
	// store float %0, float* %2, align 4
	str s0,[sp]
	// %5 = load float, float* %2, align 4
	ldr s7,[sp]
	str s7,[sp,#24]
	// %6 = fadd float %5, 0x3ff0000000000000
	ldr s7,[sp,#24]
	mov w16,#0
	movk w16,#16256,lsl #16
	fmov s15,w16
	fadd s10,s7,s15
	str s10,[sp,#32]
	// store float %6, i32* x0, align 4
	ldr s0,[sp,#32]
	// %7 = call float @my_sin(i32 x0)
	mov x0,x0
	bl my_sin
	// store i32 x0, float* %7, align 4
	str x0,[sp,#40]
	// store float %7, float* %3, align 4
	ldr s7,[sp,#40]
	str s7,[sp,#8]
	// br label %8
	b .L23
	// 
8:
.L23:
	// %9 = load float, float* %3, align 4
	ldr s7,[sp,#8]
	str s7,[sp,#48]
	// ret float %9
	ldr s0,[sp,#48]
	mov sp,x29
	ldp x29,x30,[sp], #16
	ret

.align 1
.global read_image
.type read_image, %function
read_image:
//	@ %1:[sp,#0]
//	@ %2:[sp,#8]
//	@ y:%3:[sp,#16]
//	@ x:%4:[sp,#24]
//	@ %6:[sp,#32]
//	@ %7:[sp,#40]
//	@ %8:[sp,#48]
//	@ %10:[sp,#56]
//	@ %11:[sp,#64]
//	@ %12:[sp,#72]
//	@ %16:[sp,#80]
//	@ %17:[sp,#88]
//	@ %19:[sp,#96]
//	@ %21:[sp,#104]
//	@ %22:[sp,#112]
//	@ %24:[sp,#120]
//	@ %25:[sp,#128]
//	@ %26:[sp,#136]
//	@ %28:[sp,#144]
//	@ %29:[sp,#152]
//	@ %30:[sp,#160]
//	@ %34:[sp,#168]
//	@ %35:[sp,#176]
//	@ %37:[sp,#184]
//	@ %38:[sp,#192]
//	@ %39:[sp,#200]
//	@ %43:[sp,#208]
//	@ %44:[sp,#216]
//	@ %46:[sp,#224]
//	@ %49:[sp,#232]
//	@ %50:[sp,#240]
//	@ %51:[sp,#248]
//	@ %52:[sp,#256]
//	@ %55:[sp,#264]
//	@ %56:[sp,#272]
//	@ %57:[sp,#280]
//	@ %58:[sp,#288]
//	@ %60:[sp,#296]
//	@ %61:[sp,#304]
//	@ %62:[sp,#312]
//	@ %63:[sp,#320]
//	@ %64:[sp,#328]
//	@ %65:[sp,#336]
//	@ %66:[sp,#344]
//	@ %67:[sp,#352]
//	@ %68:[sp,#360]
//	@ %69:[sp,#368]
//	@ %70:[sp,#376]
//	@ %72:[sp,#384]
//	@ %73:[sp,#392]
//	@ %76:[sp,#400]
	stp x29,x30,[sp, #-16]!
	mov x29,sp
	sub sp,sp,416
	// store i32 0, i32* %1, align 4
	movz x5,#0
	str x5,[sp]
	// br label %5
	b .L24
	// 
5:
.L24:
	// %6 = call i32 (...) @getch()
	bl getch
	// store i32 x0, i32* %6, align 4
	str x0,[sp,#32]
	// %7 = icmp ne i32 %6, 80
	ldr x5,[sp,#32]
	movz x14,#80
	cmp w5,w14
	cset x7,ne
	str x7,[sp,#40]
	// %8 = icmp ne i1 %7, 0
	ldr x5,[sp,#40]
	movz x7,#0
	cmp w5,w7
	cset x14,ne
	str x14,[sp,#48]
	// br i1 %8,  label %13,   label %9
	ldr x5,[sp,#48]
	cmp x5,#0
	b.ne .L26
	b .L25
	// 
9:
.L25:
	// %10 = call i32 (...) @getch()
	bl getch
	// store i32 x0, i32* %10, align 4
	str x0,[sp,#56]
	// %11 = icmp ne i32 %10, 50
	ldr x5,[sp,#56]
	movz x7,#50
	cmp w5,w7
	cset x14,ne
	str x14,[sp,#64]
	// %12 = icmp ne i1 %11, 0
	ldr x5,[sp,#64]
	movz x7,#0
	cmp w5,w7
	cset x14,ne
	str x14,[sp,#72]
	// br i1 %12,  label %13,   label %14
	ldr x5,[sp,#72]
	cmp x5,#0
	b.ne .L26
	b .L27
	// 
13:
.L26:
	// store i32 1, i32* %2, align 4
	movz x5,#1
	str x5,[sp,#8]
	// br label %15
	b .L28
	// 
14:
.L27:
	// store i32 0, i32* %2, align 4
	movz x5,#0
	str x5,[sp,#8]
	// br label %15
	b .L28
	// 
15:
.L28:
	// %16 = load i32, i32* %2, align 4
	ldr x5,[sp,#8]
	str x5,[sp,#80]
	// %17 = icmp ne i32 %16, 0
	ldr x5,[sp,#80]
	movz x14,#0
	cmp w5,w14
	cset x3,ne
	str x3,[sp,#88]
	// br i1 %17,  label %18,   label %20
	ldr x3,[sp,#88]
	cmp x3,#0
	b.ne .L29
	b .L30
	// 
18:
.L29:
	// %19 = sub nsw i32 0, 1
	movz x3,#0
	movz x5,#1
	sub w14,w3,w5
	str x14,[sp,#96]
	// store i32 %19, i32* %1, align 4
	ldr x3,[sp,#96]
	str x3,[sp]
	// br label %75
	b .L48
	// 
20:
.L30:
	// %21 = call i32 (...) @getint()
	bl getint
	// store i32 x0, i32* %21, align 4
	str x0,[sp,#104]
	// store i32 %21, i32* @width, align 4
	ldr x3,[sp,#104]
	adrp x16,width
	add x16,x16,:lo12:width
	str x3,[x16]
	// %22 = call i32 (...) @getint()
	bl getint
	// store i32 x0, i32* %22, align 4
	str x0,[sp,#112]
	// store i32 %22, i32* @height, align 4
	ldr x3,[sp,#112]
	adrp x16,height
	add x16,x16,:lo12:height
	str x3,[x16]
	// br label %23
	b .L31
	// 
23:
.L31:
	// %24 = load i32, i32* @width, align 4
	adrp x3,width
	add x3,x3,:lo12:width
	ldr x3,[x3]
	str x3,[sp,#120]
	// %25 = icmp sgt i32 %24, 1024
	ldr x3,[sp,#120]
	adrp x12,MAX_WIDTH
	add x12,x12,:lo12:MAX_WIDTH
	ldr x12,[x12]
	cmp w3,w12
	cset x8,gt
	str x8,[sp,#128]
	// %26 = icmp ne i1 %25, 0
	ldr x3,[sp,#128]
	movz x8,#0
	cmp w3,w8
	cset x12,ne
	str x12,[sp,#136]
	// br i1 %26,  label %31,   label %27
	ldr x3,[sp,#136]
	cmp x3,#0
	b.ne .L33
	b .L32
	// 
27:
.L32:
	// %28 = load i32, i32* @height, align 4
	adrp x3,height
	add x3,x3,:lo12:height
	ldr x3,[x3]
	str x3,[sp,#144]
	// %29 = icmp sgt i32 %28, 1024
	ldr x3,[sp,#144]
	adrp x12,MAX_HEIGHT
	add x12,x12,:lo12:MAX_HEIGHT
	ldr x12,[x12]
	cmp w3,w12
	cset x5,gt
	str x5,[sp,#152]
	// %30 = icmp ne i1 %29, 0
	ldr x3,[sp,#152]
	movz x5,#0
	cmp w3,w5
	cset x12,ne
	str x12,[sp,#160]
	// br i1 %30,  label %31,   label %32
	ldr x3,[sp,#160]
	cmp x3,#0
	b.ne .L33
	b .L34
	// 
31:
.L33:
	// store i32 1, i32* %2, align 4
	movz x3,#1
	str x3,[sp,#8]
	// br label %33
	b .L35
	// 
32:
.L34:
	// store i32 0, i32* %2, align 4
	movz x3,#0
	str x3,[sp,#8]
	// br label %33
	b .L35
	// 
33:
.L35:
	// %34 = load i32, i32* %2, align 4
	ldr x3,[sp,#8]
	str x3,[sp,#168]
	// %35 = icmp ne i32 %34, 0
	ldr x3,[sp,#168]
	movz x12,#0
	cmp w3,w12
	cset x14,ne
	str x14,[sp,#176]
	// br i1 %35,  label %40,   label %36
	ldr x3,[sp,#176]
	cmp x3,#0
	b.ne .L37
	b .L36
	// 
36:
.L36:
	// %37 = call i32 (...) @getint()
	bl getint
	// store i32 x0, i32* %37, align 4
	str x0,[sp,#184]
	// %38 = icmp ne i32 %37, 255
	ldr x3,[sp,#184]
	movz x12,#255
	cmp w3,w12
	cset x14,ne
	str x14,[sp,#192]
	// %39 = icmp ne i1 %38, 0
	ldr x3,[sp,#192]
	movz x12,#0
	cmp w3,w12
	cset x14,ne
	str x14,[sp,#200]
	// br i1 %39,  label %40,   label %41
	ldr x3,[sp,#200]
	cmp x3,#0
	b.ne .L37
	b .L38
	// 
40:
.L37:
	// store i32 1, i32* %2, align 4
	movz x3,#1
	str x3,[sp,#8]
	// br label %42
	b .L39
	// 
41:
.L38:
	// store i32 0, i32* %2, align 4
	movz x3,#0
	str x3,[sp,#8]
	// br label %42
	b .L39
	// 
42:
.L39:
	// %43 = load i32, i32* %2, align 4
	ldr x3,[sp,#8]
	str x3,[sp,#208]
	// %44 = icmp ne i32 %43, 0
	ldr x3,[sp,#208]
	movz x14,#0
	cmp w3,w14
	cset x8,ne
	str x8,[sp,#216]
	// br i1 %44,  label %45,   label %47
	ldr x3,[sp,#216]
	cmp x3,#0
	b.ne .L40
	b .L41
	// 
45:
.L40:
	// %46 = sub nsw i32 0, 1
	movz x3,#0
	movz x8,#1
	sub w14,w3,w8
	str x14,[sp,#224]
	// store i32 %46, i32* %1, align 4
	ldr x3,[sp,#224]
	str x3,[sp]
	// br label %75
	b .L48
	// 
47:
.L41:
	// store i32 0, i32* %3, align 4
	movz x3,#0
	str x3,[sp,#16]
	// br label %48
	b .L42
	// 
48:
.L42:
	// %49 = load i32, i32* %3, align 4
	ldr x3,[sp,#16]
	str x3,[sp,#232]
	// %50 = load i32, i32* @height, align 4
	adrp x3,height
	add x3,x3,:lo12:height
	ldr x3,[x3]
	str x3,[sp,#240]
	// %51 = icmp slt i32 %49, %50
	ldr x3,[sp,#232]
	ldr x6,[sp,#240]
	cmp w3,w6
	cset x5,lt
	str x5,[sp,#248]
	// %52 = icmp ne i1 %51, 0
	ldr x3,[sp,#248]
	movz x5,#0
	cmp w3,w5
	cset x6,ne
	str x6,[sp,#256]
	// br i1 %52,  label %53,   label %74
	ldr x3,[sp,#256]
	cmp x3,#0
	b.ne .L43
	b .L47
	// 
53:
.L43:
	// store i32 0, i32* %4, align 4
	movz x3,#0
	str x3,[sp,#24]
	// br label %54
	b .L44
	// 
54:
.L44:
	// %55 = load i32, i32* %4, align 4
	ldr x3,[sp,#24]
	str x3,[sp,#264]
	// %56 = load i32, i32* @width, align 4
	adrp x3,width
	add x3,x3,:lo12:width
	ldr x3,[x3]
	str x3,[sp,#272]
	// %57 = icmp slt i32 %55, %56
	ldr x3,[sp,#264]
	ldr x1,[sp,#272]
	cmp w3,w1
	cset x10,lt
	str x10,[sp,#280]
	// %58 = icmp ne i1 %57, 0
	ldr x1,[sp,#280]
	movz x3,#0
	cmp w1,w3
	cset x10,ne
	str x10,[sp,#288]
	// br i1 %58,  label %59,   label %71
	ldr x1,[sp,#288]
	cmp x1,#0
	b.ne .L45
	b .L46
	// 
59:
.L45:
	// %60 = call i32 (...) @getint()
	bl getint
	// store i32 x0, i32* %60, align 4
	str x0,[sp,#296]
	// %61 = load i32, i32* %3, align 4
	ldr x1,[sp,#16]
	str x1,[sp,#304]
	// %62 = load i32, i32* @width, align 4
	adrp x1,width
	add x1,x1,:lo12:width
	ldr x1,[x1]
	str x1,[sp,#312]
	// %63 = mul nsw i32 %61, %62
	ldr x1,[sp,#304]
	ldr x9,[sp,#312]
	mul w7,w1,w9
	str x7,[sp,#320]
	// %64 = load i32, i32* %4, align 4
	ldr x1,[sp,#24]
	str x1,[sp,#328]
	// %65 = add nsw i32 %63, %64
	ldr x1,[sp,#320]
	ldr x9,[sp,#328]
	add w12,w1,w9
	str x12,[sp,#336]
	// %66 = add nsw i32 0, %65
	movz x1,#0
	ldr x9,[sp,#336]
	add w12,w1,w9
	str x12,[sp,#344]
	// %67 = bitcast [1048576 x i32]* @image to i32*
	// %68 = getelementptr inbounds i32, i32* %67, i32 %66
	adrp x1,image
	add x1,x1,:lo12:image
	ldr x9,[sp,#344]
	lsl x9,x9,#2
	add x1,x1,x9
	str x1,[sp,#360]
	// store i32 %60, i32*  %68, align 4
	ldr x1,[sp,#296]
	ldr x9,[sp,#360]
	str w1,[x9, #0]
	// %69 = load i32, i32* %4, align 4
	ldr x1,[sp,#24]
	str x1,[sp,#368]
	// %70 = add nsw i32 %69, 1
	ldr x1,[sp,#368]
	movz x12,#1
	add w2,w1,w12
	str x2,[sp,#376]
	// store i32 %70, i32* %4, align 4
	ldr x1,[sp,#376]
	str x1,[sp,#24]
	// br label %54
	b .L44
	// 
71:
.L46:
	// %72 = load i32, i32* %3, align 4
	ldr x1,[sp,#16]
	str x1,[sp,#384]
	// %73 = add nsw i32 %72, 1
	ldr x1,[sp,#384]
	movz x12,#1
	add w15,w1,w12
	str x15,[sp,#392]
	// store i32 %73, i32* %3, align 4
	ldr x1,[sp,#392]
	str x1,[sp,#16]
	// br label %48
	b .L42
	// 
74:
.L47:
	// store i32 0, i32* %1, align 4
	movz x1,#0
	str x1,[sp]
	// br label %75
	b .L48
	// 
75:
.L48:
	// %76 = load i32, i32* %1, align 4
	ldr x1,[sp]
	str x1,[sp,#400]
	// ret i32 %76
	ldr x0,[sp,#400]
	mov sp,x29
	ldp x29,x30,[sp], #16
	ret

.align 1
.global rotate
.type rotate, %function
rotate:
//	@ x:%4:[sp,#0]
//	@ y:%5:[sp,#8]
//	@ rad:%6:[sp,#16]
//	@ %7:[sp,#24]
//	@ %8:[sp,#32]
//	@ sinma:%9:[sp,#40]
//	@ cosma:%10:[sp,#48]
//	@ hwidth:%11:[sp,#56]
//	@ hheight:%12:[sp,#64]
//	@ xt:%13:[sp,#72]
//	@ yt:%14:[sp,#80]
//	@ src_x:%15:[sp,#88]
//	@ src_y:%16:[sp,#96]
//	@ %17:[sp,#104]
//	@ %18:[sp,#112]
//	@ %19:[sp,#120]
//	@ %20:[sp,#128]
//	@ %21:[sp,#136]
//	@ %22:[sp,#144]
//	@ %23:[sp,#152]
//	@ %24:[sp,#160]
//	@ %25:[sp,#168]
//	@ %26:[sp,#176]
//	@ %27:[sp,#184]
//	@ %28:[sp,#192]
//	@ %29:[sp,#200]
//	@ %30:[sp,#208]
//	@ %31:[sp,#216]
//	@ %32:[sp,#224]
//	@ %33:[sp,#232]
//	@ %34:[sp,#240]
//	@ %35:[sp,#248]
//	@ %36:[sp,#256]
//	@ %37:[sp,#264]
//	@ %38:[sp,#272]
//	@ %39:[sp,#280]
//	@ %40:[sp,#288]
//	@ %41:[sp,#296]
//	@ %42:[sp,#304]
//	@ %43:[sp,#312]
//	@ %44:[sp,#320]
//	@ %45:[sp,#328]
//	@ %46:[sp,#336]
//	@ %47:[sp,#344]
//	@ %48:[sp,#352]
//	@ %49:[sp,#360]
//	@ %50:[sp,#368]
//	@ %51:[sp,#376]
//	@ %52:[sp,#384]
//	@ %53:[sp,#392]
//	@ %54:[sp,#400]
//	@ %55:[sp,#408]
//	@ %56:[sp,#416]
//	@ %58:[sp,#424]
//	@ %59:[sp,#432]
//	@ %60:[sp,#440]
//	@ %62:[sp,#448]
//	@ %63:[sp,#456]
//	@ %64:[sp,#464]
//	@ %65:[sp,#472]
//	@ %69:[sp,#480]
//	@ %70:[sp,#488]
//	@ %72:[sp,#496]
//	@ %73:[sp,#504]
//	@ %74:[sp,#512]
//	@ %78:[sp,#520]
//	@ %79:[sp,#528]
//	@ %81:[sp,#536]
//	@ %82:[sp,#544]
//	@ %83:[sp,#552]
//	@ %84:[sp,#560]
//	@ %88:[sp,#568]
//	@ %89:[sp,#576]
//	@ %92:[sp,#584]
//	@ %93:[sp,#592]
//	@ %94:[sp,#600]
//	@ %95:[sp,#608]
//	@ %96:[sp,#616]
//	@ %97:[sp,#624]
//	@ %98:[sp,#632]
//	@ %99:[sp,#640]
//	@ %100:[sp,#648]
//	@ %102:[sp,#656]
	stp x29,x30,[sp, #-16]!
	mov x29,sp
	movz x15,#672
	sub sp,sp,x15
	// store i32 0, i32* %7, align 4
	movz x15,#0
	str x15,[sp,#24]
	// store i32 %0, i32* %4, align 4
	str x0,[sp]
	// store i32 %1, i32* %5, align 4
	str x1,[sp,#8]
	// store float %2, float* %6, align 4
	str s2,[sp,#16]
	// %17 = load float, float* %6, align 4
	ldr s7,[sp,#16]
	str s7,[sp,#104]
	// store float %17, i32* x0, align 4
	ldr s0,[sp,#104]
	// %18 = call float @my_sin(i32 x0)
	mov x0,x0
	bl my_sin
	// store i32 x0, float* %18, align 4
	str x0,[sp,#112]
	// store float %18, float* %9, align 4
	ldr s7,[sp,#112]
	str s7,[sp,#40]
	// %19 = load float, float* %6, align 4
	ldr s7,[sp,#16]
	str s7,[sp,#120]
	// store float %19, i32* x0, align 4
	ldr s0,[sp,#120]
	// %20 = call float @my_cos(i32 x0)
	mov x0,x0
	bl my_cos
	// store i32 x0, float* %20, align 4
	str x0,[sp,#128]
	// store float %20, float* %10, align 4
	ldr s7,[sp,#128]
	str s7,[sp,#48]
	// %21 = load i32, i32* @width, align 4
	adrp x15,width
	add x15,x15,:lo12:width
	ldr x15,[x15]
	str x15,[sp,#136]
	// %22 = sdiv i32 %21, 2
	ldr x15,[sp,#136]
	movz x4,#2
	sdiv w6,w15,w4
	str x6,[sp,#144]
	// store i32 %22, i32* %11, align 4
	ldr x4,[sp,#144]
	str x4,[sp,#56]
	// %23 = load i32, i32* @height, align 4
	adrp x4,height
	add x4,x4,:lo12:height
	ldr x4,[x4]
	str x4,[sp,#152]
	// %24 = sdiv i32 %23, 2
	ldr x4,[sp,#152]
	movz x15,#2
	sdiv w6,w4,w15
	str x6,[sp,#160]
	// store i32 %24, i32* %12, align 4
	ldr x4,[sp,#160]
	str x4,[sp,#64]
	// %25 = load i32, i32* %4, align 4
	ldr x4,[sp]
	str x4,[sp,#168]
	// %26 = load i32, i32* %11, align 4
	ldr x4,[sp,#56]
	str x4,[sp,#176]
	// %27 = sub nsw i32 %25, %26
	ldr x4,[sp,#168]
	ldr x15,[sp,#176]
	sub w6,w4,w15
	str x6,[sp,#184]
	// store i32 %27, i32* %13, align 4
	ldr x4,[sp,#184]
	str x4,[sp,#72]
	// %28 = load i32, i32* %5, align 4
	ldr x4,[sp,#8]
	str x4,[sp,#192]
	// %29 = load i32, i32* %12, align 4
	ldr x4,[sp,#64]
	str x4,[sp,#200]
	// %30 = sub nsw i32 %28, %29
	ldr x4,[sp,#192]
	ldr x15,[sp,#200]
	sub w6,w4,w15
	str x6,[sp,#208]
	// store i32 %30, i32* %14, align 4
	ldr x4,[sp,#208]
	str x4,[sp,#80]
	// %31 = load i32, i32* %13, align 4
	ldr x4,[sp,#72]
	str x4,[sp,#216]
	// %32 = load float, float* %10, align 4
	ldr s7,[sp,#48]
	str s7,[sp,#224]
	// %33 = sitofp i32 %31 to float
	ldr x15,[sp,#216]
	scvtf s7,w15
	str x15,[sp,#232]
	// %34 = fmul float %33, %32
	ldr s15,[sp,#232]
	ldr s10,[sp,#224]
	fmul s4,s15,s10
	str s4,[sp,#240]
	// %35 = load i32, i32* %14, align 4
	ldr x15,[sp,#80]
	str x15,[sp,#248]
	// %36 = load float, float* %9, align 4
	ldr s10,[sp,#40]
	str s10,[sp,#256]
	// %37 = sitofp i32 %35 to float
	ldr x4,[sp,#248]
	scvtf s10,w4
	str x4,[sp,#264]
	// %38 = fmul float %37, %36
	ldr s15,[sp,#264]
	ldr s4,[sp,#256]
	fmul s13,s15,s4
	str s13,[sp,#272]
	// %39 = fsub float %34, %38
	ldr s4,[sp,#240]
	ldr s15,[sp,#272]
	fsub s13,s4,s15
	str s13,[sp,#280]
	// %40 = load i32, i32* %11, align 4
	ldr x4,[sp,#56]
	str x4,[sp,#288]
	// %41 = sitofp i32 %40 to float
	ldr x4,[sp,#288]
	scvtf s4,w4
	str x4,[sp,#296]
	// %42 = fadd float %39, %41
	ldr s15,[sp,#280]
	ldr s13,[sp,#296]
	fadd s6,s15,s13
	str s6,[sp,#304]
	// %43 = fptosi float %42 to i32
	ldr s13,[sp,#304]
	fcvtzs s13,s13
	str s13,[sp,#312]
	// store i32 %43, i32* %15, align 4
	ldr x4,[sp,#312]
	str x4,[sp,#88]
	// %44 = load i32, i32* %13, align 4
	ldr x4,[sp,#72]
	str x4,[sp,#320]
	// %45 = load float, float* %9, align 4
	ldr s13,[sp,#40]
	str s13,[sp,#328]
	// %46 = sitofp i32 %44 to float
	ldr x6,[sp,#320]
	scvtf s13,w6
	str x6,[sp,#336]
	// %47 = fmul float %46, %45
	ldr s15,[sp,#336]
	ldr s6,[sp,#328]
	fmul sp,s15,s6
	str sp,[sp,#344]
	// %48 = load i32, i32* %14, align 4
	ldr x6,[sp,#80]
	str x6,[sp,#352]
	// %49 = load float, float* %10, align 4
	ldr s6,[sp,#48]
	str s6,[sp,#360]
	// %50 = sitofp i32 %48 to float
	ldr x4,[sp,#352]
	scvtf s6,w4
	str x4,[sp,#368]
	// %51 = fmul float %50, %49
	ldr s15,[sp,#368]
	ldr sp,[sp,#360]
	fmul sp,s15,sp
	str sp,[sp,#376]
	// %52 = fadd float %47, %51
	ldr s15,[sp,#344]
	ldr sp,[sp,#376]
	fadd sp,s15,sp
	str sp,[sp,#384]
	// %53 = load i32, i32* %12, align 4
	ldr x4,[sp,#64]
	str x4,[sp,#392]
	// %54 = sitofp i32 %53 to float
	ldr x4,[sp,#392]
	scvtf s15,w4
	str x4,[sp,#400]
	// %55 = fadd float %52, %54
	ldr sp,[sp,#384]
	ldr sp,[sp,#400]
	fadd sp,sp,sp
	str sp,[sp,#408]
	// %56 = fptosi float %55 to i32
	ldr sp,[sp,#408]
	fcvtzs sp,sp
	str sp,[sp,#416]
	// store i32 %56, i32* %16, align 4
	ldr x4,[sp,#416]
	str x4,[sp,#96]
	// br label %57
	b .L49
	// 
57:
.L49:
	// %58 = load i32, i32* %15, align 4
	ldr x4,[sp,#88]
	str x4,[sp,#424]
	// %59 = icmp slt i32 %58, 0
	ldr x4,[sp,#424]
	movz x11,#0
	cmp w4,w11
	cset x3,lt
	str x3,[sp,#432]
	// %60 = icmp ne i1 %59, 0
	ldr x3,[sp,#432]
	movz x4,#0
	cmp w3,w4
	cset x11,ne
	str x11,[sp,#440]
	// br i1 %60,  label %66,   label %61
	ldr x3,[sp,#440]
	cmp x3,#0
	b.ne .L51
	b .L50
	// 
61:
.L50:
	// %62 = load i32, i32* %15, align 4
	ldr x3,[sp,#88]
	str x3,[sp,#448]
	// %63 = load i32, i32* @width, align 4
	adrp x3,width
	add x3,x3,:lo12:width
	ldr x3,[x3]
	str x3,[sp,#456]
	// %64 = icmp sge i32 %62, %63
	ldr x3,[sp,#448]
	ldr x4,[sp,#456]
	cmp w3,w4
	cset x11,ge
	str x11,[sp,#464]
	// %65 = icmp ne i1 %64, 0
	ldr x3,[sp,#464]
	movz x4,#0
	cmp w3,w4
	cset x11,ne
	str x11,[sp,#472]
	// br i1 %65,  label %66,   label %67
	ldr x3,[sp,#472]
	cmp x3,#0
	b.ne .L51
	b .L52
	// 
66:
.L51:
	// store i32 1, i32* %8, align 4
	movz x3,#1
	str x3,[sp,#32]
	// br label %68
	b .L53
	// 
67:
.L52:
	// store i32 0, i32* %8, align 4
	movz x3,#0
	str x3,[sp,#32]
	// br label %68
	b .L53
	// 
68:
.L53:
	// %69 = load i32, i32* %8, align 4
	ldr x3,[sp,#32]
	str x3,[sp,#480]
	// %70 = icmp ne i32 %69, 0
	ldr x3,[sp,#480]
	movz x11,#0
	cmp w3,w11
	cset x10,ne
	str x10,[sp,#488]
	// br i1 %70,  label %75,   label %71
	ldr x3,[sp,#488]
	cmp x3,#0
	b.ne .L55
	b .L54
	// 
71:
.L54:
	// %72 = load i32, i32* %16, align 4
	ldr x3,[sp,#96]
	str x3,[sp,#496]
	// %73 = icmp slt i32 %72, 0
	ldr x3,[sp,#496]
	movz x11,#0
	cmp w3,w11
	cset x10,lt
	str x10,[sp,#504]
	// %74 = icmp ne i1 %73, 0
	ldr x3,[sp,#504]
	movz x10,#0
	cmp w3,w10
	cset x11,ne
	str x11,[sp,#512]
	// br i1 %74,  label %75,   label %76
	ldr x3,[sp,#512]
	cmp x3,#0
	b.ne .L55
	b .L56
	// 
75:
.L55:
	// store i32 1, i32* %8, align 4
	movz x3,#1
	str x3,[sp,#32]
	// br label %77
	b .L57
	// 
76:
.L56:
	// store i32 0, i32* %8, align 4
	movz x3,#0
	str x3,[sp,#32]
	// br label %77
	b .L57
	// 
77:
.L57:
	// %78 = load i32, i32* %8, align 4
	ldr x3,[sp,#32]
	str x3,[sp,#520]
	// %79 = icmp ne i32 %78, 0
	ldr x3,[sp,#520]
	movz x11,#0
	cmp w3,w11
	cset x10,ne
	str x10,[sp,#528]
	// br i1 %79,  label %85,   label %80
	ldr x3,[sp,#528]
	cmp x3,#0
	b.ne .L59
	b .L58
	// 
80:
.L58:
	// %81 = load i32, i32* %16, align 4
	ldr x3,[sp,#96]
	str x3,[sp,#536]
	// %82 = load i32, i32* @height, align 4
	adrp x3,height
	add x3,x3,:lo12:height
	ldr x3,[x3]
	str x3,[sp,#544]
	// %83 = icmp sge i32 %81, %82
	ldr x3,[sp,#536]
	ldr x10,[sp,#544]
	cmp w3,w10
	cset x11,ge
	str x11,[sp,#552]
	// %84 = icmp ne i1 %83, 0
	ldr x3,[sp,#552]
	movz x10,#0
	cmp w3,w10
	cset x11,ne
	str x11,[sp,#560]
	// br i1 %84,  label %85,   label %86
	ldr x3,[sp,#560]
	cmp x3,#0
	b.ne .L59
	b .L60
	// 
85:
.L59:
	// store i32 1, i32* %8, align 4
	movz x3,#1
	str x3,[sp,#32]
	// br label %87
	b .L61
	// 
86:
.L60:
	// store i32 0, i32* %8, align 4
	movz x3,#0
	str x3,[sp,#32]
	// br label %87
	b .L61
	// 
87:
.L61:
	// %88 = load i32, i32* %8, align 4
	ldr x3,[sp,#32]
	str x3,[sp,#568]
	// %89 = icmp ne i32 %88, 0
	ldr x3,[sp,#568]
	movz x11,#0
	cmp w3,w11
	cset x7,ne
	str x7,[sp,#576]
	// br i1 %89,  label %90,   label %91
	ldr x3,[sp,#576]
	cmp x3,#0
	b.ne .L62
	b .L63
	// 
90:
.L62:
	// store i32 0, i32* %7, align 4
	movz x3,#0
	str x3,[sp,#24]
	// br label %101
	b .L64
	// 
91:
.L63:
	// %92 = load i32, i32* %16, align 4
	ldr x3,[sp,#96]
	str x3,[sp,#584]
	// %93 = load i32, i32* @width, align 4
	adrp x3,width
	add x3,x3,:lo12:width
	ldr x3,[x3]
	str x3,[sp,#592]
	// %94 = mul nsw i32 %92, %93
	ldr x3,[sp,#584]
	ldr x9,[sp,#592]
	mul w5,w3,w9
	str x5,[sp,#600]
	// %95 = load i32, i32* %15, align 4
	ldr x3,[sp,#88]
	str x3,[sp,#608]
	// %96 = add nsw i32 %94, %95
	ldr x3,[sp,#600]
	ldr x9,[sp,#608]
	add w4,w3,w9
	str x4,[sp,#616]
	// %97 = add nsw i32 0, %96
	movz x3,#0
	ldr x4,[sp,#616]
	add w9,w3,w4
	str x9,[sp,#624]
	// %98 = bitcast [1048576 x i32]* @image to i32*
	// %99 = getelementptr inbounds i32, i32* %98, i32 %97
	adrp x3,image
	add x3,x3,:lo12:image
	ldr x4,[sp,#624]
	lsl x4,x4,#2
	add x3,x3,x4
	str x3,[sp,#640]
	// %100 = load i32, i32* %99, align 4
	ldr x3,[sp,#640]
	ldr x3,[x3, #0]
	str x3,[sp,#648]
	// store i32 %100, i32* %7, align 4
	ldr x3,[sp,#648]
	str x3,[sp,#24]
	// br label %101
	b .L64
	// 
101:
.L64:
	// %102 = load i32, i32* %7, align 4
	ldr x3,[sp,#24]
	str x3,[sp,#656]
	// ret i32 %102
	ldr x0,[sp,#656]
	mov sp,x29
	ldp x29,x30,[sp], #16
	ret

.align 1
.global write_pgm
.type write_pgm, %function
write_pgm:
//	@ rad:%2:[sp,#0]
//	@ %3:[sp,#8]
//	@ %4:[sp,#16]
//	@ y:%5:[sp,#24]
//	@ x:%6:[sp,#32]
//	@ %7:[sp,#40]
//	@ %8:[sp,#48]
//	@ %10:[sp,#56]
//	@ %11:[sp,#64]
//	@ %12:[sp,#72]
//	@ %13:[sp,#80]
//	@ %16:[sp,#88]
//	@ %17:[sp,#96]
//	@ %18:[sp,#104]
//	@ %19:[sp,#112]
//	@ %21:[sp,#120]
//	@ %22:[sp,#128]
//	@ %23:[sp,#136]
//	@ %24:[sp,#144]
//	@ %25:[sp,#152]
//	@ %26:[sp,#160]
//	@ %28:[sp,#168]
//	@ %29:[sp,#176]
//	@ %32:[sp,#184]
	stp x29,x30,[sp, #-16]!
	mov x29,sp
	sub sp,sp,192
	// store float %0, float* %2, align 4
	str s0,[sp]
	// store i32 80, i32* x0, align 4
	movz x0,#80
	// call void  @putch(i32 x0)
	mov x0,x0
	bl putch
	// store i32 50, i32* x0, align 4
	movz x0,#50
	// call void  @putch(i32 x0)
	mov x0,x0
	bl putch
	// store i32 10, i32* x0, align 4
	movz x0,#10
	// call void  @putch(i32 x0)
	mov x0,x0
	bl putch
	// %7 = load i32, i32* @width, align 4
	adrp x3,width
	add x3,x3,:lo12:width
	ldr x3,[x3]
	str x3,[sp,#40]
	// store i32 %7, i32* x0, align 4
	ldr x0,[sp,#40]
	// call void  @putint(i32 x0)
	mov x0,x0
	bl putint
	// store i32 32, i32* x0, align 4
	movz x0,#32
	// call void  @putch(i32 x0)
	mov x0,x0
	bl putch
	// %8 = load i32, i32* @height, align 4
	adrp x3,height
	add x3,x3,:lo12:height
	ldr x3,[x3]
	str x3,[sp,#48]
	// store i32 %8, i32* x0, align 4
	ldr x0,[sp,#48]
	// call void  @putint(i32 x0)
	mov x0,x0
	bl putint
	// store i32 32, i32* x0, align 4
	movz x0,#32
	// call void  @putch(i32 x0)
	mov x0,x0
	bl putch
	// store i32 255, i32* x0, align 4
	movz x0,#255
	// call void  @putint(i32 x0)
	mov x0,x0
	bl putint
	// store i32 10, i32* x0, align 4
	movz x0,#10
	// call void  @putch(i32 x0)
	mov x0,x0
	bl putch
	// store i32 0, i32* %5, align 4
	movz x3,#0
	str x3,[sp,#24]
	// br label %9
	b .L65
	// 
9:
.L65:
	// %10 = load i32, i32* %5, align 4
	ldr x3,[sp,#24]
	str x3,[sp,#56]
	// %11 = load i32, i32* @height, align 4
	adrp x3,height
	add x3,x3,:lo12:height
	ldr x3,[x3]
	str x3,[sp,#64]
	// %12 = icmp slt i32 %10, %11
	ldr x3,[sp,#56]
	ldr x9,[sp,#64]
	cmp w3,w9
	cset x10,lt
	str x10,[sp,#72]
	// %13 = icmp ne i1 %12, 0
	ldr x3,[sp,#72]
	movz x9,#0
	cmp w3,w9
	cset x10,ne
	str x10,[sp,#80]
	// br i1 %13,  label %14,   label %30
	ldr x3,[sp,#80]
	cmp x3,#0
	b.ne .L66
	b .L70
	// 
14:
.L66:
	// store i32 0, i32* %6, align 4
	movz x3,#0
	str x3,[sp,#32]
	// br label %15
	b .L67
	// 
15:
.L67:
	// %16 = load i32, i32* %6, align 4
	ldr x3,[sp,#32]
	str x3,[sp,#88]
	// %17 = load i32, i32* @width, align 4
	adrp x3,width
	add x3,x3,:lo12:width
	ldr x3,[x3]
	str x3,[sp,#96]
	// %18 = icmp slt i32 %16, %17
	ldr x3,[sp,#88]
	ldr x10,[sp,#96]
	cmp w3,w10
	cset x9,lt
	str x9,[sp,#104]
	// %19 = icmp ne i1 %18, 0
	ldr x3,[sp,#104]
	movz x9,#0
	cmp w3,w9
	cset x10,ne
	str x10,[sp,#112]
	// br i1 %19,  label %20,   label %27
	ldr x3,[sp,#112]
	cmp x3,#0
	b.ne .L68
	b .L69
	// 
20:
.L68:
	// %21 = load i32, i32* %6, align 4
	ldr x3,[sp,#32]
	str x3,[sp,#120]
	// %22 = load i32, i32* %5, align 4
	ldr x3,[sp,#24]
	str x3,[sp,#128]
	// %23 = load float, float* %2, align 4
	ldr sp,[sp]
	str sp,[sp,#136]
	// store i32 %21, i32* x0, align 4
	ldr x0,[sp,#120]
	// store i32 %22, i32* x1, align 4
	ldr x1,[sp,#128]
	// store float %23, i32* x2, align 4
	ldr s2,[sp,#136]
	// %24 = call i32 @rotate(i32 x0, i32 x1, i32 x2)
	mov x0,x0
	mov x1,x1
	mov x2,x2
	bl rotate
	// store i32 x0, i32* %24, align 4
	str x0,[sp,#144]
	// store i32 %24, i32* x0, align 4
	ldr x0,[sp,#144]
	// call void  @putint(i32 x0)
	mov x0,x0
	bl putint
	// store i32 32, i32* x0, align 4
	movz x0,#32
	// call void  @putch(i32 x0)
	mov x0,x0
	bl putch
	// %25 = load i32, i32* %6, align 4
	ldr x9,[sp,#32]
	str x9,[sp,#152]
	// %26 = add nsw i32 %25, 1
	ldr x9,[sp,#152]
	movz x3,#1
	add w10,w9,w3
	str x10,[sp,#160]
	// store i32 %26, i32* %6, align 4
	ldr x3,[sp,#160]
	str x3,[sp,#32]
	// br label %15
	b .L67
	// 
27:
.L69:
	// store i32 10, i32* x0, align 4
	movz x0,#10
	// call void  @putch(i32 x0)
	mov x0,x0
	bl putch
	// %28 = load i32, i32* %5, align 4
	ldr x3,[sp,#24]
	str x3,[sp,#168]
	// %29 = add nsw i32 %28, 1
	ldr x3,[sp,#168]
	movz x9,#1
	add w10,w3,w9
	str x10,[sp,#176]
	// store i32 %29, i32* %5, align 4
	ldr x3,[sp,#176]
	str x3,[sp,#24]
	// br label %9
	b .L65
	// 
30:
.L70:
	// br label %31
	b .L71
	// 
31:
.L71:
	// %32 = load i32, i32* %3, align 4
	ldr x3,[sp,#8]
	str x3,[sp,#184]
	// ret void
	mov sp,x29
	ldp x29,x30,[sp], #16
	ret

.align 1
.global main
.type main, %function
main:
//	@ %1:[sp,#0]
//	@ %2:[sp,#8]
//	@ rad:%3:[sp,#16]
//	@ %4:[sp,#24]
//	@ %5:[sp,#32]
//	@ %7:[sp,#40]
//	@ %8:[sp,#48]
//	@ %9:[sp,#56]
//	@ %11:[sp,#64]
//	@ %13:[sp,#72]
//	@ %15:[sp,#80]
	stp x29,x30,[sp, #-16]!
	mov x29,sp
	sub sp,sp,96
	// store i32 0, i32* %1, align 4
	movz x3,#0
	str x3,[sp]
	// %4 = call float (...) @getfloat()
	bl getfloat
	// store i32 x0, float* %4, align 4
	str x0,[sp,#24]
	// store float %4, float* %3, align 4
	ldr sp,[sp,#24]
	str sp,[sp,#16]
	// %5 = call i32 (...) @getch()
	bl getch
	// store i32 x0, i32* %5, align 4
	str x0,[sp,#32]
	// br label %6
	b .L72
	// 
6:
.L72:
	// %7 = call i32 @read_image()
	bl read_image
	// store i32 x0, i32* %7, align 4
	str x0,[sp,#40]
	// %8 = icmp slt i32 %7, 0
	ldr x3,[sp,#40]
	movz x9,#0
	cmp w3,w9
	cset x10,lt
	str x10,[sp,#48]
	// %9 = icmp ne i1 %8, 0
	ldr x3,[sp,#48]
	movz x9,#0
	cmp w3,w9
	cset x10,ne
	str x10,[sp,#56]
	// br i1 %9,  label %10,   label %12
	ldr x3,[sp,#56]
	cmp x3,#0
	b.ne .L73
	b .L74
	// 
10:
.L73:
	// %11 = sub nsw i32 0, 1
	movz x3,#0
	movz x9,#1
	sub w10,w3,w9
	str x10,[sp,#64]
	// store i32 %11, i32* %1, align 4
	ldr x3,[sp,#64]
	str x3,[sp]
	// br label %14
	b .L75
	// 
12:
.L74:
	// %13 = load float, float* %3, align 4
	ldr sp,[sp,#16]
	str sp,[sp,#72]
	// store float %13, i32* x0, align 4
	ldr s0,[sp,#72]
	// call void @write_pgm(i32 x0)
	mov x0,x0
	bl write_pgm
	// store i32 0, i32* %1, align 4
	movz x10,#0
	str x10,[sp]
	// br label %14
	b .L75
	// 
14:
.L75:
	// %15 = load i32, i32* %1, align 4
	ldr x10,[sp]
	str x10,[sp,#80]
	// ret i32 %15
	ldr x0,[sp,#80]
	mov sp,x29
	ldp x29,x30,[sp], #16
	ret
