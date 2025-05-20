@e = dso_local constant float  0x4005BF0A80000000, align 4
define dso_local float @my_fabs(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  store i32 0, float* %3, align 4
  store float %0, float* %2, align 4
  br label %4

4:
  %5 = load float, float* %2, align 4
  %6 = icmp sgt float %5, 0.000000
  %7 = icmp ne i1 %6, 0
  br i1 %7,  label %8,   label %10

8:
  %9 = load float, float* %2, align 4
  store float %9, float* %3, align 4
  br label %10

10:
  %11 = load float, float* %2, align 4
  %12 = sub nsw float 0, %11
  store i32 %12, float* %3, align 4
  %13 = load i32, i32* %3, align 4
  ret i32 %13
}
define dso_local float @my_pow(float %0, i32 %1) #0 {
  %3 = alloca float, align 4
  %4 = alloca i32, align 4
  %5 = alloca float, align 4
  %6 = alloca float, align 4
  store i32 0, float* %5, align 4
  store float %0, float* %3, align 4
  store i32 %1, i32* %4, align 4
  br label %7

7:
  %8 = load i32, i32* %4, align 4
  %9 = icmp slt i32 %8, 0
  %10 = icmp ne i1 %9, 0
  br i1 %10,  label %11,   label %17

11:
  %12 = load float, float* %3, align 4
  %13 = load i32, i32* %4, align 4
  %14 = sub nsw i32 0, %13
  %15 = call f32 @my_pow(float %12, i32 %14)
  %16 = sdiv float 1, %15
  store i32 %16, float* %5, align 4
  br label %17

17:
  store float 1.000000, float* %6, align 4
  br label %18

18:
  %19 = load i32, i32* %4, align 4
  %20 = icmp ne i32 %19, 0
  br i1 %20,  label %21,   label %36

21:
  br label %22

22:
  %23 = load i32, i32* %4, align 4
  %24 = srem i32 %23, 2
  %25 = icmp ne i32 %24, 0
  br i1 %25,  label %26,   label %30

26:
  %27 = load float, float* %6, align 4
  %28 = load float, float* %3, align 4
  %29 = mul nsw float %27, %28
  store i32 %29, float* %6, align 4
  br label %30

30:
  %31 = load float, float* %3, align 4
  %32 = load float, float* %3, align 4
  %33 = mul nsw float %31, %32
  store i32 %33, float* %3, align 4
  %34 = load i32, i32* %4, align 4
  %35 = sdiv i32 %34, 2
  store i32 %35, i32* %4, align 4
  br label %18

36:
  %37 = load float, float* %6, align 4
  store float %37, float* %5, align 4
  %38 = load i32, i32* %5, align 4
  ret i32 %38
}
define dso_local float @my_sqrt(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  %4 = alloca float, align 4
  %5 = alloca i32, align 4
  store i32 0, float* %3, align 4
  store float %0, float* %2, align 4
  br label %6

6:
  %7 = load float, float* %2, align 4
  %8 = icmp sgt float %7, 100.000000
  %9 = icmp ne i1 %8, 0
  br i1 %9,  label %10,   label %15

10:
  %11 = load float, float* %2, align 4
  %12 = fdiv float %11, 100.000000
  %13 = call f32 @my_sqrt(i32 %12)
  %14 = mul nsw float 10.000000, %13
  store i32 %14, float* %3, align 4
  br label %15

15:
  %16 = load float, float* %2, align 4
  %17 = fdiv float %16, 8.000000
  %18 = add nsw float %17, 0
  %19 = load float, float* %2, align 4
  %20 = mul nsw float 2, %19
  %21 = load float, float* %2, align 4
  %22 = add nsw float 4, %21
  %23 = sdiv i32 %20, %22
  %24 = add nsw i32 %18, %23
  store i32 %24, float* %4, align 4
  store i32 10, i32* %5, align 4
  br label %25

25:
  %26 = load i32, i32* %5, align 4
  %27 = icmp ne i32 %26, 0
  br i1 %27,  label %28,   label %37

28:
  %29 = load float, float* %4, align 4
  %30 = load float, float* %2, align 4
  %31 = load float, float* %4, align 4
  %32 = fdiv float %30, %31
  %33 = add nsw float %29, %32
  %34 = sdiv i32 %33, 2
  store i32 %34, float* %4, align 4
  %35 = load i32, i32* %5, align 4
  %36 = sub nsw i32 %35, 1
  store i32 %36, i32* %5, align 4
  br label %25

37:
  %38 = load float, float* %4, align 4
  store float %38, float* %3, align 4
  %39 = load i32, i32* %3, align 4
  ret i32 %39
}
define dso_local float @F1(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  store i32 0, float* %3, align 4
  store float %0, float* %2, align 4
  %4 = load float, float* %2, align 4
  %5 = sdiv float 1, %4
  store i32 %5, float* %3, align 4
  %6 = load i32, i32* %3, align 4
  ret i32 %6
}
define dso_local float @F2(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  store i32 0, float* %3, align 4
  store float %0, float* %2, align 4
  %4 = load float, float* %2, align 4
  %5 = load float, float* %2, align 4
  %6 = mul nsw float %4, %5
  %7 = sub nsw i32 1, %6
  %8 = call f32 @my_sqrt(i32 %7)
  %9 = sdiv float 1, %8
  store i32 %9, float* %3, align 4
  %10 = load i32, i32* %3, align 4
  ret i32 %10
}
define dso_local float @simpson(float %0, float %1, i32 %2) #0 {
  %4 = alloca float, align 4
  %5 = alloca float, align 4
  %6 = alloca i32, align 4
  %7 = alloca float, align 4
  %8 = alloca float, align 4
  store i32 0, float* %7, align 4
  store float %0, float* %4, align 4
  store float %1, float* %5, align 4
  store i32 %2, i32* %6, align 4
  %9 = load float, float* %4, align 4
  %10 = load float, float* %5, align 4
  %11 = load float, float* %4, align 4
  %12 = sub nsw float %10, %11
  %13 = sdiv i32 %12, 2
  %14 = add nsw float %9, %13
  store i32 %14, float* %8, align 4
  br label %15

15:
  %16 = load i32, i32* %6, align 4
  %17 = icmp eq i32 %16, 1
  %18 = icmp ne i1 %17, 0
  br i1 %18,  label %19,   label %34

19:
  %20 = load float, float* %4, align 4
  %21 = call f32 @F1(float %20)
  %22 = load float, float* %8, align 4
  %23 = call f32 @F1(float %22)
  %24 = mul nsw float 4, %23
  %25 = add nsw float %21, %24
  %26 = load float, float* %5, align 4
  %27 = call f32 @F1(float %26)
  %28 = add nsw float %25, %27
  %29 = load float, float* %5, align 4
  %30 = load float, float* %4, align 4
  %31 = sub nsw float %29, %30
  %32 = mul nsw i32 %28, %31
  %33 = sdiv i32 %32, 6
  store i32 %33, float* %7, align 4
  br label %34

34:
  br label %35

35:
  %36 = load i32, i32* %6, align 4
  %37 = icmp eq i32 %36, 2
  %38 = icmp ne i1 %37, 0
  br i1 %38,  label %39,   label %54

39:
  %40 = load float, float* %4, align 4
  %41 = call f32 @F2(float %40)
  %42 = load float, float* %8, align 4
  %43 = call f32 @F2(float %42)
  %44 = mul nsw float 4, %43
  %45 = add nsw float %41, %44
  %46 = load float, float* %5, align 4
  %47 = call f32 @F2(float %46)
  %48 = add nsw float %45, %47
  %49 = load float, float* %5, align 4
  %50 = load float, float* %4, align 4
  %51 = sub nsw float %49, %50
  %52 = mul nsw i32 %48, %51
  %53 = sdiv i32 %52, 6
  store i32 %53, float* %7, align 4
  br label %54

54:
  store i32 0, float* %7, align 4
  %55 = load i32, i32* %7, align 4
  ret i32 %55
}
define dso_local float @asr5(float %0, float %1, float %2, float %3, i32 %4) #0 {
  %6 = alloca float, align 4
  %7 = alloca float, align 4
  %8 = alloca float, align 4
  %9 = alloca float, align 4
  %10 = alloca i32, align 4
  %11 = alloca float, align 4
  %12 = alloca float, align 4
  %13 = alloca float, align 4
  %14 = alloca float, align 4
  store i32 0, float* %11, align 4
  store float %0, float* %6, align 4
  store float %1, float* %7, align 4
  store float %2, float* %8, align 4
  store float %3, float* %9, align 4
  store i32 %4, i32* %10, align 4
  %15 = load float, float* %6, align 4
  %16 = load float, float* %7, align 4
  %17 = load float, float* %6, align 4
  %18 = sub nsw float %16, %17
  %19 = sdiv i32 %18, 2
  %20 = add nsw float %15, %19
  store i32 %20, float* %12, align 4
  %21 = load float, float* %6, align 4
  %22 = load float, float* %12, align 4
  %23 = load i32, i32* %10, align 4
  %24 = call f32 @simpson(float %21, float %22, i32 %23)
  store float %24, float* %13, align 4
  %25 = load float, float* %12, align 4
  %26 = load float, float* %7, align 4
  %27 = load i32, i32* %10, align 4
  %28 = call f32 @simpson(float %25, float %26, i32 %27)
  store float %28, float* %14, align 4
  br label %29

29:
  %30 = load float, float* %13, align 4
  %31 = load float, float* %14, align 4
  %32 = add nsw float %30, %31
  %33 = load float, float* %9, align 4
  %34 = sub nsw float %32, %33
  %35 = call f32 @my_fabs(i32 %34)
  %36 = load float, float* %8, align 4
  %37 = mul nsw float 15, %36
  %38 = icmp sle float %35, %37
  %39 = icmp ne i1 %38, 0
  br i1 %39,  label %40,   label %51

40:
  %41 = load float, float* %13, align 4
  %42 = load float, float* %14, align 4
  %43 = add nsw float %41, %42
  %44 = load float, float* %13, align 4
  %45 = load float, float* %14, align 4
  %46 = add nsw float %44, %45
  %47 = load float, float* %9, align 4
  %48 = sub nsw float %46, %47
  %49 = sdiv float %48, 15
  %50 = add nsw i32 %43, %49
  store i32 %50, float* %11, align 4
  br label %51

51:
  %52 = load float, float* %6, align 4
  %53 = load float, float* %12, align 4
  %54 = load float, float* %8, align 4
  %55 = fdiv float %54, 2.000000
  %56 = load float, float* %13, align 4
  %57 = load i32, i32* %10, align 4
  %58 = call f32 @asr5(float %52, float %53, i32 %55, float %56, i32 %57)
  %59 = load float, float* %12, align 4
  %60 = load float, float* %7, align 4
  %61 = load float, float* %8, align 4
  %62 = fdiv float %61, 2.000000
  %63 = load float, float* %14, align 4
  %64 = load i32, i32* %10, align 4
  %65 = call f32 @asr5(float %59, float %60, i32 %62, float %63, i32 %64)
  %66 = add nsw float %58, %65
  store i32 %66, float* %11, align 4
  %67 = load i32, i32* %11, align 4
  ret i32 %67
}
define dso_local float @asr4(float %0, float %1, float %2, i32 %3) #0 {
  %5 = alloca float, align 4
  %6 = alloca float, align 4
  %7 = alloca float, align 4
  %8 = alloca i32, align 4
  %9 = alloca float, align 4
  store i32 0, float* %9, align 4
  store float %0, float* %5, align 4
  store float %1, float* %6, align 4
  store float %2, float* %7, align 4
  store i32 %3, i32* %8, align 4
  %10 = load float, float* %5, align 4
  %11 = load float, float* %6, align 4
  %12 = load float, float* %7, align 4
  %13 = load float, float* %5, align 4
  %14 = load float, float* %6, align 4
  %15 = load i32, i32* %8, align 4
  %16 = call f32 @simpson(float %13, float %14, i32 %15)
  %17 = load i32, i32* %8, align 4
  %18 = call f32 @asr5(float %10, float %11, float %12, float %16, i32 %17)
  store float %18, float* %9, align 4
  %19 = load i32, i32* %9, align 4
  ret i32 %19
}
define dso_local float @eee(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  %4 = alloca float, align 4
  store i32 0, float* %3, align 4
  store float %0, float* %2, align 4
  br label %5

5:
  %6 = load float, float* %2, align 4
  %7 = icmp sgt float %6, 0.001000
  %8 = icmp ne i1 %7, 0
  br i1 %8,  label %9,   label %16

9:
  %10 = load float, float* %2, align 4
  %11 = fdiv float %10, 2.000000
  %12 = call f32 @eee(i32 %11)
  store float %12, float* %4, align 4
  %13 = load float, float* %4, align 4
  %14 = load float, float* %4, align 4
  %15 = mul nsw float %13, %14
  store i32 %15, float* %3, align 4
  br label %16

16:
  %17 = load float, float* %2, align 4
  %18 = add nsw float 1, %17
  %19 = load float, float* %2, align 4
  %20 = load float, float* %2, align 4
  %21 = mul nsw float %19, %20
  %22 = sdiv i32 %21, 2
  %23 = add nsw i32 %18, %22
  %24 = load float, float* %2, align 4
  %25 = call f32 @my_pow(float %24, i32 3)
  %26 = fdiv float %25, 6.000000
  %27 = add nsw i32 %23, %26
  %28 = load float, float* %2, align 4
  %29 = call f32 @my_pow(float %28, i32 4)
  %30 = fdiv float %29, 24.000000
  %31 = add nsw i32 %27, %30
  %32 = load float, float* %2, align 4
  %33 = call f32 @my_pow(float %32, i32 5)
  %34 = fdiv float %33, 120.000000
  %35 = add nsw i32 %31, %34
  store i32 %35, float* %3, align 4
  %36 = load i32, i32* %3, align 4
  ret i32 %36
}
define dso_local float @my_exp(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  %4 = alloca i32, align 4
  %5 = alloca float, align 4
  %6 = alloca float, align 4
  store i32 0, float* %3, align 4
  store float %0, float* %2, align 4
  br label %7

7:
  %8 = load float, float* %2, align 4
  %9 = icmp slt float %8, 0.000000
  %10 = icmp ne i1 %9, 0
  br i1 %10,  label %11,   label %16

11:
  %12 = load float, float* %2, align 4
  %13 = sub nsw float 0, %12
  %14 = call f32 @my_exp(i32 %13)
  %15 = sdiv float 1, %14
  store i32 %15, float* %3, align 4
  br label %16

16:
  %17 = load float, float* %2, align 4
  store float %17, i32* %4, align 4
  %18 = load float, float* %2, align 4
  %19 = load i32, i32* %4, align 4
  %20 = sub nsw float %18, %19
  store i32 %20, float* %2, align 4
  %21 = load i32, i32* %4, align 4
  %22 = call f32 @my_pow(float @e, i32 %21)
  store float %22, float* %5, align 4
  %23 = load float, float* %2, align 4
  %24 = call f32 @eee(float %23)
  store float %24, float* %6, align 4
  %25 = load float, float* %5, align 4
  %26 = load float, float* %6, align 4
  %27 = mul nsw float %25, %26
  store i32 %27, float* %3, align 4
  %28 = load i32, i32* %3, align 4
  ret i32 %28
}
define dso_local float @my_ln(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  store i32 0, float* %3, align 4
  store float %0, float* %2, align 4
  %4 = load float, float* %2, align 4
  %5 = call f32 @asr4(i32 1, float %4, float 0.000000, i32 1)
  store float %5, float* %3, align 4
  %6 = load i32, i32* %3, align 4
  ret i32 %6
}
define dso_local float @my_log(float %0, float %1) #0 {
  %3 = alloca float, align 4
  %4 = alloca float, align 4
  %5 = alloca float, align 4
  store i32 0, float* %5, align 4
  store float %0, float* %3, align 4
  store float %1, float* %4, align 4
  %6 = load float, float* %4, align 4
  %7 = call f32 @my_ln(float %6)
  %8 = load float, float* %3, align 4
  %9 = call f32 @my_ln(float %8)
  %10 = fdiv float %7, %9
  store i32 %10, float* %5, align 4
  %11 = load i32, i32* %5, align 4
  ret i32 %11
}
define dso_local float @my_powf(float %0, float %1) #0 {
  %3 = alloca float, align 4
  %4 = alloca float, align 4
  %5 = alloca float, align 4
  store i32 0, float* %5, align 4
  store float %0, float* %3, align 4
  store float %1, float* %4, align 4
  %6 = load float, float* %4, align 4
  %7 = load float, float* %3, align 4
  %8 = call f32 @my_ln(float %7)
  %9 = mul nsw float %6, %8
  %10 = call f32 @my_exp(i32 %9)
  store float %10, float* %5, align 4
  %11 = load i32, i32* %5, align 4
  ret i32 %11
}
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca float, align 4
  %4 = alloca float, align 4
  store i32 0, i32* %1, align 4
  %5 = call i32 (...) @getint()
  store i32 %5, i32* %2, align 4
  br label %6

6:
  %7 = load i32, i32* %2, align 4
  %8 = icmp ne i32 %7, 0
  br i1 %8,  label %9,   label %60

9:
  %10 = call f32 (...) @getfloat()
  store float %10, float* %3, align 4
  %11 = call f32 (...) @getfloat()
  store float %11, float* %4, align 4
  %12 = load float, float* %3, align 4
  %13 = call f32 @my_fabs(float %12)
  call void  @putfloat(float %13)
  call void  @putch(i32 32)
  %14 = load float, float* %3, align 4
  %15 = call f32 @my_pow(float %14, i32 2)
  call void  @putfloat(float %15)
  call void  @putch(i32 32)
  %16 = load float, float* %3, align 4
  %17 = call f32 @my_sqrt(float %16)
  call void  @putfloat(float %17)
  call void  @putch(i32 32)
  %18 = load float, float* %3, align 4
  %19 = call f32 @my_exp(float %18)
  call void  @putfloat(float %19)
  call void  @putch(i32 32)
  br label %20

20:
  %21 = load float, float* %3, align 4
  %22 = icmp sgt float %21, 0.000000
  %23 = icmp ne i1 %22, 0
  br i1 %23,  label %24,   label %27

24:
  %25 = load float, float* %3, align 4
  %26 = call f32 @my_ln(float %25)
  call void  @putfloat(float %26)
  br label %28

27:
  call void  @putch(i32 45)
  br label %28

28:
  call void  @putch(i32 32)
  br label %29

29:
  %30 = load float, float* %3, align 4
  %31 = icmp sgt float %30, 0.000000
  %32 = icmp ne i1 %31, 0
  br i1 %32,  label %33,   label %38

33:
  %34 = load float, float* %4, align 4
  %35 = icmp sgt float %34, 0.000000
  %36 = icmp ne i1 %35, 0
  br i1 %36,  label %37,   label %38

37:
  store i32 1, i32* %1, align 4
  br label %39

38:
  store i32 0, i32* %1, align 4
  br label %39

39:
  %40 = load i32, i32* %1, align 4
  %41 = icmp ne i32 %40, 0
  br i1 %41,  label %42,   label %46

42:
  %43 = load float, float* %3, align 4
  %44 = load float, float* %4, align 4
  %45 = call f32 @my_log(float %43, float %44)
  call void  @putfloat(float %45)
  br label %47

46:
  call void  @putch(i32 45)
  br label %47

47:
  call void  @putch(i32 32)
  br label %48

48:
  %49 = load float, float* %3, align 4
  %50 = icmp sgt float %49, 0.000000
  %51 = icmp ne i1 %50, 0
  br i1 %51,  label %52,   label %56

52:
  %53 = load float, float* %3, align 4
  %54 = load float, float* %4, align 4
  %55 = call f32 @my_powf(float %53, float %54)
  call void  @putfloat(float %55)
  br label %57

56:
  call void  @putch(i32 45)
  br label %57

57:
  call void  @putch(i32 10)
  %58 = load i32, i32* %2, align 4
  %59 = sub nsw i32 %58, 1
  store i32 %59, i32* %2, align 4
  br label %6

60:
  store i32 0, i32* %1, align 4
  %61 = load i32, i32* %1, align 4
  ret i32 %61
}
declare i32 @getint(...) #1
declare void @putch(i32) #1
declare f32 @getfloat(...) #1
declare void @putfloat(f32) #1
