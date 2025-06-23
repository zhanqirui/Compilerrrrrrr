	.arch armv8-a
	.text
.text

.align 1
.global MAX
.type MAX, %function
MAX:
//	@ a:%3:[sp,#0]
//	@ b:%4:[sp,#8]
//	@ %5:[sp,#16]
//	@ %6:[sp,#24]
//	@ %8:[sp,#32]
//	@ %9:[sp,#40]
//	@ %10:[sp,#48]
//	@ %11:[sp,#56]
//	@ %13:[sp,#64]
//	@ %15:[sp,#72]
//	@ %16:[sp,#80]
//	@ %17:[sp,#88]
//	@ %18:[sp,#96]
//	@ %20:[sp,#104]
//	@ %22:[sp,#112]
//	@ %26:[sp,#120]
	stp x29,x30,[sp, #-16]!
	mov x29,sp
	sub sp,sp,128
	// store i32 0, i32* %5, align 4
	mov x2,#0
	str x2,[sp,#16]
	// store i32 %0, i32* %3, align 4
	str x0,[sp]
	// store i32 %1, i32* %4, align 4
	str x1,[sp,#8]
	// br label %7
	b .L0
	// 
7:
.L0:
	// %8 = load i32, i32* %3, align 4
	ldr x2,[sp]
	str x2,[sp,#32]
	// %9 = load i32, i32* %4, align 4
	ldr x2,[sp,#8]
	str x2,[sp,#40]
	// %10 = icmp eq i32 %8, %9
	ldr x2,[sp,#32]
	ldr x6,[sp,#40]
	cmp w2,w6
	cset x7,eq
	str x7,[sp,#48]
	// %11 = icmp ne i1 %10, 0
	ldr x2,[sp,#48]
	mov x6,#0
	cmp w2,w6
	cset x7,ne
	str x7,[sp,#56]
	// br i1 %11,  label %12,   label %14
	ldr x2,[sp,#56]
	cmp x2,#0
	b.ne .L1
	b .L2
	// 
12:
.L1:
	// %13 = load i32, i32* %3, align 4
	ldr x2,[sp]
	str x2,[sp,#64]
	// store i32 %13, i32* %5, align 4
	ldr x2,[sp,#64]
	str x2,[sp,#16]
	// br label %25
	b .L7
	// 
14:
.L2:
	// %15 = load i32, i32* %3, align 4
	ldr x2,[sp]
	str x2,[sp,#72]
	// %16 = load i32, i32* %4, align 4
	ldr x2,[sp,#8]
	str x2,[sp,#80]
	// %17 = icmp sgt i32 %15, %16
	ldr x2,[sp,#72]
	ldr x9,[sp,#80]
	cmp w2,w9
	cset x10,gt
	str x10,[sp,#88]
	// %18 = icmp ne i1 %17, 0
	ldr x2,[sp,#88]
	mov x9,#0
	cmp w2,w9
	cset x10,ne
	str x10,[sp,#96]
	// br i1 %18,  label %19,   label %21
	ldr x2,[sp,#96]
	cmp x2,#0
	b.ne .L3
	b .L4
	// 
19:
.L3:
	// %20 = load i32, i32* %3, align 4
	ldr x2,[sp]
	str x2,[sp,#104]
	// store i32 %20, i32* %5, align 4
	ldr x2,[sp,#104]
	str x2,[sp,#16]
	// br label %25
	b .L7
	// 
21:
.L4:
	// %22 = load i32, i32* %4, align 4
	ldr x2,[sp,#8]
	str x2,[sp,#112]
	// store i32 %22, i32* %5, align 4
	ldr x2,[sp,#112]
	str x2,[sp,#16]
	// br label %25
	b .L7
	// 
23:

	// br label %24
	b .L6
	// 
24:
.L6:
	// br label %25
	b .L7
	// 
25:
.L7:
	// %26 = load i32, i32* %5, align 4
	ldr x2,[sp,#16]
	str x2,[sp,#120]
	// ret i32 %26
	ldr x0,[sp,#120]
	mov sp,x29
	ldp x29,x30,[sp], #16
	ret

.align 1
.global max_sum_nonadjacent
.type max_sum_nonadjacent, %function
max_sum_nonadjacent:
//	@ arr:%3:[sp,#0]
//	@ n:%4:[sp,#8]
//	@ %5:[sp,#16]
//	@ %6:[sp,#24]
//	@ temp:%7:[sp,#32]
//	@ i:%8:[sp,#160]
//	@ %9:[sp,#168]
//	@ %10:[sp,#176]
//	@ %11:[sp,#184]
//	@ %12:[sp,#192]
//	@ %13:[sp,#200]
//	@ %14:[sp,#208]
//	@ %15:[sp,#216]
//	@ %16:[sp,#224]
//	@ %17:[sp,#232]
//	@ %18:[sp,#240]
//	@ %19:[sp,#248]
//	@ %20:[sp,#256]
//	@ %21:[sp,#264]
//	@ %22:[sp,#272]
//	@ %23:[sp,#280]
//	@ %24:[sp,#288]
//	@ %25:[sp,#296]
//	@ %26:[sp,#304]
//	@ %27:[sp,#312]
//	@ %28:[sp,#320]
//	@ %29:[sp,#328]
//	@ %30:[sp,#336]
//	@ %31:[sp,#344]
//	@ %33:[sp,#352]
//	@ %34:[sp,#360]
//	@ %35:[sp,#368]
//	@ %36:[sp,#376]
//	@ %38:[sp,#384]
//	@ %39:[sp,#392]
//	@ %40:[sp,#400]
//	@ %41:[sp,#408]
//	@ %42:[sp,#416]
//	@ %43:[sp,#424]
//	@ %44:[sp,#432]
//	@ %45:[sp,#440]
//	@ %46:[sp,#448]
//	@ %47:[sp,#456]
//	@ %48:[sp,#464]
//	@ %49:[sp,#472]
//	@ %50:[sp,#480]
//	@ %51:[sp,#488]
//	@ %52:[sp,#496]
//	@ %53:[sp,#504]
//	@ %54:[sp,#512]
//	@ %55:[sp,#520]
//	@ %56:[sp,#528]
//	@ %57:[sp,#536]
//	@ %58:[sp,#544]
//	@ %59:[sp,#552]
//	@ %60:[sp,#560]
//	@ %61:[sp,#568]
//	@ %62:[sp,#576]
//	@ %63:[sp,#584]
//	@ %65:[sp,#592]
//	@ %66:[sp,#600]
//	@ %67:[sp,#608]
//	@ %68:[sp,#616]
//	@ %69:[sp,#624]
//	@ %70:[sp,#632]
//	@ %72:[sp,#640]
	stp x29,x30,[sp, #-16]!
	mov x29,sp
	mov x2,#656
	sub sp,sp,x2
	// store i32 0, i32* %5, align 4
	mov x2,#0
	str x2,[sp,#16]
	// store i32* %0, i32**  %3, align 4
	str x0,[sp]
	// store i32 %1, i32* %4, align 4
	str x1,[sp,#8]
	// %9 = bitcast [16 x i32]* %7 to i8*
	// call void @llvm.memset.p0i8.i64(i8* align 16 %9, i8 0, i64 64, i1 false)
	add x2,sp,#32
	sub sp,sp,#32
	str x0,[sp, #0]
	str x1,[sp, #8]
	str x2,[sp, #16]
	str lr,[sp, #24]
	mov x0,x2
	mov w1,#0
	mov x2,#64
	bl memset
	ldr x0,[sp, #0]
	ldr x1,[sp, #8]
	ldr x2,[sp, #16]
	ldr lr,[sp, #24]
	add sp,sp,#32
	// %10 = add nsw i32 0, 0
	mov x2,#0
	mov x13,#0
	add w14,w2,w13
	str x14,[sp,#176]
	// %11 = load i32*, i32** %3, align 4
	add x2,sp,#0
	ldr x2,[x2]
	str x2,[sp,#184]
	// %12 = bitcast i32* %11 to i32*
	// %13 = getelementptr inbounds i32, i32* %12, i32 %10
	ldr x2,[sp,#184]
	ldr x14,[sp,#176]
	lsl x14,x14,#2
	add x2,x2,x14
	str x2,[sp,#200]
	// %14 = load i32, i32* %13, align 4
	ldr x2,[sp,#200]
	ldr x2,[x2, #0]
	str x2,[sp,#208]
	// %15 = add nsw i32 0, 0
	mov x2,#0
	mov x14,#0
	add w15,w2,w14
	str x15,[sp,#216]
	// %16 = bitcast [16 x i32]* %7 to i32*
	// %17 = getelementptr inbounds i32, i32* %16, i32 %15
	add x2,sp,#32
	ldr x14,[sp,#216]
	lsl x14,x14,#2
	add x2,x2,x14
	str x2,[sp,#232]
	// store i32 %14, i32*  %17, align 4
	ldr x2,[sp,#208]
	ldr x14,[sp,#232]
	str w2,[x14, #0]
	// %18 = add nsw i32 0, 0
	mov x2,#0
	mov x14,#0
	add w15,w2,w14
	str x15,[sp,#240]
	// %19 = load i32*, i32** %3, align 4
	add x2,sp,#0
	ldr x2,[x2]
	str x2,[sp,#248]
	// %20 = bitcast i32* %19 to i32*
	// %21 = getelementptr inbounds i32, i32* %20, i32 %18
	ldr x2,[sp,#248]
	ldr x15,[sp,#240]
	lsl x15,x15,#2
	add x2,x2,x15
	str x2,[sp,#264]
	// %22 = load i32, i32* %21, align 4
	ldr x2,[sp,#264]
	ldr x2,[x2, #0]
	str x2,[sp,#272]
	// %23 = add nsw i32 0, 1
	mov x2,#0
	mov x15,#1
	add w3,w2,w15
	str x3,[sp,#280]
	// %24 = load i32*, i32** %3, align 4
	add x2,sp,#0
	ldr x2,[x2]
	str x2,[sp,#288]
	// %25 = bitcast i32* %24 to i32*
	// %26 = getelementptr inbounds i32, i32* %25, i32 %23
	ldr x2,[sp,#288]
	ldr x15,[sp,#280]
	lsl x15,x15,#2
	add x2,x2,x15
	str x2,[sp,#304]
	// %27 = load i32, i32* %26, align 4
	ldr x2,[sp,#304]
	ldr x2,[x2, #0]
	str x2,[sp,#312]
	// store i32 %22, i32* x0, align 4
	ldr x0,[sp,#272]
	// store i32 %27, i32* x1, align 4
	ldr x1,[sp,#312]
	// %28 = call i32 @MAX(i32 x0, i32 x1)
	mov x0,x0
	mov x1,x1
	bl MAX
	// store i32 x0, i32* %28, align 4
	str x0,[sp,#320]
	// %29 = add nsw i32 0, 1
	mov x2,#0
	mov x15,#1
	add w4,w2,w15
	str x4,[sp,#328]
	// %30 = bitcast [16 x i32]* %7 to i32*
	// %31 = getelementptr inbounds i32, i32* %30, i32 %29
	add x2,sp,#32
	ldr x4,[sp,#328]
	lsl x4,x4,#2
	add x2,x2,x4
	str x2,[sp,#344]
	// store i32 %28, i32*  %31, align 4
	ldr x2,[sp,#320]
	ldr x4,[sp,#344]
	str w2,[x4, #0]
	// store i32 2, i32* %8, align 4
	mov x2,#2
	str x2,[sp,#160]
	// br label %32
	b .L8
	// 
32:
.L8:
	// %33 = load i32, i32* %8, align 4
	ldr x2,[sp,#160]
	str x2,[sp,#352]
	// %34 = load i32, i32* %4, align 4
	ldr x2,[sp,#8]
	str x2,[sp,#360]
	// %35 = icmp slt i32 %33, %34
	ldr x2,[sp,#352]
	ldr x6,[sp,#360]
	cmp w2,w6
	cset x7,lt
	str x7,[sp,#368]
	// %36 = icmp ne i1 %35, 0
	ldr x2,[sp,#368]
	mov x6,#0
	cmp w2,w6
	cset x7,ne
	str x7,[sp,#376]
	// br i1 %36,  label %37,   label %64
	ldr x2,[sp,#376]
	cmp x2,#0
	b.ne .L9
	b .L10
	// 
37:
.L9:
	// %38 = load i32, i32* %8, align 4
	ldr x2,[sp,#160]
	str x2,[sp,#384]
	// %39 = sub nsw i32 %38, 2
	ldr x2,[sp,#384]
	mov x7,#2
	sub w8,w2,w7
	str x8,[sp,#392]
	// %40 = add nsw i32 0, %39
	mov x2,#0
	ldr x7,[sp,#392]
	add w8,w2,w7
	str x8,[sp,#400]
	// %41 = bitcast [16 x i32]* %7 to i32*
	// %42 = getelementptr inbounds i32, i32* %41, i32 %40
	add x2,sp,#32
	ldr x7,[sp,#400]
	lsl x7,x7,#2
	add x2,x2,x7
	str x2,[sp,#416]
	// %43 = load i32, i32* %42, align 4
	ldr x2,[sp,#416]
	ldr x2,[x2, #0]
	str x2,[sp,#424]
	// %44 = load i32, i32* %8, align 4
	ldr x2,[sp,#160]
	str x2,[sp,#432]
	// %45 = add nsw i32 0, %44
	mov x2,#0
	ldr x8,[sp,#432]
	add w9,w2,w8
	str x9,[sp,#440]
	// %46 = load i32*, i32** %3, align 4
	add x2,sp,#0
	ldr x2,[x2]
	str x2,[sp,#448]
	// %47 = bitcast i32* %46 to i32*
	// %48 = getelementptr inbounds i32, i32* %47, i32 %45
	ldr x2,[sp,#448]
	ldr x9,[sp,#440]
	lsl x9,x9,#2
	add x2,x2,x9
	str x2,[sp,#464]
	// %49 = load i32, i32* %48, align 4
	ldr x2,[sp,#464]
	ldr x2,[x2, #0]
	str x2,[sp,#472]
	// %50 = add nsw i32 %43, %49
	ldr x2,[sp,#424]
	ldr x9,[sp,#472]
	add w10,w2,w9
	str x10,[sp,#480]
	// %51 = load i32, i32* %8, align 4
	ldr x2,[sp,#160]
	str x2,[sp,#488]
	// %52 = sub nsw i32 %51, 1
	ldr x2,[sp,#488]
	mov x10,#1
	sub w11,w2,w10
	str x11,[sp,#496]
	// %53 = add nsw i32 0, %52
	mov x2,#0
	ldr x10,[sp,#496]
	add w11,w2,w10
	str x11,[sp,#504]
	// %54 = bitcast [16 x i32]* %7 to i32*
	// %55 = getelementptr inbounds i32, i32* %54, i32 %53
	add x2,sp,#32
	ldr x10,[sp,#504]
	lsl x10,x10,#2
	add x2,x2,x10
	str x2,[sp,#520]
	// %56 = load i32, i32* %55, align 4
	ldr x2,[sp,#520]
	ldr x2,[x2, #0]
	str x2,[sp,#528]
	// store i32 %50, i32* x0, align 4
	ldr x0,[sp,#480]
	// store i32 %56, i32* x1, align 4
	ldr x1,[sp,#528]
	// %57 = call i32 @MAX(i32 x0, i32 x1)
	mov x0,x0
	mov x1,x1
	bl MAX
	// store i32 x0, i32* %57, align 4
	str x0,[sp,#536]
	// %58 = load i32, i32* %8, align 4
	ldr x2,[sp,#160]
	str x2,[sp,#544]
	// %59 = add nsw i32 0, %58
	mov x2,#0
	ldr x11,[sp,#544]
	add w12,w2,w11
	str x12,[sp,#552]
	// %60 = bitcast [16 x i32]* %7 to i32*
	// %61 = getelementptr inbounds i32, i32* %60, i32 %59
	add x2,sp,#32
	ldr x11,[sp,#552]
	lsl x11,x11,#2
	add x2,x2,x11
	str x2,[sp,#568]
	// store i32 %57, i32*  %61, align 4
	ldr x2,[sp,#536]
	ldr x11,[sp,#568]
	str w2,[x11, #0]
	// %62 = load i32, i32* %8, align 4
	ldr x2,[sp,#160]
	str x2,[sp,#576]
	// %63 = add nsw i32 %62, 1
	ldr x2,[sp,#576]
	mov x12,#1
	add w13,w2,w12
	str x13,[sp,#584]
	// store i32 %63, i32* %8, align 4
	ldr x2,[sp,#584]
	str x2,[sp,#160]
	// br label %32
	b .L8
	// 
64:
.L10:
	// %65 = load i32, i32* %4, align 4
	ldr x2,[sp,#8]
	str x2,[sp,#592]
	// %66 = sub nsw i32 %65, 1
	ldr x2,[sp,#592]
	mov x13,#1
	sub w14,w2,w13
	str x14,[sp,#600]
	// %67 = add nsw i32 0, %66
	mov x2,#0
	ldr x13,[sp,#600]
	add w14,w2,w13
	str x14,[sp,#608]
	// %68 = bitcast [16 x i32]* %7 to i32*
	// %69 = getelementptr inbounds i32, i32* %68, i32 %67
	add x2,sp,#32
	ldr x13,[sp,#608]
	lsl x13,x13,#2
	add x2,x2,x13
	str x2,[sp,#624]
	// %70 = load i32, i32* %69, align 4
	ldr x2,[sp,#624]
	ldr x2,[x2, #0]
	str x2,[sp,#632]
	// store i32 %70, i32* %5, align 4
	ldr x2,[sp,#632]
	str x2,[sp,#16]
	// br label %71
	b .L11
	// 
71:
.L11:
	// %72 = load i32, i32* %5, align 4
	ldr x2,[sp,#16]
	str x2,[sp,#640]
	// ret i32 %72
	ldr x0,[sp,#640]
	mov sp,x29
	ldp x29,x30,[sp], #16
	ret

.align 1
.global longest_common_subseq
.type longest_common_subseq, %function
longest_common_subseq:
//	@ arr1:%5:[sp,#0]
//	@ len1:%6:[sp,#8]
//	@ arr2:%7:[sp,#16]
//	@ len2:%8:[sp,#24]
//	@ %9:[sp,#32]
//	@ %10:[sp,#40]
//	@ p:%11:[sp,#48]
//	@ i:%12:[sp,#2096]
//	@ j:%13:[sp,#2104]
//	@ %14:[sp,#2112]
//	@ %16:[sp,#2120]
//	@ %17:[sp,#2128]
//	@ %18:[sp,#2136]
//	@ %19:[sp,#2144]
//	@ %22:[sp,#2152]
//	@ %23:[sp,#2160]
//	@ %24:[sp,#2168]
//	@ %25:[sp,#2176]
//	@ %28:[sp,#2184]
//	@ %29:[sp,#2192]
//	@ %30:[sp,#2200]
//	@ %31:[sp,#2208]
//	@ %32:[sp,#2216]
//	@ %33:[sp,#2224]
//	@ %34:[sp,#2232]
//	@ %35:[sp,#2240]
//	@ %36:[sp,#2248]
//	@ %37:[sp,#2256]
//	@ %38:[sp,#2264]
//	@ %39:[sp,#2272]
//	@ %40:[sp,#2280]
//	@ %41:[sp,#2288]
//	@ %42:[sp,#2296]
//	@ %43:[sp,#2304]
//	@ %45:[sp,#2312]
//	@ %46:[sp,#2320]
//	@ %47:[sp,#2328]
//	@ %48:[sp,#2336]
//	@ %49:[sp,#2344]
//	@ %50:[sp,#2352]
//	@ %51:[sp,#2360]
//	@ %52:[sp,#2368]
//	@ %53:[sp,#2376]
//	@ %54:[sp,#2384]
//	@ %55:[sp,#2392]
//	@ %56:[sp,#2400]
//	@ %57:[sp,#2408]
//	@ %58:[sp,#2416]
//	@ %59:[sp,#2424]
//	@ %60:[sp,#2432]
//	@ %62:[sp,#2440]
//	@ %63:[sp,#2448]
//	@ %64:[sp,#2456]
//	@ %65:[sp,#2464]
//	@ %66:[sp,#2472]
//	@ %67:[sp,#2480]
//	@ %68:[sp,#2488]
//	@ %69:[sp,#2496]
//	@ %70:[sp,#2504]
//	@ %71:[sp,#2512]
//	@ %72:[sp,#2520]
//	@ %73:[sp,#2528]
//	@ %74:[sp,#2536]
//	@ %75:[sp,#2544]
//	@ %76:[sp,#2552]
//	@ %77:[sp,#2560]
//	@ %78:[sp,#2568]
//	@ %79:[sp,#2576]
//	@ %80:[sp,#2584]
//	@ %81:[sp,#2592]
//	@ %82:[sp,#2600]
//	@ %83:[sp,#2608]
//	@ %84:[sp,#2616]
//	@ %86:[sp,#2624]
//	@ %87:[sp,#2632]
//	@ %89:[sp,#2640]
//	@ %90:[sp,#2648]
//	@ %92:[sp,#2656]
//	@ %93:[sp,#2664]
//	@ %94:[sp,#2672]
//	@ %95:[sp,#2680]
//	@ %96:[sp,#2688]
//	@ %97:[sp,#2696]
//	@ %98:[sp,#2704]
//	@ %99:[sp,#2712]
//	@ %100:[sp,#2720]
//	@ %102:[sp,#2728]
	stp x29,x30,[sp, #-16]!
	mov x29,sp
	mov x3,#2736
	sub sp,sp,x3
	// store i32 0, i32* %9, align 4
	mov x3,#0
	str x3,[sp,#32]
	// store i32* %0, i32**  %5, align 4
	str x0,[sp]
	// store i32 %1, i32* %6, align 4
	str x1,[sp,#8]
	// store i32* %2, i32**  %7, align 4
	str x2,[sp,#16]
	// store i32 %3, i32* %8, align 4
	str x3,[sp,#24]
	// %14 = bitcast [16 x [16 x i32]]* %11 to i8*
	// call void @llvm.memset.p0i8.i64(i8* align 16 %14, i8 0, i64 1024, i1 false)
	add x3,sp,#48
	sub sp,sp,#32
	str x0,[sp, #0]
	str x1,[sp, #8]
	str x2,[sp, #16]
	str lr,[sp, #24]
	mov x0,x3
	mov w1,#0
	mov x2,#1024
	bl memset
	ldr x0,[sp, #0]
	ldr x1,[sp, #8]
	ldr x2,[sp, #16]
	ldr lr,[sp, #24]
	add sp,sp,#32
	// store i32 1, i32* %12, align 4
	mov x3,#1
	str x3,[sp,#2096]
	// br label %15
	b .L12
	// 
15:
.L12:
	// %16 = load i32, i32* %12, align 4
	ldr x3,[sp,#2096]
	str x3,[sp,#2120]
	// %17 = load i32, i32* %6, align 4
	ldr x3,[sp,#8]
	str x3,[sp,#2128]
	// %18 = icmp sle i32 %16, %17
	ldr x3,[sp,#2120]
	ldr x7,[sp,#2128]
	cmp w3,w7
	cset x8,le
	str x8,[sp,#2136]
	// %19 = icmp ne i1 %18, 0
	ldr x3,[sp,#2136]
	mov x7,#0
	cmp w3,w7
	cset x8,ne
	str x8,[sp,#2144]
	// br i1 %19,  label %20,   label %91
	ldr x3,[sp,#2144]
	cmp x3,#0
	b.ne .L13
	b .L21
	// 
20:
.L13:
	// store i32 1, i32* %13, align 4
	mov x3,#1
	str x3,[sp,#2104]
	// br label %21
	b .L14
	// 
21:
.L14:
	// %22 = load i32, i32* %13, align 4
	ldr x3,[sp,#2104]
	str x3,[sp,#2152]
	// %23 = load i32, i32* %8, align 4
	ldr x3,[sp,#24]
	str x3,[sp,#2160]
	// %24 = icmp sle i32 %22, %23
	ldr x3,[sp,#2152]
	ldr x10,[sp,#2160]
	cmp w3,w10
	cset x11,le
	str x11,[sp,#2168]
	// %25 = icmp ne i1 %24, 0
	ldr x3,[sp,#2168]
	mov x10,#0
	cmp w3,w10
	cset x11,ne
	str x11,[sp,#2176]
	// br i1 %25,  label %26,   label %88
	ldr x3,[sp,#2176]
	cmp x3,#0
	b.ne .L15
	b .L20
	// 
26:
.L15:
	// br label %27
	b .L16
	// 
27:
.L16:
	// %28 = load i32, i32* %12, align 4
	ldr x3,[sp,#2096]
	str x3,[sp,#2184]
	// %29 = sub nsw i32 %28, 1
	ldr x3,[sp,#2184]
	mov x11,#1
	sub w12,w3,w11
	str x12,[sp,#2192]
	// %30 = add nsw i32 0, %29
	mov x3,#0
	ldr x11,[sp,#2192]
	add w12,w3,w11
	str x12,[sp,#2200]
	// %31 = load i32*, i32** %5, align 4
	add x3,sp,#0
	ldr x3,[x3]
	str x3,[sp,#2208]
	// %32 = bitcast i32* %31 to i32*
	// %33 = getelementptr inbounds i32, i32* %32, i32 %30
	ldr x3,[sp,#2208]
	ldr x12,[sp,#2200]
	lsl x12,x12,#2
	add x3,x3,x12
	str x3,[sp,#2224]
	// %34 = load i32, i32* %33, align 4
	ldr x3,[sp,#2224]
	ldr x3,[x3, #0]
	str x3,[sp,#2232]
	// %35 = load i32, i32* %13, align 4
	ldr x3,[sp,#2104]
	str x3,[sp,#2240]
	// %36 = sub nsw i32 %35, 1
	ldr x3,[sp,#2240]
	mov x13,#1
	sub w14,w3,w13
	str x14,[sp,#2248]
	// %37 = add nsw i32 0, %36
	mov x3,#0
	ldr x13,[sp,#2248]
	add w14,w3,w13
	str x14,[sp,#2256]
	// %38 = load i32*, i32** %7, align 4
	add x3,sp,#16
	ldr x3,[x3]
	str x3,[sp,#2264]
	// %39 = bitcast i32* %38 to i32*
	// %40 = getelementptr inbounds i32, i32* %39, i32 %37
	ldr x3,[sp,#2264]
	ldr x14,[sp,#2256]
	lsl x14,x14,#2
	add x3,x3,x14
	str x3,[sp,#2280]
	// %41 = load i32, i32* %40, align 4
	ldr x3,[sp,#2280]
	ldr x3,[x3, #0]
	str x3,[sp,#2288]
	// %42 = icmp eq i32 %34, %41
	ldr x3,[sp,#2232]
	ldr x14,[sp,#2288]
	cmp w3,w14
	cset x4,eq
	str x4,[sp,#2296]
	// %43 = icmp ne i1 %42, 0
	ldr x3,[sp,#2296]
	mov x4,#0
	cmp w3,w4
	cset x14,ne
	str x14,[sp,#2304]
	// br i1 %43,  label %44,   label %61
	ldr x3,[sp,#2304]
	cmp x3,#0
	b.ne .L17
	b .L18
	// 
44:
.L17:
	// %45 = load i32, i32* %12, align 4
	ldr x3,[sp,#2096]
	str x3,[sp,#2312]
	// %46 = sub nsw i32 %45, 1
	ldr x3,[sp,#2312]
	mov x14,#1
	sub w15,w3,w14
	str x15,[sp,#2320]
	// %47 = load i32, i32* %13, align 4
	ldr x3,[sp,#2104]
	str x3,[sp,#2328]
	// %48 = sub nsw i32 %47, 1
	ldr x3,[sp,#2328]
	mov x15,#1
	sub w5,w3,w15
	str x5,[sp,#2336]
	// %49 = mul nsw i32 %46, 16
	ldr x3,[sp,#2320]
	mov x5,#16
	mul w15,w3,w5
	str x15,[sp,#2344]
	// %50 = add nsw i32 %49, %48
	ldr x3,[sp,#2344]
	ldr x5,[sp,#2336]
	add w15,w3,w5
	str x15,[sp,#2352]
	// %51 = bitcast [16 x [16 x i32]]* %11 to i32*
	// %52 = getelementptr inbounds i32, i32* %51, i32 %50
	add x3,sp,#48
	ldr x5,[sp,#2352]
	lsl x5,x5,#2
	add x3,x3,x5
	str x3,[sp,#2368]
	// %53 = load i32, i32* %52, align 4
	ldr x3,[sp,#2368]
	ldr x3,[x3, #0]
	str x3,[sp,#2376]
	// %54 = add nsw i32 %53, 1
	ldr x3,[sp,#2376]
	mov x5,#1
	add w15,w3,w5
	str x15,[sp,#2384]
	// %55 = load i32, i32* %12, align 4
	ldr x3,[sp,#2096]
	str x3,[sp,#2392]
	// %56 = mul nsw i32 %55, 16
	ldr x3,[sp,#2392]
	mov x15,#16
	mul w6,w3,w15
	str x6,[sp,#2400]
	// %57 = load i32, i32* %13, align 4
	ldr x3,[sp,#2104]
	str x3,[sp,#2408]
	// %58 = add nsw i32 %56, %57
	ldr x3,[sp,#2400]
	ldr x15,[sp,#2408]
	add w7,w3,w15
	str x7,[sp,#2416]
	// %59 = bitcast [16 x [16 x i32]]* %11 to i32*
	// %60 = getelementptr inbounds i32, i32* %59, i32 %58
	add x3,sp,#48
	ldr x7,[sp,#2416]
	lsl x7,x7,#2
	add x3,x3,x7
	str x3,[sp,#2432]
	// store i32 %54, i32*  %60, align 4
	ldr x3,[sp,#2384]
	ldr x7,[sp,#2432]
	str w3,[x7, #0]
	// br label %85
	b .L19
	// 
61:
.L18:
	// %62 = load i32, i32* %12, align 4
	ldr x3,[sp,#2096]
	str x3,[sp,#2440]
	// %63 = sub nsw i32 %62, 1
	ldr x3,[sp,#2440]
	mov x15,#1
	sub w8,w3,w15
	str x8,[sp,#2448]
	// %64 = mul nsw i32 %63, 16
	ldr x3,[sp,#2448]
	mov x8,#16
	mul w15,w3,w8
	str x15,[sp,#2456]
	// %65 = load i32, i32* %13, align 4
	ldr x3,[sp,#2104]
	str x3,[sp,#2464]
	// %66 = add nsw i32 %64, %65
	ldr x3,[sp,#2456]
	ldr x15,[sp,#2464]
	add w9,w3,w15
	str x9,[sp,#2472]
	// %67 = bitcast [16 x [16 x i32]]* %11 to i32*
	// %68 = getelementptr inbounds i32, i32* %67, i32 %66
	add x3,sp,#48
	ldr x9,[sp,#2472]
	lsl x9,x9,#2
	add x3,x3,x9
	str x3,[sp,#2488]
	// %69 = load i32, i32* %68, align 4
	ldr x3,[sp,#2488]
	ldr x3,[x3, #0]
	str x3,[sp,#2496]
	// %70 = load i32, i32* %13, align 4
	ldr x3,[sp,#2104]
	str x3,[sp,#2504]
	// %71 = sub nsw i32 %70, 1
	ldr x3,[sp,#2504]
	mov x15,#1
	sub w10,w3,w15
	str x10,[sp,#2512]
	// %72 = load i32, i32* %12, align 4
	ldr x3,[sp,#2096]
	str x3,[sp,#2520]
	// %73 = mul nsw i32 %72, 16
	ldr x3,[sp,#2520]
	mov x15,#16
	mul w11,w3,w15
	str x11,[sp,#2528]
	// %74 = add nsw i32 %73, %71
	ldr x3,[sp,#2528]
	ldr x11,[sp,#2512]
	add w15,w3,w11
	str x15,[sp,#2536]
	// %75 = bitcast [16 x [16 x i32]]* %11 to i32*
	// %76 = getelementptr inbounds i32, i32* %75, i32 %74
	add x3,sp,#48
	ldr x11,[sp,#2536]
	lsl x11,x11,#2
	add x3,x3,x11
	str x3,[sp,#2552]
	// %77 = load i32, i32* %76, align 4
	ldr x3,[sp,#2552]
	ldr x3,[x3, #0]
	str x3,[sp,#2560]
	// store i32 %69, i32* x0, align 4
	ldr x0,[sp,#2496]
	// store i32 %77, i32* x1, align 4
	ldr x1,[sp,#2560]
	// %78 = call i32 @MAX(i32 x0, i32 x1)
	mov x0,x0
	mov x1,x1
	bl MAX
	// store i32 x0, i32* %78, align 4
	str x0,[sp,#2568]
	// %79 = load i32, i32* %12, align 4
	ldr x3,[sp,#2096]
	str x3,[sp,#2576]
	// %80 = mul nsw i32 %79, 16
	ldr x3,[sp,#2576]
	mov x15,#16
	mul w12,w3,w15
	str x12,[sp,#2584]
	// %81 = load i32, i32* %13, align 4
	ldr x3,[sp,#2104]
	str x3,[sp,#2592]
	// %82 = add nsw i32 %80, %81
	ldr x3,[sp,#2584]
	ldr x15,[sp,#2592]
	add w13,w3,w15
	str x13,[sp,#2600]
	// %83 = bitcast [16 x [16 x i32]]* %11 to i32*
	// %84 = getelementptr inbounds i32, i32* %83, i32 %82
	add x3,sp,#48
	ldr x13,[sp,#2600]
	lsl x13,x13,#2
	add x3,x3,x13
	str x3,[sp,#2616]
	// store i32 %78, i32*  %84, align 4
	ldr x3,[sp,#2568]
	ldr x13,[sp,#2616]
	str w3,[x13, #0]
	// br label %85
	b .L19
	// 
85:
.L19:
	// %86 = load i32, i32* %13, align 4
	ldr x3,[sp,#2104]
	str x3,[sp,#2624]
	// %87 = add nsw i32 %86, 1
	ldr x3,[sp,#2624]
	mov x15,#1
	add w4,w3,w15
	str x4,[sp,#2632]
	// store i32 %87, i32* %13, align 4
	ldr x3,[sp,#2632]
	str x3,[sp,#2104]
	// br label %21
	b .L14
	// 
88:
.L20:
	// %89 = load i32, i32* %12, align 4
	ldr x3,[sp,#2096]
	str x3,[sp,#2640]
	// %90 = add nsw i32 %89, 1
	ldr x3,[sp,#2640]
	mov x14,#1
	add w5,w3,w14
	str x5,[sp,#2648]
	// store i32 %90, i32* %12, align 4
	ldr x3,[sp,#2648]
	str x3,[sp,#2096]
	// br label %15
	b .L12
	// 
91:
.L21:
	// %92 = load i32, i32* %6, align 4
	ldr x3,[sp,#8]
	str x3,[sp,#2656]
	// store i32 %92, i32* x0, align 4
	ldr x0,[sp,#2656]
	// call void  @putint(i32 x0)
	mov x0,x0
	bl putint
	// store i32 10, i32* x0, align 4
	mov x0,#10
	// call void  @putch(i32 x0)
	mov x0,x0
	bl putch
	// %93 =