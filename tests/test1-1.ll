@buf = dso_local global [2 x [100 x i32]] zeroinitializer, align 16
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %3 = add nsw i32 0, 0
  %4 = bitcast [2 x [100 x i32]]* @buf to i32*
  %5 = getelementptr inbounds i32, i32* %4, i32 %3
  %6 = load i32, i32* %5, align 4
  %7 = call i32 (...) @getarray(i32 %6)
  store i32 %7, i32* %2, align 4
  %8 = load i32, i32* %2, align 4
  %9 = add nsw i32 0, 0
  %10 = bitcast [2 x [100 x i32]]* @buf to i32*
  %11 = getelementptr inbounds i32, i32* %10, i32 %9
  %12 = load i32, i32* %11, align 4
  call void  @putarray(i32 %8, i32 %12)
  store i32 0, i32* %1, align 4
  br label %13

13:
  %14 = load i32, i32* %1, align 4
  ret i32 %14
}
declare i32 @getarray(i32*) #1
declare void @putarray(i32,i32*) #1
