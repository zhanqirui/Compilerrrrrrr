define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 1, i32* %2, align 4
  store i32 2, i32* %3, align 4
  store i32 3, i32* %4, align 4
  store i32 4, i32* %5, align 4
  store i32 5, i32* %6, align 4
  store i32 0, i32* %7, align 4
  br label %8

8:
  %9 = load i32, i32* %2, align 4
  %10 = icmp eq i32 %9, 1
  %11 = icmp ne i1 %10, 0
  br i1 %11,  label %12,   label %48

12:
  %13 = load i32, i32* %7, align 4
  %14 = add nsw i32 %13, 2
  store i32 %14, i32* %7, align 4
  br label %15

15:
  %16 = load i32, i32* %3, align 4
  %17 = icmp eq i32 %16, 2
  %18 = icmp ne i1 %17, 0
  br i1 %18,  label %19,   label %44

19:
  %20 = load i32, i32* %7, align 4
  %21 = add nsw i32 %20, 2
  store i32 %21, i32* %7, align 4
  br label %22

22:
  %23 = load i32, i32* %4, align 4
  %24 = icmp eq i32 %23, 3
  %25 = icmp ne i1 %24, 0
  br i1 %25,  label %26,   label %40

26:
  %27 = load i32, i32* %7, align 4
  %28 = add nsw i32 %27, 2
  store i32 %28, i32* %7, align 4
  br label %29

29:
  %30 = load i32, i32* %5, align 4
  %31 = icmp eq i32 %30, 4
  %32 = icmp ne i1 %31, 0
  br i1 %32,  label %33,   label %36

33:
  %34 = load i32, i32* %7, align 4
  %35 = add nsw i32 %34, 2
  store i32 %35, i32* %7, align 4
  br label %39

36:
  %37 = load i32, i32* %7, align 4
  %38 = add nsw i32 %37, 1
  store i32 %38, i32* %7, align 4
  br label %39

39:
  br label %43

40:
  %41 = load i32, i32* %7, align 4
  %42 = add nsw i32 %41, 1
  store i32 %42, i32* %7, align 4
  br label %43

43:
  br label %47

44:
  %45 = load i32, i32* %7, align 4
  %46 = add nsw i32 %45, 1
  store i32 %46, i32* %7, align 4
  br label %47

47:
  br label %51

48:
  %49 = load i32, i32* %7, align 4
  %50 = add nsw i32 %49, 1
  store i32 %50, i32* %7, align 4
  br label %51

51:
  %52 = load i32, i32* %7, align 4
  store i32 %52, i32* %1, align 4
  %53 = load i32, i32* %1, align 4
  ret i32 %53
}
