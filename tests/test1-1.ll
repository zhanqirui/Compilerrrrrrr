define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca [3 x i32], align 16
  %3 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %4 = bitcast [3 x i32]* %2 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %4, i8 0, i64 32, i1 false)
  %5 = bitcast [3 x i32]* %2 to i32*
  %6 = getelementptr inbounds i32, i32* %5, i64 0
  store i32 0, i32* %6, align 4
  %7 = getelementptr inbounds i32, i32* %5, i64 1
  store i32 2, i32* %7, align 4
  %8 = getelementptr inbounds i32, i32* %5, i64 2
  store i32 3, i32* %8, align 4
  store i32 10, i32* %3, align 4
  %9 = bitcast [3 x i32]* %2 to i32*
  %10 = getelementptr inbounds i32, i32* %9, i64 1
  store i32 10, i32* %10, align 4
  %11 = bitcast [3 x i32]* %2 to i32*
  %12 = getelementptr inbounds i32, i32* %11, i64 1
  %13 = load i32, i32* %12, align 4
  store i32 %13, i32* %1, align 4
  %14 = load i32, i32* %1, align 4
  ret i32 %14
}

declare void @putint(i32) #0

declare i32 @getint() #0

declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #1
