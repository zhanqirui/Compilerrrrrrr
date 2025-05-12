@a = dso_local global i32 0, align 4
define dso_local i32 @func() #0 {
  ret i32 1
}
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 10, i32* @a, align 4
  %3 = call i32 @func(i32 %3)
  store i32 %3, i32* %2, align 4
  %4 = load i32, i32* %2, align 4
  ret i32 %4
}
