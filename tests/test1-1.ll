@a = dso_local global [4096 x i32] zeroinitializer, align 16
define dso_local i32 @f1(i32* %0) #0 {
  %2 = alloca i32*, align 4
  %3 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32* %0, i32**  %2, align 4
  %4 = add nsw i32 0, 5
  %5 = bitcast [4096 x i32]* @a to i32*
  %6 = getelementptr inbounds i32, i32* %5, i32 %4
  store i32 4000, i32* %6, align 4
  %7 = add nsw i32 0, 4000
  %8 = bitcast [4096 x i32]* @a to i32*
  %9 = getelementptr inbounds i32, i32* %8, i32 %7
  store i32 3, i32* %9, align 4
  %10 = add nsw i32 0, 4095
  %11 = bitcast [4096 x i32]* @a to i32*
  %12 = getelementptr inbounds i32, i32* %11, i32 %10
  store i32 7, i32* %12, align 4
  %13 = add nsw i32 0, 2216
  %14 = bitcast [4096 x i32]* @a to i32*
  %15 = getelementptr inbounds i32, i32* %14, i32 %13
  %16 = load i32, i32* %15, align 4
  %17 = add nsw i32 %16, 9
  %18 = add nsw i32 0, 4095
  %19 = bitcast [4096 x i32]* @a to i32*
  %20 = getelementptr inbounds i32, i32* %19, i32 %18
  %21 = load i32, i32* %20, align 4
  %22 = add nsw i32 0, %21
  %23 = load i32*, i32** %2, align 4
  %24 = bitcast i32* %23 to i32*
  %25 = getelementptr inbounds i32, i32* %24, i32 %22
  store i32 %17, i32*  %25, align 4
  %26 = add nsw i32 0, 5
  %27 = bitcast [4096 x i32]* @a to i32*
  %28 = getelementptr inbounds i32, i32* %27, i32 %26
  %29 = load i32, i32* %28, align 4
  %30 = add nsw i32 0, %29
  %31 = bitcast [4096 x i32]* @a to i32*
  %32 = getelementptr inbounds i32, i32* %31, i32 %30
  %33 = load i32, i32* %32, align 4
  store i32 %33, i32* %3, align 4
  br label %34

34:
  %35 = load i32, i32* %3, align 4
  ret i32 %35
}
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca [4 x [1024 x i32]], align 16
  %3 = alloca [1024 x [4 x i32]], align 16
  store i32 0, i32* %1, align 4
  %4 = bitcast [4 x [1024 x i32]]* %2 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %4, i8 0, i64 16384, i1 false)
  %5 = bitcast [4 x [1024 x i32]]* %2 to i32*
  %6 = getelementptr inbounds i32, i32* %5, i32 1024
  store i32 1, i32* %6, align 4
  %7 = getelementptr inbounds i32, i32* %5, i32 2048
  store i32 2, i32* %7, align 4
  %8 = getelementptr inbounds i32, i32* %5, i32 2049
  store i32 3, i32* %8, align 4
  %9 = getelementptr inbounds i32, i32* %5, i32 3072
  store i32 4, i32* %9, align 4
  %10 = getelementptr inbounds i32, i32* %5, i32 3073
  store i32 5, i32* %10, align 4
  %11 = getelementptr inbounds i32, i32* %5, i32 3074
  store i32 6, i32* %11, align 4
  %12 = bitcast [1024 x [4 x i32]]* %3 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %12, i8 0, i64 16384, i1 false)
  %13 = bitcast [1024 x [4 x i32]]* %3 to i32*
  %14 = getelementptr inbounds i32, i32* %13, i32 0
  store i32 1, i32* %14, align 4
  %15 = getelementptr inbounds i32, i32* %13, i32 1
  store i32 2, i32* %15, align 4
  %16 = getelementptr inbounds i32, i32* %13, i32 4
  store i32 3, i32* %16, align 4
  %17 = getelementptr inbounds i32, i32* %13, i32 5
  store i32 4, i32* %17, align 4
  %18 = add nsw i32 0, 0
  %19 = bitcast [1024 x [4 x i32]]* %3 to i32*
  %20 = getelementptr inbounds i32, i32* %19, i32 %18
  %21 = load i32, i32* %20, align 4
  %22 = call i32 @f1(i32 %21)
  call void  @putint(i32 %22)
  call void  @putch(i32 10)
  %23 = mul nsw i32 2, 4
  %24 = add nsw i32 %23, 0
  %25 = bitcast [1024 x [4 x i32]]* %3 to i32*
  %26 = getelementptr inbounds i32, i32* %25, i32 %24
  %27 = load i32, i32* %26, align 4
  store i32 %27, i32* %1, align 4
  br label %28

28:
  %29 = load i32, i32* %1, align 4
  ret i32 %29
}
declare void @putint(i32) #1
declare void @putch(i32) #1

declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #1
