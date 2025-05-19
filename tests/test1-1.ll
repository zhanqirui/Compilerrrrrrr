define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca [4 x [2 x i32]], align 16
  %3 = alloca i32, align 4
  %4 = alloca [4 x [2 x i32]], align 16
  %5 = alloca [4 x [2 x i32]], align 16
  %6 = alloca [4 x [2 x i32]], align 16
  %7 = alloca [4 x [2 x [1 x i32]]], align 16
  store i32 0, i32* %1, align 4
  %8 = bitcast [4 x [2 x i32]]* %2 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %8, i8 0, i64 32, i1 false)
  %9 = bitcast [4 x [2 x i32]]* %2 to i32*
  %10 = getelementptr inbounds i32, i32* %9, i32 0
  store i32 1, i32* %10, align 4
  %11 = getelementptr inbounds i32, i32* %9, i32 1
  store i32 2, i32* %11, align 4
  %12 = getelementptr inbounds i32, i32* %9, i32 2
  store i32 3, i32* %12, align 4
  %13 = getelementptr inbounds i32, i32* %9, i32 3
  store i32 4, i32* %13, align 4
  %14 = getelementptr inbounds i32, i32* %9, i32 6
  store i32 7, i32* %14, align 4
  store i32 3, i32* %3, align 4
  %15 = bitcast [4 x [2 x i32]]* %4 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %15, i8 0, i64 32, i1 false)
  %16 = bitcast [4 x [2 x i32]]* %5 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %16, i8 0, i64 32, i1 false)
  %17 = bitcast [4 x [2 x i32]]* %5 to i32*
  %18 = getelementptr inbounds i32, i32* %17, i32 0
  store i32 1, i32* %18, align 4
  %19 = getelementptr inbounds i32, i32* %17, i32 1
  store i32 2, i32* %19, align 4
  %20 = getelementptr inbounds i32, i32* %17, i32 2
  store i32 3, i32* %20, align 4
  %21 = getelementptr inbounds i32, i32* %17, i32 3
  store i32 4, i32* %21, align 4
  %22 = getelementptr inbounds i32, i32* %17, i32 4
  store i32 5, i32* %22, align 4
  %23 = getelementptr inbounds i32, i32* %17, i32 5
  store i32 6, i32* %23, align 4
  %24 = getelementptr inbounds i32, i32* %17, i32 6
  store i32 7, i32* %24, align 4
  %25 = getelementptr inbounds i32, i32* %17, i32 7
  store i32 8, i32* %25, align 4
  %26 = bitcast [4 x [2 x i32]]* %6 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %26, i8 0, i64 32, i1 false)
  %27 = mul nsw i32 3, 2
  %28 = add nsw i32 %27, 0
  %29 = bitcast [4 x [2 x i32]]* %2 to i32*
  %30 = getelementptr inbounds i32, i32* %29, i32 %28
  %31 = load i32, i32* %30, align 4
  %32 = bitcast [4 x [2 x i32]]* %6 to i32*
  %33 = getelementptr inbounds i32, i32* %32, i32 0
  store i32 1, i32* %33, align 4
  %34 = getelementptr inbounds i32, i32* %32, i32 1
  store i32 2, i32* %34, align 4
  %35 = getelementptr inbounds i32, i32* %32, i32 2
  store i32 3, i32* %35, align 4
  %36 = getelementptr inbounds i32, i32* %32, i32 4
  store i32 5, i32* %36, align 4
  %37 = getelementptr inbounds i32, i32* %32, i32 6
  store i32 %31, i32* %37, align 4
  %38 = getelementptr inbounds i32, i32* %32, i32 7
  store i32 8, i32* %38, align 4
  %39 = bitcast [4 x [2 x [1 x i32]]]* %7 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %39, i8 0, i64 32, i1 false)
  %40 = mul nsw i32 2, 2
  %41 = add nsw i32 %40, 1
  %42 = bitcast [4 x [2 x i32]]* %6 to i32*
  %43 = getelementptr inbounds i32, i32* %42, i32 %41
  %44 = load i32, i32* %43, align 4
  %45 = mul nsw i32 2, 2
  %46 = add nsw i32 %45, 1
  %47 = bitcast [4 x [2 x i32]]* %5 to i32*
  %48 = getelementptr inbounds i32, i32* %47, i32 %46
  %49 = load i32, i32* %48, align 4
  %50 = bitcast [4 x [2 x [1 x i32]]]* %7 to i32*
  %51 = getelementptr inbounds i32, i32* %50, i32 0
  store i32 %44, i32* %51, align 4
  %52 = getelementptr inbounds i32, i32* %50, i32 1
  store i32 %49, i32* %52, align 4
  %53 = getelementptr inbounds i32, i32* %50, i32 2
  store i32 3, i32* %53, align 4
  %54 = getelementptr inbounds i32, i32* %50, i32 3
  store i32 4, i32* %54, align 4
  %55 = getelementptr inbounds i32, i32* %50, i32 4
  store i32 5, i32* %55, align 4
  %56 = getelementptr inbounds i32, i32* %50, i32 5
  store i32 6, i32* %56, align 4
  %57 = getelementptr inbounds i32, i32* %50, i32 6
  store i32 7, i32* %57, align 4
  %58 = getelementptr inbounds i32, i32* %50, i32 7
  store i32 8, i32* %58, align 4
  %59 = mul nsw i32 3, 2
  %60 = add nsw i32 %59, 1
  %61 = mul nsw i32 %60, 1
  %62 = add nsw i32 %61, 0
  %63 = bitcast [4 x [2 x [1 x i32]]]* %7 to i32*
  %64 = getelementptr inbounds i32, i32* %63, i32 %62
  %65 = load i32, i32* %64, align 4
  %66 = mul nsw i32 0, 2
  %67 = add nsw i32 %66, 0
  %68 = mul nsw i32 %67, 1
  %69 = add nsw i32 %68, 0
  %70 = bitcast [4 x [2 x [1 x i32]]]* %7 to i32*
  %71 = getelementptr inbounds i32, i32* %70, i32 %69
  %72 = load i32, i32* %71, align 4
  %73 = add nsw i32 %65, %72
  %74 = mul nsw i32 0, 2
  %75 = add nsw i32 %74, 1
  %76 = mul nsw i32 %75, 1
  %77 = add nsw i32 %76, 0
  %78 = bitcast [4 x [2 x [1 x i32]]]* %7 to i32*
  %79 = getelementptr inbounds i32, i32* %78, i32 %77
  %80 = load i32, i32* %79, align 4
  %81 = add nsw i32 %73, %80
  %82 = mul nsw i32 3, 2
  %83 = add nsw i32 %82, 0
  %84 = bitcast [4 x [2 x i32]]* %6 to i32*
  %85 = getelementptr inbounds i32, i32* %84, i32 %83
  %86 = load i32, i32* %85, align 4
  %87 = add nsw i32 %81, %86
  store i32 %87, i32* %1, align 4
  %88 = load i32, i32* %1, align 4
  ret i32 %88
}

declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #1
