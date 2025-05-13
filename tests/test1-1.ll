@b = private unnamed_addr constant [4 x [2 x i32]][[2 x i32] [i32 1, i32 2], [2 x i32] [i32 3, i32 4], [2 x i32] [i32 5, i32 6], [2 x i32] [i32 7, i32 8]], align 16
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca [4 x [2 x i32]], align 16
  %3 = alloca [4 x [2 x i32]], align 16
  %4 = alloca [4 x [2 x i32]], align 16
  store i32 0, i32* %1, align 4
  %5 = mul nsw i32 2, 2
  %6 = add nsw i32 %5, 1
  %7 = mul nsw i32 %6, 4
  %8 = add nsw i32 %7, %3
  %9 = mul nsw i32 3, 2
  %10 = add nsw i32 %9, 1
  %11 = mul nsw i32 %10, 4
  %12 = add nsw i32 %11, %4
  store i32** %12, i32 %1, align 4
  %13 = load i32, i32* %1, align 4
  ret i32 %13
}
