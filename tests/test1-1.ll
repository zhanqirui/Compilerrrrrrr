@RADIUS = dso_local global float 0x4016000000000000, align 4
@PI = dso_local global float 0x400921fb60000000, align 4
@EPS = dso_local global float 0x3eb0c6f7a0000000, align 4
@PI_HEX = dso_local global float 0x400921fb60000000, align 4
@HEX2 = dso_local global float 0x3fb4000000000000, align 4
@FACT = dso_local global float 0xc0e01d0000000000, align 4
@EVAL1 = dso_local global float 0x4057c21fc0000000, align 4
@EVAL2 = dso_local global float 0x4041475ce0000000, align 4
@EVAL3 = dso_local global float 0x4041475ce0000000, align 4
@CONV1 = dso_local global float 0x406d200000000000, align 4
@CONV2 = dso_local global float 0x40affe0000000000, align 4
@MAX = dso_local global i32 1000000000, align 4
@TWO = dso_local global i32 2, align 4
@THREE = dso_local global i32 3, align 4
@FIVE = dso_local global i32 5, align 4
define dso_local float @float_abs(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  store float 0x0, float* %3, align 4
  store float %0, float* %2, align 4
  br label %4

4:
  %5 = load float, float* %2, align 4
  %6 = fcmp olt float %5, 0.000000
  %7 = icmp ne i1 %6, 0
  br i1 %7,  label %8,   label %12

8:
  %9 = load float, float* %2, align 4
  %10 = sub nsw float 0, %9
  %11 = sitofp i32 %10 to float
  store float %11, float* %3, align 4
  br label %14

12:
  %13 = load float, float* %2, align 4
  store float %13, float* %3, align 4
  br label %14

14:
  %15 = load i32, i32* %3, align 4
  ret i32 %15
}
define dso_local float @circle_area(i32 %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca float, align 4
  store float 0x0, float* %3, align 4
  store i32 %0, i32* %2, align 4
  %4 = load i32, i32* %2, align 4
  %5 = mul nsw float 3.141593, %4
  %6 = load i32, i32* %2, align 4
  %7 = mul nsw i32 %5, %6
  %8 = load i32, i32* %2, align 4
  %9 = load i32, i32* %2, align 4
  %10 = mul nsw i32 %8, %9
  %11 = mul nsw float %10, 3
  %12 = add nsw i32 %7, %11
  %13 = sdiv i32 %12, 2
  %14 = sitofp i32 %13 to float
  store float %14, float* %3, align 4
  br label %15

15:
  %16 = load i32, i32* %3, align 4
  ret i32 %16
}
define dso_local i32 @float_eq(float %0, float %1) #0 {
  %3 = alloca float, align 4
  %4 = alloca float, align 4
  %5 = alloca i32, align 4
  store i32 0, i32* %5, align 4
  store float %0, float* %3, align 4
  store float %1, float* %4, align 4
  br label %6

6:
  %7 = load float, float* %3, align 4
  %8 = load float, float* %4, align 4
  %9 = sub nsw float %7, %8
  %10 = call f32 @float_abs(i32 %9)
  %11 = icmp slt float %10, 0.000001
  %12 = icmp ne i1 %11, 0
  br i1 %12,  label %13,   label %14

13:
  store i32 1, i32* %5, align 4
  br label %16

14:
  store i32 0, i32* %5, align 4
  br label %16

15:
  br label %16

16:
  %17 = load i32, i32* %5, align 4
  ret i32 %17
}
define dso_local void @error() #0 {
  %1 = alloca i32, align 4
  call void  @putch(i32 101)
  call void  @putch(i32 114)
  call void  @putch(i32 114)
  call void  @putch(i32 111)
  call void  @putch(i32 114)
  call void  @putch(i32 10)
  br label %2

2:
  %3 = load i32, i32* %1, align 4
  ret void
}
define dso_local void @ok() #0 {
  %1 = alloca i32, align 4
  call void  @putch(i32 111)
  call void  @putch(i32 107)
  call void  @putch(i32 10)
  br label %2

2:
  %3 = load i32, i32* %1, align 4
  ret void
}
define dso_local void @assert(i32 %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  br label %4

4:
  %5 = load i32, i32* %2, align 4
  %6 = icmp ne i32 0, %5
  br i1 %6,  label %7,   label %8

7:
  store i32 0, i32* %3, align 4
  br label %9

8:
  store i32 1, i32* %3, align 4
  br label %9

9:
  %10 = load i32, i32* %3, align 4
  %11 = icmp ne i32 %10, 0
  br i1 %11,  label %12,   label %13

12:
  call void @error()
  br label %14

13:
  call void @ok()
  br label %14

14:
  br label %15

15:
  %16 = load i32, i32* %3, align 4
  ret void
}
define dso_local void @assert_not(i32 %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  br label %4

4:
  %5 = load i32, i32* %2, align 4
  %6 = icmp ne i32 %5, 0
  %7 = icmp ne i1 %6, 0
  br i1 %7,  label %8,   label %9

8:
  call void @error()
  br label %10

9:
  call void @ok()
  br label %10

10:
  br label %11

11:
  %12 = load i32, i32* %3, align 4
  ret void
}
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca [10 x float], align 16
  %5 = alloca i32, align 4
  %6 = alloca float, align 4
  %7 = alloca float, align 4
  %8 = alloca float, align 4
  store i32 0, i32* %1, align 4
  %9 = call i32 @float_eq(float @HEX2, float @FACT)
  call void @assert_not(i32 %9)
  %10 = call i32 @float_eq(float @EVAL1, float @EVAL2)
  call void @assert_not(i32 %10)
  %11 = call i32 @float_eq(float @EVAL2, float @EVAL3)
  call void @assert(i32 %11)
  %12 = call f32 @circle_area(float @RADIUS)
  %13 = call f32 @circle_area(i32 @FIVE)
  %14 = call i32 @float_eq(float %12, float %13)
  call void @assert(i32 %14)
  %15 = call i32 @float_eq(float @CONV1, float @CONV2)
  call void @assert_not(i32 %15)
  br label %16

16:
  %17 = icmp ne float 1.500000, 0.000000
  br i1 %17,  label %18,   label %19

18:
  call void @ok()
  br label %19

19:
  br label %20

20:
  %21 = icmp ne float 3.300000, 0.000000
  br i1 %21,  label %22,   label %23

22:
  call void @ok()
  br label %23

23:
  br label %24

24:
  %25 = icmp ne float 0.000000, 0.000000
  br i1 %25,  label %26,   label %29

26:
  %27 = icmp ne i32 3, 0
  br i1 %27,  label %28,   label %29

28:
  store i32 1, i32* %1, align 4
  br label %30

29:
  store i32 0, i32* %1, align 4
  br label %30

30:
  %31 = load i32, i32* %1, align 4
  %32 = icmp ne i32 %31, 0
  br i1 %32,  label %33,   label %34

33:
  call void @error()
  br label %34

34:
  br label %35

35:
  %36 = icmp ne i32 0, 0
  br i1 %36,  label %39,   label %37

37:
  %38 = icmp ne float 0.300000, 0.000000
  br i1 %38,  label %39,   label %40

39:
  store i32 1, i32* %1, align 4
  br label %41

40:
  store i32 0, i32* %1, align 4
  br label %41

41:
  %42 = load i32, i32* %1, align 4
  %43 = icmp ne i32 %42, 0
  br i1 %43,  label %44,   label %45

44:
  call void @ok()
  br label %45

45:
  store i32 1, i32* %2, align 4
  store i32 0, i32* %3, align 4
  %46 = bitcast [10 x float]* %4 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %46, i8 0, i64 40, i1 false)
  %47 = bitcast [10 x float]* %4 to i32*
  %48 = getelementptr inbounds i32, i32* %47, i32 0
  store i32 1, i32* %48, align 4
  %49 = getelementptr inbounds i32, i32* %47, i32 1
  store i32 2, i32* %49, align 4
  %50 = bitcast [10 x float]* %4 to i32*
  %51 = getelementptr inbounds i32, i32* %50, i32 0
  %52 = call i32 (...) @getfarray(i32* %51)
  store i32 %52, i32* %5, align 4
  br label %53

53:
  %54 = load i32, i32* %2, align 4
  %55 = icmp slt i32 %54, 1000000000
  %56 = icmp ne i1 %55, 0
  br i1 %56,  label %57,   label %83

57:
  %58 = call f32 (...) @getfloat()
  store float %58, float* %6, align 4
  %59 = load float, float* %6, align 4
  %60 = mul nsw float 3.141593, %59
  %61 = load float, float* %6, align 4
  %62 = mul nsw float %60, %61
  %63 = sitofp i32 %62 to float
  store float %63, float* %7, align 4
  %64 = load float, float* %6, align 4
  %65 = call f32 @circle_area(float %64)
  store float %65, float* %8, align 4
  %66 = load i32, i32* %3, align 4
  %67 = add nsw i32 0, %66
  %68 = bitcast [10 x float]* %4 to i32*
  %69 = getelementptr inbounds i32, i32* %68, i32 %67
  %70 = load i32, i32* %69, align 4
  %71 = load float, float* %6, align 4
  %72 = add nsw float %70, %71
  %73 = load i32, i32* %3, align 4
  %74 = add nsw i32 0, %73
  %75 = bitcast [10 x float]* %4 to i32*
  %76 = getelementptr inbounds i32, i32* %75, i32 %74
  store i32 %72, i32*  %76, align 4
  %77 = load float, float* %7, align 4
  call void  @putfloat(float %77)
  call void  @putch(i32 32)
  %78 = load float, float* %8, align 4
  call void  @putint(float %78)
  call void  @putch(i32 10)
  %79 = load i32, i32* %2, align 4
  %80 = mul nsw float %79, 10
  store i32 %80, i32* %2, align 4
  %81 = load i32, i32* %3, align 4
  %82 = add nsw i32 %81, 1
  store i32 %82, i32* %3, align 4
  br label %53

83:
  %84 = load i32, i32* %5, align 4
  %85 = bitcast [10 x float]* %4 to i32*
  %86 = getelementptr inbounds i32, i32* %85, i32 0
  call void  @putfarray(i32 %84, i32* %86)
  store i32 0, i32* %1, align 4
  br label %87

87:
  %88 = load i32, i32* %1, align 4
  ret i32 %88
}
declare void @putint(i32) #1
declare void @putch(i32) #1
declare f32 @getfloat(...) #1
declare void @putfloat(f32) #1
declare i32 @getfarray(f32*) #1
declare void @putfarray(i32,f32*) #1

declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #1
