@a = dso_local global i32 0, align 4
@b = dso_local global i32 0, align 4
@c = dso_local global i32 0, align 4
@d = dso_local global i32 0, align 4
@e = dso_local global i32 0, align 4
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %3 = call i32 @getint()
  store i32 %3, i32* @a, align 4
  %4 = call i32 @getint()
  store i32 %4, i32* @b, align 4
  %5 = call i32 @getint()
  store i32 %5, i32* @c, align 4
  %6 = call i32 @getint()
  store i32 %6, i32* @d, align 4
  %7 = call i32 @getint()
  store i32 %7, i32* @e, align 4
  store i32 0, i32* %2, align 4
  %8 = load i32, i32* @a, align 4
  %9 = load i32, i32* @b, align 4
  %10 = load i32, i32* @c, align 4
  %11 = mul nsw i32 %9, %10
  %12 = sub nsw i32 %8, %11
  %13 = load i32, i32* @d, align 4
  %14 = load i32, i32* @a, align 4
  %15 = load i32, i32* @c, align 4
  %16 = sdiv i32 %14, %15
  %17 = sub nsw i32 %13, %16
  %18 = icmp ne i32 %12, %17
  %19 = load i32, i32* @a, align 4
  %20 = load i32, i32* @b, align 4
  %21 = mul nsw i32 %19, %20
  %22 = load i32, i32* @c, align 4
  %23 = sdiv i32 %21, %22
  %24 = load i32, i32* @e, align 4
  %25 = load i32, i32* @d, align 4
  %26 = add nsw i32 %24, %25
  %27 = icmp eq i32 %23, %26
  %28 = or %18,%27
  %29 = load i32, i32* @a, align 4
  %30 = load i32, i32* @b, align 4
  %31 = add nsw i32 %29, %30
  %32 = load i32, i32* @c, align 4
  %33 = add nsw i32 %31, %32
  %34 = load i32, i32* @d, align 4
  %35 = load i32, i32* @e, align 4
  %36 = add nsw i32 %34, %35
  %37 = icmp eq i32 %33, %36
  %38 = or %28,%37
  br i1 %38,  label %39,   label %40

39:
  store i32 1, i32* %2, align 4
  br label %40

40:
  %41 = load i32, i32* %2, align 4
  store i32 %41, i32* %1, align 4
  %42 = load i32, i32* %1, align 4
  ret i32 %42
}
