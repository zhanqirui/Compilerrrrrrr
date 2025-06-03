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
  %6 = fcmp olt float %5, 0x0
  %7 = icmp ne i1 %6, 0
  br i1 %7,  label %8,   label %11

8:
  %9 = load float, float* %2, align 4
  %10 = fsub float 0x0, %9
  store float %10, float* %3, align 4
  br label %13

11:
  %12 = load float, float* %2, align 4
  store float %12, float* %3, align 4
  br label %13

13:
  %14 = load float, float* %3, align 4
  ret float %14
}
define dso_local float @circle_area(i32 %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca float, align 4
  store float 0x0, float* %3, align 4
  store i32 %0, i32* %2, align 4
  %4 = load i32, i32* %2, align 4
  %5 = sitofp i32 %4 to float
  %6 = fmul float 0x400921fb60000000, %5
  %7 = load i32, i32* %2, align 4
  %8 = sitofp i32 %7 to float
  %9 = fmul float %6, %8
  %10 = load i32, i32* %2, align 4
  %11 = load i32, i32* %2, align 4
  %12 = mul nsw i32 %10, %11
  %13 = sitofp i32 %12 to float
  %14 = fmul float %13, 0x400921fb60000000
  %15 = fadd float %9, %14
  %16 = sitofp i32 2 to float
  %17 = fdiv float %15, %16
  store float %17, float* %3, align 4
  br label %18

18:
  %19 = load float, float* %3, align 4
  ret float %19
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
  %9 = fsub float %7, %8
  %10 = call float @float_abs(float %9)
  %11 = fcmp olt float %10, 0x3eb0c6f7a0000000
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
  store i32 0, i32* %1, align 4
  %8 = call i32 @float_eq(float 0x3fb4000000000000, float 0xc0e01d0000000000)
  call void @assert_not(i32 %8)
  %9 = call i32 @float_eq(float 0x4057c21fc0000000, float 0x4041475ce0000000)
  call void @assert_not(i32 %9)
  %10 = call i32 @float_eq(float 0x4041475ce0000000, float 0x4041475ce0000000)
  call void @assert(i32 %10)
  %11 = call i32 @float_eq(float 0x406d200000000000, float 0x40affe0000000000)
  call void @assert_not(i32 %11)
  br label %12

12:
  %13 = icmp ne float 1.500000, 0.000000
  br i1 %13,  label %14,   label %15

14:
  call void @ok()
  br label %15

15:
  br label %16

16:
  %17 = icmp ne float 3.300000, 0.000000
  br i1 %17,  label %18,   label %19

18:
  call void @ok()
  br label %19

19:
  br label %20

20:
  %21 = icmp ne float 0.000000, 0.000000
  br i1 %21,  label %22,   label %25

22:
  %23 = icmp ne i32 3, 0
  br i1 %23,  label %24,   label %25

24:
  store i32 1, i32* %1, align 4
  br label %26

25:
  store i32 0, i32* %1, align 4
  br label %26

26:
  %27 = load i32, i32* %1, align 4
  %28 = icmp ne i32 %27, 0
  br i1 %28,  label %29,   label %30

29:
  call void @error()
  br label %30

30:
  br label %31

31:
  %32 = icmp ne i32 0, 0
  br i1 %32,  label %35,   label %33

33:
  %34 = icmp ne float 0.300000, 0.000000
  br i1 %34,  label %35,   label %36

35:
  store i32 1, i32* %1, align 4
  br label %37

36:
  store i32 0, i32* %1, align 4
  br label %37

37:
  %38 = load i32, i32* %1, align 4
  %39 = icmp ne i32 %38, 0
  br i1 %39,  label %40,   label %41

40:
  call void @ok()
  br label %41

41:
  store i32 1, i32* %2, align 4
  store i32 0, i32* %3, align 4
  %42 = bitcast [10 x float]* %4 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %42, i8 0, i64 40, i1 false)
  %43 = bitcast [10 x float]* %4 to float*
  %44 = getelementptr inbounds float, float* %43, i32 0
  store float 0x3ff0000000000000, float* %44, align 4
  %45 = getelementptr inbounds float, float* %43, i32 1
  store float 0x4000000000000000, float* %45, align 4
  %46 = bitcast [10 x float]* %4 to float*
  %47 = getelementptr inbounds float, float* %46, i32 0
  %48 = call i32 (...) @getfarray(float* %47)
  store i32 %48, i32* %5, align 4
  br label %49

49:
  %50 = load i32, i32* %2, align 4
  %51 = icmp slt i32 %50, 1000000000
  %52 = icmp ne i1 %51, 0
  br i1 %52,  label %53,   label %77

53:
  %54 = call float (...) @getfloat()
  store float %54, float* %6, align 4
  %55 = load float, float* %6, align 4
  %56 = fmul float 0x400921fb60000000, %55
  %57 = load float, float* %6, align 4
  %58 = fmul float %56, %57
  store float %58, float* %7, align 4
  %59 = load i32, i32* %3, align 4
  %60 = add nsw i32 0, %59
  %61 = bitcast [10 x float]* %4 to float*
  %62 = getelementptr inbounds float, float* %61, i32 %60
  %63 = load float, float* %62, align 4
  %64 = load float, float* %6, align 4
  %65 = fadd float %63, %64
  %66 = load i32, i32* %3, align 4
  %67 = add nsw i32 0, %66
  %68 = bitcast [10 x float]* %4 to float*
  %69 = getelementptr inbounds float, float* %68, i32 %67
  store float %65, float*  %69, align 4
  %70 = load float, float* %7, align 4
  call void  @putfloat(float %70)
  call void  @putch(i32 32)
  call void  @putch(i32 10)
  %71 = load i32, i32* %2, align 4
  %72 = sitofp i32 %71 to float
  %73 = fmul float %72, 0x4024000000000000
  %74 = fptosi float %73 to i32
  store i32 %74, i32* %2, align 4
  %75 = load i32, i32* %3, align 4
  %76 = add nsw i32 %75, 1
  store i32 %76, i32* %3, align 4
  br label %49

77:
  %78 = load i32, i32* %5, align 4
  %79 = bitcast [10 x float]* %4 to float*
  %80 = getelementptr inbounds float, float* %79, i32 0
  call void  @putfarray(i32 %78, float* %80)
  store i32 0, i32* %1, align 4
  br label %81

81:
  %82 = load i32, i32* %1, align 4
  ret i32 %82
}
declare void @putch(i32) #1
declare float @getfloat(...) #1
declare void @putfloat(float) #1
declare i32 @getfarray(float*) #1
declare void @putfarray(i32,float*) #1

declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #1
