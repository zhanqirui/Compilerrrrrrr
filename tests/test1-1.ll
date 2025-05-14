define dso_local void @putint(i32 ) #0 {
}
define dso_local i32 @getint() #0 {
}
define dso_local i32 @ifElseIf() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 5, i32* %2, align 4
  store i32 10, i32* %3, align 4
  %4 = load i32, i32* %2, align 4
  %5 = icmp eq i32 %4, 6
  %6 = icmp ne i1 %5, 0
  br i1 %6,  label %11,   label %13

7:
  %8 = load i32, i32* %3, align 4
  %9 = icmp eq i32 %8, 11
  %10 = icmp ne i1 %9, 0
  br i1 %10,  label %11,   label %13

11:
  %12 = load i32, i32* %2, align 4
  store i32 %12, i32* %1, align 4
  br label %40

13:
  %14 = load i32, i32* %3, align 4
  %15 = icmp eq i32 %14, 10
  %16 = icmp ne i1 %15, 0
  br i1 %16,  label %17,   label %22

17:
  %18 = load i32, i32* %2, align 4
  %19 = icmp eq i32 %18, 1
  %20 = icmp ne i1 %19, 0
  br i1 %20,  label %21,   label %22

21:
  store i32 25, i32* %2, align 4
  br label %39

22:
  %23 = load i32, i32* %3, align 4
  %24 = icmp eq i32 %23, 10
  %25 = icmp ne i1 %24, 0
  br i1 %25,  label %26,   label %34

26:
  %27 = load i32, i32* %2, align 4
  %28 = sub nsw i32 0, 5
  %29 = icmp eq i32 %27, %28
  %30 = icmp ne i1 %29, 0
  br i1 %30,  label %31,   label %34

31:
  %32 = load i32, i32* %2, align 4
  %33 = add nsw i32 %32, 15
  store i32 %33, i32* %2, align 4
  br label %38

34:
  %35 = load i32, i32* %2, align 4
  %36 = add nsw i32 0, %35
  %37 = sub nsw i32 0, %36
  store i32 %37, i32* %2, align 4
  br label %38

38:
  br label %39

39:
  br label %40

40:
  %41 = load i32, i32* %2, align 4
  store i32 %41, i32* %1, align 4
  %42 = load i32, i32* %1, align 4
  ret i32 %42
}
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 @ifElseIf()
  call void @putint(i32 %2, i32 1)
  store i32 0, i32* %1, align 4
  %3 = load i32, i32* %1, align 4
  ret i32 %3
}
