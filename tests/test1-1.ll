@MAX_DIM_X = dso_local global i32 8, align 4
@MAX_DIM_Y = dso_local global i32 8, align 4
@test_block = dso_local global [8 x [8 x float]] zeroinitializer, align 16
@test_dct = dso_local global [8 x [8 x float]] zeroinitializer, align 16
@test_idct = dso_local global [8 x [8 x float]] zeroinitializer, align 16
@PI = dso_local global float 0x400921fb60000000, align 4
@TWO_PI = dso_local global float 0x401921fb60000000, align 4
@EPSILON = dso_local global float 0x3eb0c6f7a0000000, align 4
define dso_local float @my_fabs(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  %4 = alloca i32, align 4
  store float 0x0, float* %3, align 4
  store float %0, float* %2, align 4
  br label %5

5:
  %6 = load float, float* %2, align 4
  %7 = sitofp i32 0 to float
  %8 = fcmp ogt float %6, %7
  %9 = icmp ne i1 %8, 0
  br i1 %9,  label %10,   label %12

10:
  %11 = load float, float* %2, align 4
  store float %11, float* %3, align 4
  br label %15

12:
  %13 = load float, float* %2, align 4
  %14 = fsub float 0x0, %13
  store float %14, float* %3, align 4
  br label %15

15:
  %16 = load float, float* %3, align 4
  ret float %16
}
define dso_local float @p(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  %4 = alloca i32, align 4
  store float 0x0, float* %3, align 4
  store float %0, float* %2, align 4
  %5 = load float, float* %2, align 4
  %6 = sitofp i32 3 to float
  %7 = fmul float %6, %5
  %8 = load float, float* %2, align 4
  %9 = sitofp i32 4 to float
  %10 = fmul float %9, %8
  %11 = load float, float* %2, align 4
  %12 = fmul float %10, %11
  %13 = load float, float* %2, align 4
  %14 = fmul float %12, %13
  %15 = fsub float %7, %14
  store float %15, float* %3, align 4
  br label %16

16:
  %17 = load float, float* %3, align 4
  ret float %17
}
define dso_local float @my_sin_impl(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  %4 = alloca i32, align 4
  store float 0x0, float* %3, align 4
  store float %0, float* %2, align 4
  br label %5

5:
  %6 = load float, float* %2, align 4
  %7 = call float @my_fabs(float %6)
  %8 = fcmp ole float %7, 0x3eb0c6f7a0000000
  %9 = icmp ne i1 %8, 0
  br i1 %9,  label %10,   label %12

10:
  %11 = load float, float* %2, align 4
  store float %11, float* %3, align 4
  br label %17

12:
  %13 = load float, float* %2, align 4
  %14 = fdiv float %13, 0x4008000000000000
  %15 = call float @my_sin_impl(float %14)
  %16 = call float @p(float %15)
  store float %16, float* %3, align 4
  br label %17

17:
  %18 = load float, float* %3, align 4
  ret float %18
}
define dso_local float @my_sin(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store float 0x0, float* %3, align 4
  store float %0, float* %2, align 4
  br label %6

6:
  %7 = load float, float* %2, align 4
  %8 = fcmp ogt float %7, 0x401921fb60000000
  %9 = icmp ne i1 %8, 0
  br i1 %9,  label %15,   label %10

10:
  %11 = load float, float* %2, align 4
  %12 = fsub float 0x0, 0x401921fb60000000
  %13 = fcmp olt float %11, %12
  %14 = icmp ne i1 %13, 0
  br i1 %14,  label %15,   label %16

15:
  store i32 1, i32* %4, align 4
  br label %17

16:
  store i32 0, i32* %4, align 4
  br label %17

17:
  %18 = load i32, i32* %4, align 4
  %19 = icmp ne i32 %18, 0
  br i1 %19,  label %20,   label %29

20:
  %21 = load float, float* %2, align 4
  %22 = fdiv float %21, 0x401921fb60000000
  %23 = fptosi float %22 to i32
  store i32 %23, i32* %5, align 4
  %24 = load float, float* %2, align 4
  %25 = load i32, i32* %5, align 4
  %26 = sitofp i32 %25 to float
  %27 = fmul float %26, 0x401921fb60000000
  %28 = fsub float %24, %27
  store float %28, float* %2, align 4
  br label %29

29:
  br label %30

30:
  %31 = load float, float* %2, align 4
  %32 = fcmp ogt float %31, 0x400921fb60000000
  %33 = icmp ne i1 %32, 0
  br i1 %33,  label %34,   label %37

34:
  %35 = load float, float* %2, align 4
  %36 = fsub float %35, 0x401921fb60000000
  store float %36, float* %2, align 4
  br label %37

37:
  br label %38

38:
  %39 = load float, float* %2, align 4
  %40 = fsub float 0x0, 0x400921fb60000000
  %41 = fcmp olt float %39, %40
  %42 = icmp ne i1 %41, 0
  br i1 %42,  label %43,   label %46

43:
  %44 = load float, float* %2, align 4
  %45 = fadd float %44, 0x401921fb60000000
  store float %45, float* %2, align 4
  br label %46

46:
  %47 = load float, float* %2, align 4
  %48 = call float @my_sin_impl(float %47)
  store float %48, float* %3, align 4
  br label %49

49:
  %50 = load float, float* %3, align 4
  ret float %50
}
define dso_local float @my_cos(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  %4 = alloca i32, align 4
  store float 0x0, float* %3, align 4
  store float %0, float* %2, align 4
  %5 = load float, float* %2, align 4
  %6 = fadd float %5, 0x3ff0000000000000
  %7 = call float @my_sin(float %6)
  store float %7, float* %3, align 4
  br label %8

8:
  %9 = load float, float* %3, align 4
  ret float %9
}
define dso_local void @write_mat(float* %0, i32 %1, i32 %2) #0 {
  %4 = alloca float*, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  store float* %0, float**  %4, align 4
  store i32 %1, i32* %5, align 4
  store i32 %2, i32* %6, align 4
  store i32 0, i32* %9, align 4
  br label %11

11:
  %12 = load i32, i32* %9, align 4
  %13 = load i32, i32* %5, align 4
  %14 = icmp slt i32 %12, %13
  %15 = icmp ne i1 %14, 0
  br i1 %15,  label %16,   label %43

16:
  %17 = load i32, i32* %9, align 4
  %18 = mul nsw i32 %17, 8
  %19 = add nsw i32 %18, 0
  %20 = load float*, float** %4, align 4
  %21 = bitcast float* %20 to float*
  %22 = getelementptr inbounds float, float* %21, i32 %19
  %23 = load float, float* %22, align 4
  call void  @putfloat(float %23)
  store i32 1, i32* %10, align 4
  br label %24

24:
  %25 = load i32, i32* %10, align 4
  %26 = load i32, i32* %6, align 4
  %27 = icmp slt i32 %25, %26
  %28 = icmp ne i1 %27, 0
  br i1 %28,  label %29,   label %40

29:
  call void  @putch(i32 32)
  %30 = load i32, i32* %9, align 4
  %31 = mul nsw i32 %30, 8
  %32 = load i32, i32* %10, align 4
  %33 = add nsw i32 %31, %32
  %34 = load float*, float** %4, align 4
  %35 = bitcast float* %34 to float*
  %36 = getelementptr inbounds float, float* %35, i32 %33
  %37 = load float, float* %36, align 4
  call void  @putfloat(float %37)
  %38 = load i32, i32* %10, align 4
  %39 = add nsw i32 %38, 1
  store i32 %39, i32* %10, align 4
  br label %24

40:
  call void  @putch(i32 10)
  %41 = load i32, i32* %9, align 4
  %42 = add nsw i32 %41, 1
  store i32 %42, i32* %9, align 4
  br label %11

43:
  call void  @putch(i32 10)
  br label %44

44:
  %45 = load i32, i32* %7, align 4
  ret void
}
define dso_local void @dct(float* %0, float* %1, i32 %2, i32 %3) #0 {
  %5 = alloca float*, align 4
  %6 = alloca float*, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  store float* %0, float**  %5, align 4
  store float* %1, float**  %6, align 4
  store i32 %2, i32* %7, align 4
  store i32 %3, i32* %8, align 4
  store i32 0, i32* %11, align 4
  br label %15

15:
  %16 = load i32, i32* %11, align 4
  %17 = load i32, i32* %7, align 4
  %18 = icmp slt i32 %16, %17
  %19 = icmp ne i1 %18, 0
  br i1 %19,  label %20,   label %106

20:
  store i32 0, i32* %12, align 4
  br label %21

21:
  %22 = load i32, i32* %12, align 4
  %23 = load i32, i32* %8, align 4
  %24 = icmp slt i32 %22, %23
  %25 = icmp ne i1 %24, 0
  br i1 %25,  label %26,   label %103

26:
  %27 = load i32, i32* %11, align 4
  %28 = mul nsw i32 %27, 8
  %29 = load i32, i32* %12, align 4
  %30 = add nsw i32 %28, %29
  %31 = load float*, float** %5, align 4
  %32 = bitcast float* %31 to float*
  %33 = getelementptr inbounds float, float* %32, i32 %30
  %34 = sitofp i32 0 to float
  store float %34, float*  %33, align 4
  store i32 0, i32* %13, align 4
  br label %35

35:
  %36 = load i32, i32* %13, align 4
  %37 = load i32, i32* %7, align 4
  %38 = icmp slt i32 %36, %37
  %39 = icmp ne i1 %38, 0
  br i1 %39,  label %40,   label %100

40:
  store i32 0, i32* %14, align 4
  br label %41

41:
  %42 = load i32, i32* %14, align 4
  %43 = load i32, i32* %8, align 4
  %44 = icmp slt i32 %42, %43
  %45 = icmp ne i1 %44, 0
  br i1 %45,  label %46,   label %97

46:
  %47 = load i32, i32* %11, align 4
  %48 = mul nsw i32 %47, 8
  %49 = load i32, i32* %12, align 4
  %50 = add nsw i32 %48, %49
  %51 = load float*, float** %5, align 4
  %52 = bitcast float* %51 to float*
  %53 = getelementptr inbounds float, float* %52, i32 %50
  %54 = load float, float* %53, align 4
  %55 = load i32, i32* %13, align 4
  %56 = mul nsw i32 %55, 8
  %57 = load i32, i32* %14, align 4
  %58 = add nsw i32 %56, %57
  %59 = load float*, float** %6, align 4
  %60 = bitcast float* %59 to float*
  %61 = getelementptr inbounds float, float* %60, i32 %58
  %62 = load float, float* %61, align 4
  %63 = load i32, i32* %7, align 4
  %64 = sitofp i32 %63 to float
  %65 = fdiv float 0x400921fb60000000, %64
  %66 = load i32, i32* %13, align 4
  %67 = sitofp i32 %66 to float
  %68 = fadd float %67, 0x0
  %69 = fmul float %65, %68
  %70 = load i32, i32* %11, align 4
  %71 = sitofp i32 %70 to float
  %72 = fmul float %69, %71
  %73 = call float @my_cos(float %72)
  %74 = fmul float %62, %73
  %75 = load i32, i32* %8, align 4
  %76 = sitofp i32 %75 to float
  %77 = fdiv float 0x400921fb60000000, %76
  %78 = load i32, i32* %14, align 4
  %79 = sitofp i32 %78 to float
  %80 = fadd float %79, 0x0
  %81 = fmul float %77, %80
  %82 = load i32, i32* %12, align 4
  %83 = sitofp i32 %82 to float
  %84 = fmul float %81, %83
  %85 = call float @my_cos(float %84)
  %86 = fmul float %74, %85
  %87 = fadd float %54, %86
  %88 = load i32, i32* %11, align 4
  %89 = mul nsw i32 %88, 8
  %90 = load i32, i32* %12, align 4
  %91 = add nsw i32 %89, %90
  %92 = load float*, float** %5, align 4
  %93 = bitcast float* %92 to float*
  %94 = getelementptr inbounds float, float* %93, i32 %91
  store float %87, float*  %94, align 4
  %95 = load i32, i32* %14, align 4
  %96 = add nsw i32 %95, 1
  store i32 %96, i32* %14, align 4
  br label %41

97:
  %98 = load i32, i32* %13, align 4
  %99 = add nsw i32 %98, 1
  store i32 %99, i32* %13, align 4
  br label %35

100:
  %101 = load i32, i32* %12, align 4
  %102 = add nsw i32 %101, 1
  store i32 %102, i32* %12, align 4
  br label %21

103:
  %104 = load i32, i32* %11, align 4
  %105 = add nsw i32 %104, 1
  store i32 %105, i32* %11, align 4
  br label %15

106:
  br label %107

107:
  %108 = load i32, i32* %9, align 4
  ret void
}
define dso_local void @idct(float* %0, float* %1, i32 %2, i32 %3) #0 {
  %5 = alloca float*, align 4
  %6 = alloca float*, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  store float* %0, float**  %5, align 4
  store float* %1, float**  %6, align 4
  store i32 %2, i32* %7, align 4
  store i32 %3, i32* %8, align 4
  store i32 0, i32* %11, align 4
  br label %15

15:
  %16 = load i32, i32* %11, align 4
  %17 = load i32, i32* %7, align 4
  %18 = icmp slt i32 %16, %17
  %19 = icmp ne i1 %18, 0
  br i1 %19,  label %20,   label %204

20:
  store i32 0, i32* %12, align 4
  br label %21

21:
  %22 = load i32, i32* %12, align 4
  %23 = load i32, i32* %8, align 4
  %24 = icmp slt i32 %22, %23
  %25 = icmp ne i1 %24, 0
  br i1 %25,  label %26,   label %201

26:
  %27 = mul nsw i32 0, 8
  %28 = add nsw i32 %27, 0
  %29 = load float*, float** %6, align 4
  %30 = bitcast float* %29 to float*
  %31 = getelementptr inbounds float, float* %30, i32 %28
  %32 = load float, float* %31, align 4
  %33 = sitofp i32 0 to float
  %34 = fmul float %33, %32
  %35 = load i32, i32* %11, align 4
  %36 = mul nsw i32 %35, 8
  %37 = load i32, i32* %12, align 4
  %38 = add nsw i32 %36, %37
  %39 = load float*, float** %5, align 4
  %40 = bitcast float* %39 to float*
  %41 = getelementptr inbounds float, float* %40, i32 %38
  store float %34, float*  %41, align 4
  store i32 1, i32* %13, align 4
  br label %42

42:
  %43 = load i32, i32* %13, align 4
  %44 = load i32, i32* %7, align 4
  %45 = icmp slt i32 %43, %44
  %46 = icmp ne i1 %45, 0
  br i1 %46,  label %47,   label %75

47:
  %48 = load i32, i32* %11, align 4
  %49 = mul nsw i32 %48, 8
  %50 = load i32, i32* %12, align 4
  %51 = add nsw i32 %49, %50
  %52 = load float*, float** %5, align 4
  %53 = bitcast float* %52 to float*
  %54 = getelementptr inbounds float, float* %53, i32 %51
  %55 = load float, float* %54, align 4
  %56 = load i32, i32* %13, align 4
  %57 = mul nsw i32 %56, 8
  %58 = add nsw i32 %57, 0
  %59 = load float*, float** %6, align 4
  %60 = bitcast float* %59 to float*
  %61 = getelementptr inbounds float, float* %60, i32 %58
  %62 = load float, float* %61, align 4
  %63 = sitofp i32 0 to float
  %64 = fmul float %63, %62
  %65 = fadd float %55, %64
  %66 = load i32, i32* %11, align 4
  %67 = mul nsw i32 %66, 8
  %68 = load i32, i32* %12, align 4
  %69 = add nsw i32 %67, %68
  %70 = load float*, float** %5, align 4
  %71 = bitcast float* %70 to float*
  %72 = getelementptr inbounds float, float* %71, i32 %69
  store float %65, float*  %72, align 4
  %73 = load i32, i32* %13, align 4
  %74 = add nsw i32 %73, 1
  store i32 %74, i32* %13, align 4
  br label %42

75:
  store i32 1, i32* %14, align 4
  br label %76

76:
  %77 = load i32, i32* %14, align 4
  %78 = load i32, i32* %8, align 4
  %79 = icmp slt i32 %77, %78
  %80 = icmp ne i1 %79, 0
  br i1 %80,  label %81,   label %109

81:
  %82 = load i32, i32* %11, align 4
  %83 = mul nsw i32 %82, 8
  %84 = load i32, i32* %12, align 4
  %85 = add nsw i32 %83, %84
  %86 = load float*, float** %5, align 4
  %87 = bitcast float* %86 to float*
  %88 = getelementptr inbounds float, float* %87, i32 %85
  %89 = load float, float* %88, align 4
  %90 = mul nsw i32 0, 8
  %91 = load i32, i32* %14, align 4
  %92 = add nsw i32 %90, %91
  %93 = load float*, float** %6, align 4
  %94 = bitcast float* %93 to float*
  %95 = getelementptr inbounds float, float* %94, i32 %92
  %96 = load float, float* %95, align 4
  %97 = sitofp i32 0 to float
  %98 = fmul float %97, %96
  %99 = fadd float %89, %98
  %100 = load i32, i32* %11, align 4
  %101 = mul nsw i32 %100, 8
  %102 = load i32, i32* %12, align 4
  %103 = add nsw i32 %101, %102
  %104 = load float*, float** %5, align 4
  %105 = bitcast float* %104 to float*
  %106 = getelementptr inbounds float, float* %105, i32 %103
  store float %99, float*  %106, align 4
  %107 = load i32, i32* %14, align 4
  %108 = add nsw i32 %107, 1
  store i32 %108, i32* %14, align 4
  br label %76

109:
  store i32 1, i32* %13, align 4
  br label %110

110:
  %111 = load i32, i32* %13, align 4
  %112 = load i32, i32* %7, align 4
  %113 = icmp slt i32 %111, %112
  %114 = icmp ne i1 %113, 0
  br i1 %114,  label %115,   label %175

115:
  store i32 1, i32* %14, align 4
  br label %116

116:
  %117 = load i32, i32* %14, align 4
  %118 = load i32, i32* %8, align 4
  %119 = icmp slt i32 %117, %118
  %120 = icmp ne i1 %119, 0
  br i1 %120,  label %121,   label %172

121:
  %122 = load i32, i32* %11, align 4
  %123 = mul nsw i32 %122, 8
  %124 = load i32, i32* %12, align 4
  %125 = add nsw i32 %123, %124
  %126 = load float*, float** %5, align 4
  %127 = bitcast float* %126 to float*
  %128 = getelementptr inbounds float, float* %127, i32 %125
  %129 = load float, float* %128, align 4
  %130 = load i32, i32* %13, align 4
  %131 = mul nsw i32 %130, 8
  %132 = load i32, i32* %14, align 4
  %133 = add nsw i32 %131, %132
  %134 = load float*, float** %6, align 4
  %135 = bitcast float* %134 to float*
  %136 = getelementptr inbounds float, float* %135, i32 %133
  %137 = load float, float* %136, align 4
  %138 = load i32, i32* %7, align 4
  %139 = sitofp i32 %138 to float
  %140 = fdiv float 0x400921fb60000000, %139
  %141 = load i32, i32* %11, align 4
  %142 = sitofp i32 %141 to float
  %143 = fadd float %142, 0x0
  %144 = fmul float %140, %143
  %145 = load i32, i32* %13, align 4
  %146 = sitofp i32 %145 to float
  %147 = fmul float %144, %146
  %148 = call float @my_cos(float %147)
  %149 = fmul float %137, %148
  %150 = load i32, i32* %8, align 4
  %151 = sitofp i32 %150 to float
  %152 = fdiv float 0x400921fb60000000, %151
  %153 = load i32, i32* %12, align 4
  %154 = sitofp i32 %153 to float
  %155 = fadd float %154, 0x0
  %156 = fmul float %152, %155
  %157 = load i32, i32* %14, align 4
  %158 = sitofp i32 %157 to float
  %159 = fmul float %156, %158
  %160 = call float @my_cos(float %159)
  %161 = fmul float %149, %160
  %162 = fadd float %129, %161
  %163 = load i32, i32* %11, align 4
  %164 = mul nsw i32 %163, 8
  %165 = load i32, i32* %12, align 4
  %166 = add nsw i32 %164, %165
  %167 = load float*, float** %5, align 4
  %168 = bitcast float* %167 to float*
  %169 = getelementptr inbounds float, float* %168, i32 %166
  store float %162, float*  %169, align 4
  %170 = load i32, i32* %14, align 4
  %171 = add nsw i32 %170, 1
  store i32 %171, i32* %14, align 4
  br label %116

172:
  %173 = load i32, i32* %13, align 4
  %174 = add nsw i32 %173, 1
  store i32 %174, i32* %13, align 4
  br label %110

175:
  %176 = load i32, i32* %11, align 4
  %177 = mul nsw i32 %176, 8
  %178 = load i32, i32* %12, align 4
  %179 = add nsw i32 %177, %178
  %180 = load float*, float** %5, align 4
  %181 = bitcast float* %180 to float*
  %182 = getelementptr inbounds float, float* %181, i32 %179
  %183 = load float, float* %182, align 4
  %184 = fmul float %183, 0x4000000000000000
  %185 = load i32, i32* %7, align 4
  %186 = sitofp i32 %185 to float
  %187 = fdiv float %184, %186
  %188 = fmul float %187, 0x4000000000000000
  %189 = load i32, i32* %8, align 4
  %190 = sitofp i32 %189 to float
  %191 = fdiv float %188, %190
  %192 = load i32, i32* %11, align 4
  %193 = mul nsw i32 %192, 8
  %194 = load i32, i32* %12, align 4
  %195 = add nsw i32 %193, %194
  %196 = load float*, float** %5, align 4
  %197 = bitcast float* %196 to float*
  %198 = getelementptr inbounds float, float* %197, i32 %195
  store float %191, float*  %198, align 4
  %199 = load i32, i32* %12, align 4
  %200 = add nsw i32 %199, 1
  store i32 %200, i32* %12, align 4
  br label %21

201:
  %202 = load i32, i32* %11, align 4
  %203 = add nsw i32 %202, 1
  store i32 %203, i32* %11, align 4
  br label %15

204:
  br label %205

205:
  %206 = load i32, i32* %9, align 4
  ret void
}
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %7 = call i32 (...) @getint()
  store i32 %7, i32* %3, align 4
  %8 = call i32 (...) @getint()
  store i32 %8, i32* %4, align 4
  store i32 0, i32* %5, align 4
  br label %9

9:
  %10 = load i32, i32* %5, align 4
  %11 = load i32, i32* %3, align 4
  %12 = icmp slt i32 %10, %11
  %13 = icmp ne i1 %12, 0
  br i1 %13,  label %14,   label %33

14:
  store i32 0, i32* %6, align 4
  br label %15

15:
  %16 = load i32, i32* %6, align 4
  %17 = load i32, i32* %4, align 4
  %18 = icmp slt i32 %16, %17
  %19 = icmp ne i1 %18, 0
  br i1 %19,  label %20,   label %30

20:
  %21 = call float (...) @getfloat()
  %22 = load i32, i32* %5, align 4
  %23 = mul nsw i32 %22, 8
  %24 = load i32, i32* %6, align 4
  %25 = add nsw i32 %23, %24
  %26 = bitcast [8 x [8 x float]]* @test_block to float*
  %27 = getelementptr inbounds float, float* %26, i32 %25
  store float %21, float*  %27, align 4
  %28 = load i32, i32* %6, align 4
  %29 = add nsw i32 %28, 1
  store i32 %29, i32* %6, align 4
  br label %15

30:
  %31 = load i32, i32* %5, align 4
  %32 = add nsw i32 %31, 1
  store i32 %32, i32* %5, align 4
  br label %9

33:
  %34 = bitcast [8 x [8 x float]]* @test_dct to float*
  %35 = getelementptr inbounds float, float* %34, i32 0
  %36 = bitcast [8 x [8 x float]]* @test_block to float*
  %37 = getelementptr inbounds float, float* %36, i32 0
  %38 = load i32, i32* %3, align 4
  %39 = load i32, i32* %4, align 4
  call void @dct(float* %35, float* %37, i32 %38, i32 %39)
  %40 = bitcast [8 x [8 x float]]* @test_dct to float*
  %41 = getelementptr inbounds float, float* %40, i32 0
  %42 = load i32, i32* %3, align 4
  %43 = load i32, i32* %4, align 4
  call void @write_mat(float* %41, i32 %42, i32 %43)
  %44 = bitcast [8 x [8 x float]]* @test_idct to float*
  %45 = getelementptr inbounds float, float* %44, i32 0
  %46 = bitcast [8 x [8 x float]]* @test_dct to float*
  %47 = getelementptr inbounds float, float* %46, i32 0
  %48 = load i32, i32* %3, align 4
  %49 = load i32, i32* %4, align 4
  call void @idct(float* %45, float* %47, i32 %48, i32 %49)
  %50 = bitcast [8 x [8 x float]]* @test_idct to float*
  %51 = getelementptr inbounds float, float* %50, i32 0
  %52 = load i32, i32* %3, align 4
  %53 = load i32, i32* %4, align 4
  call void @write_mat(float* %51, i32 %52, i32 %53)
  store i32 0, i32* %1, align 4
  br label %54

54:
  %55 = load i32, i32* %1, align 4
  ret i32 %55
}
declare i32 @getint(...) #1
declare void @putch(i32) #1
declare float @getfloat(...) #1
declare void @putfloat(float) #1
