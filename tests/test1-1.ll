@a = dso_local constant [5 x [5 x i32]] [[5 x i32] [i32 0, i32 1, i32 2, i32 3, i32 4], [5 x i32] [i32 5, i32 0, i32 0, i32 0, i32 0], [5 x i32] zeroinitializer, [5 x i32] zeroinitializer, [5 x i32] zeroinitializer], align 16
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = bitcast [5 x [5 x i32]]* @a to i32*
  %3 = getelementptr inbounds i32, i32* %2, i64 4
  %4 = load i32, i32* %3, align 4
  store i32 %4, i32* %1, align 4
  %5 = load i32, i32* %1, align 4
  ret i32 %5
}
