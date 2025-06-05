define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca float, align 4
  %4 = alloca [2 x [2 x float]], align 16
  %5 = alloca float, align 4
  %6 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 5, i32* %2, align 4
  store float 0x4025000000000000, float* %3, align 4
  %7 = bitcast [2 x [2 x float]]* %4 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %7, i8 0, i64 16, i1 false)
  %8 = bitcast [2 x [2 x float]]* %4 to i32*
  %9 = getelementptr inbounds i32, i32* %8, i32 0
  store i32 1, i32* %9, align 4
  %10 = getelementptr inbounds i32, i32* %8, i32 1
  store i32 2, i32* %10, align 4
  %11 = getelementptr inbounds i32, i32* %8, i32 2
  store i32 3, i32* %11, align 4
  %12 = getelementptr inbounds i32, i32* %8, i32 3
  store i32 4, i32* %12, align 4
  %13 = mul nsw i32 0, 2
  %14 = add nsw i32 %13, 1
  %15 = bitcast [2 x [2 x float]]* %4 to i32*
  %16 = getelementptr inbounds i32, i32* %15, i32 %14
  %17 = load i32, i32* %16, align 4
  %18 = mul nsw i32 1, 2
  %19 = add nsw i32 %18, 0
  %20 = bitcast [2 x [2 x float]]* %4 to i32*
  %21 = getelementptr inbounds i32, i32* %20, i32 %19
  %22 = load i32, i32* %21, align 4
  %23 = add nsw i32 %17, %22
  %24 = sitofp i32 %23 to float
  store float %24, float* %5, align 4
  %25 = load float, float* %3, align 4
  %26 = fptosi float %25 to i32
  store i32 %26, i32* %6, align 4
  store i32 0, i32* %1, align 4
  br label %27

27:
  %28 = load i32, i32* %1, align 4
  ret i32 %28
}

declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #1
