define dso_local void @stack_push(i32* %0) #0 {
  %2 = alloca i32*, align 4
  %3 = alloca i32, align 4
  store i32* %0, i32**  %2, align 4
  %4 = add nsw i32 0, 1
  %5 = load i32*, i32** %2, align 4
  %6 = bitcast i32* %5 to i32*
  %7 = getelementptr inbounds i32, i32* %6, i32 %4
  store i32 3, i32* %7, align 4
  %8 = load i32, i32* %3, align 4
  ret void
}
define dso_local i32 @eval() #0 {
  %1 = alloca i32, align 4
  %2 = alloca [3 x i32], align 16
  store i32 0, i32* %1, align 4
  %3 = bitcast [3 x i32]* %2 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %3, i8 0, i64 12, i1 false)
  %4 = load i32, i32* %2, align 4
  %5 = bitcast i32* %4 to i32*
  %6 = getelementptr inbounds i32, i32* %5, i32 0
  call void @stack_push(i32* %6)
  %7 = add nsw i32 0, 1
  %8 = bitcast [3 x i32]* %2 to i32*
  %9 = getelementptr inbounds i32, i32* %8, i32 %7
  %10 = load i32, i32* %9, align 4
  store i32 %10, i32* %1, align 4
  %11 = load i32, i32* %1, align 4
  ret i32 %11
}
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %3 = call i32 @eval()
  store i32 %3, i32* %2, align 4
  %4 = load i32, i32* %2, align 4
  store i32 %4, i32* %1, align 4
  %5 = load i32, i32* %1, align 4
  ret i32 %5
}

declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #1
