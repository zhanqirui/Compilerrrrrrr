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
  store i32 6, i32* %7, align 4
  %8 = load i32, i32* %4, align 4
  %9 = add nsw i32 2, %8
  %10 = icmp lt i32 %9, 6
  %11 = icmp and %10,1
  br i1 %11,  label %12,   label %56

12:
  %13 = load i32, i32* %6, align 4
  %14 = load i32, i32* %2, align 4
  %15 = add nsw i32 0, %14
  %16 = add nsw i32 %15, 0
  %17 = icmp or %13,%16
  br i1 %17,  label %18,   label %54

18:
  %19 = icmp gt i32 9, 2
  %20 = icmp and 0,%19
  br i1 %20,  label %21,   label %22

21:
  store i32 3, i32* %1, align 4
  br label %53

22:
  %23 = load i32, i32* %6, align 4
  %24 = icmp and 0,%23
  br i1 %24,  label %25,   label %26

25:
  store i32 4, i32* %1, align 4
  br label %52

26:
  %27 = load i32, i32* %2, align 4
  %28 = add nsw i32 2, %27
  %29 = icmp ge i32 %28, 2
  br i1 %29,  label %30,   label %50

30:
  %31 = icmp ge i32 -1, 0
  %32 = icmp or %31,0
  br i1 %32,  label %33,   label %34

33:
  store i32 6, i32* %1, align 4
  br label %49

34:
  br i1 1,  label %35,   label %47

35:
  %36 = load i32, i32* %3, align 4
  %37 = add nsw i32 %36, 20
  %38 = icmp gt i32 %37, 10
  br i1 %38,  label %39,   label %45

39:
  %40 = load i32, i32* %7, align 4
  %41 = add nsw i32 0, %40
  br i1 %41,  label %42,   label %43

42:
  store i32 9, i32* %1, align 4
  br label %44

43:
  store i32 10, i32* %1, align 4
  br label %44

44:
  br label %46

45:
  store i32 8, i32* %1, align 4
  br label %46

46:
  br label %48

47:
  store i32 7, i32* %1, align 4
  br label %48

48:
  br label %49

49:
  br label %51

50:
  store i32 5, i32* %1, align 4
  br label %51

51:
  br label %52

52:
  br label %53

53:
  br label %55

54:
  store i32 2, i32* %1, align 4
  br label %55

55:
  br label %57

56:
  store i32 1, i32* %1, align 4
  br label %57

57:
  %58 = load i32, i32* %1, align 4
  ret i32 %58
}
