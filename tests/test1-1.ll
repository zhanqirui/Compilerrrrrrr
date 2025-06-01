define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca [2 x float], align 16
  store i32 0, i32* %1, align 4
  %3 = bitcast [2 x float]* %2 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %3, i8 0, i64 8, i1 false)
  %4 = bitcast [2 x float]* %2 to float*
  %5 = getelementptr inbounds float, float* %4, i32 0
  store float 0x3ff19999a0000000, float* %5, align 4
  %6 = getelementptr inbounds float, float* %4, i32 1
  store float 0x40019999a0000000, float* %6, align 4
  %7 = add nsw i32 0, 0
  %8 = bitcast [2 x float]* %2 to float*
  %9 = getelementptr inbounds float, float* %8, i32 %7
  %10 = load float, float* %9, align 4
  call void  @putfloat(float %10)
  store i32 0, i32* %1, align 4
  br label %11

11:
  %12 = load i32, i32* %1, align 4
  ret i32 %12
}
declare void @putfloat(float) #1

declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #1
