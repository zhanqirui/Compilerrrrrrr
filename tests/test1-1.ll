@a = dso_local global [5 x i32]  zeroinitializer, align 16
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = bitcast [5 x i32]* @a to i32*
  %3 = getelementptr inbounds i32, i32* %2, i64 4
  %4 = load i32, i32* %3, align 4
  store i32 %4, i32* %1, align 4
  %5 = load i32, i32* %1, align 4
  ret i32 %5
}
