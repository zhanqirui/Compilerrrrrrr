@maxn = dso_local global i32 10005, align 4
@n = dso_local global i32 0, align 4
@m = dso_local global i32 0, align 4
@f = dso_local global [10005 x [20 x i32]] zeroinitializer, align 16
@dep = dso_local global [10005 x i32] zeroinitializer, align 16
@to = dso_local global [10005 x i32] zeroinitializer, align 16
@next = dso_local global [10005 x i32] zeroinitializer, align 16
@head = dso_local global [10005 x i32] zeroinitializer, align 16
@cnt = dso_local global i32 0, align 4
define dso_local i32 @quick_read() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %6 = call i32 (...) @getch()
  store i32 %6, i32* %3, align 4
  store i32 0, i32* %4, align 4
  store i32 0, i32* %5, align 4
  br label %7

7:
  %8 = load i32, i32* %3, align 4
  %9 = icmp slt i32 %8, 48
  %10 = icmp ne i1 %9, 0
  br i1 %10,  label %15,   label %11

11:
  %12 = load i32, i32* %3, align 4
  %13 = icmp sgt i32 %12, 57
  %14 = icmp ne i1 %13, 0
  br i1 %14,  label %15,   label %16

15:
  store i32 1, i32* %2, align 4
  br label %17

16:
  store i32 0, i32* %2, align 4
  br label %17

17:
  %18 = load i32, i32* %2, align 4
  %19 = icmp ne i32 %18, 0
  br i1 %19,  label %20,   label %28

20:
  br label %21

21:
  %22 = load i32, i32* %3, align 4
  %23 = icmp eq i32 %22, 45
  %24 = icmp ne i1 %23, 0
  br i1 %24,  label %25,   label %26

25:
  store i32 1, i32* %5, align 4
  br label %26

26:
  %27 = call i32 (...) @getch()
  store i32 %27, i32* %3, align 4
  br label %7

28:
  br label %29

29:
  %30 = load i32, i32* %3, align 4
  %31 = icmp sge i32 %30, 48
  %32 = icmp ne i1 %31, 0
  br i1 %32,  label %33,   label %38

33:
  %34 = load i32, i32* %3, align 4
  %35 = icmp sle i32 %34, 57
  %36 = icmp ne i1 %35, 0
  br i1 %36,  label %37,   label %38

37:
  store i32 1, i32* %2, align 4
  br label %39

38:
  store i32 0, i32* %2, align 4
  br label %39

39:
  %40 = load i32, i32* %2, align 4
  %41 = icmp ne i32 %40, 0
  br i1 %41,  label %42,   label %49

42:
  %43 = load i32, i32* %4, align 4
  %44 = mul nsw i32 %43, 10
  %45 = load i32, i32* %3, align 4
  %46 = add nsw i32 %44, %45
  %47 = sub nsw i32 %46, 48
  store i32 %47, i32* %4, align 4
  %48 = call i32 (...) @getch()
  store i32 %48, i32* %3, align 4
  br label %29

49:
  br label %50

50:
  %51 = load i32, i32* %5, align 4
  %52 = icmp ne i32 %51, 0
  %53 = icmp ne i1 %52, 0
  br i1 %53,  label %54,   label %57

54:
  %55 = load i32, i32* %4, align 4
  %56 = sub nsw i32 0, %55
  store i32 %56, i32* %1, align 4
  br label %60

57:
  %58 = load i32, i32* %4, align 4
  store i32 %58, i32* %1, align 4
  br label %60

59:
  br label %60

60:
  %61 = load i32, i32* %1, align 4
  ret i32 %61
}
define dso_local void @add_edge(i32 %0, i32 %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %7 = load i32, i32* %4, align 4
  %8 = load i32, i32* @cnt, align 4
  %9 = add nsw i32 0, %8
  %10 = bitcast [10005 x i32]* @to to i32*
  %11 = getelementptr inbounds i32, i32* %10, i32 %9
  store i32 %7, i32*  %11, align 4
  %12 = load i32, i32* %3, align 4
  %13 = add nsw i32 0, %12
  %14 = bitcast [10005 x i32]* @head to i32*
  %15 = getelementptr inbounds i32, i32* %14, i32 %13
  %16 = load i32, i32* %15, align 4
  %17 = load i32, i32* @cnt, align 4
  %18 = add nsw i32 0, %17
  %19 = bitcast [10005 x i32]* @next to i32*
  %20 = getelementptr inbounds i32, i32* %19, i32 %18
  store i32 %16, i32*  %20, align 4
  %21 = load i32, i32* @cnt, align 4
  %22 = load i32, i32* %3, align 4
  %23 = add nsw i32 0, %22
  %24 = bitcast [10005 x i32]* @head to i32*
  %25 = getelementptr inbounds i32, i32* %24, i32 %23
  store i32 %21, i32*  %25, align 4
  %26 = load i32, i32* @cnt, align 4
  %27 = add nsw i32 %26, 1
  store i32 %27, i32* @cnt, align 4
  %28 = load i32, i32* %3, align 4
  %29 = load i32, i32* %4, align 4
  %30 = mul nsw i32 %29, 20
  %31 = add nsw i32 %30, 0
  %32 = bitcast [10005 x [20 x i32]]* @f to i32*
  %33 = getelementptr inbounds i32, i32* %32, i32 %31
  store i32 %28, i32*  %33, align 4
  br label %34

34:
  %35 = load i32, i32* %5, align 4
  ret void
}
define dso_local void @init() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = add nsw i32 0, 0
  %5 = bitcast [10005 x i32]* @dep to i32*
  %6 = getelementptr inbounds i32, i32* %5, i32 %4
  store i32 1061109567, i32* %6, align 4
  store i32 1, i32* %3, align 4
  br label %7

7:
  %8 = load i32, i32* %3, align 4
  %9 = load i32, i32* @n, align 4
  %10 = icmp sle i32 %8, %9
  %11 = icmp ne i1 %10, 0
  br i1 %11,  label %12,   label %20

12:
  %13 = sub nsw i32 0, 1
  %14 = load i32, i32* %3, align 4
  %15 = add nsw i32 0, %14
  %16 = bitcast [10005 x i32]* @head to i32*
  %17 = getelementptr inbounds i32, i32* %16, i32 %15
  store i32 %13, i32*  %17, align 4
  %18 = load i32, i32* %3, align 4
  %19 = add nsw i32 %18, 1
  store i32 %19, i32* %3, align 4
  br label %7

20:
  br label %21

21:
  %22 = load i32, i32* %1, align 4
  ret void
}
define dso_local void @tree(i32 %0, i32 %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %9 = load i32, i32* %4, align 4
  %10 = load i32, i32* %3, align 4
  %11 = add nsw i32 0, %10
  %12 = bitcast [10005 x i32]* @dep to i32*
  %13 = getelementptr inbounds i32, i32* %12, i32 %11
  store i32 %9, i32*  %13, align 4
  store i32 0, i32* %7, align 4
  br label %14

14:
  %15 = load i32, i32* %3, align 4
  %16 = mul nsw i32 %15, 20
  %17 = load i32, i32* %7, align 4
  %18 = add nsw i32 %16, %17
  %19 = bitcast [10005 x [20 x i32]]* @f to i32*
  %20 = getelementptr inbounds i32, i32* %19, i32 %18
  %21 = load i32, i32* %20, align 4
  %22 = icmp ne i32 %21, 0
  br i1 %22,  label %23,   label %46

23:
  %24 = load i32, i32* %3, align 4
  %25 = mul nsw i32 %24, 20
  %26 = load i32, i32* %7, align 4
  %27 = add nsw i32 %25, %26
  %28 = bitcast [10005 x [20 x i32]]* @f to i32*
  %29 = getelementptr inbounds i32, i32* %28, i32 %27
  %30 = load i32, i32* %29, align 4
  %31 = mul nsw i32 %30, 20
  %32 = load i32, i32* %7, align 4
  %33 = add nsw i32 %31, %32
  %34 = bitcast [10005 x [20 x i32]]* @f to i32*
  %35 = getelementptr inbounds i32, i32* %34, i32 %33
  %36 = load i32, i32* %35, align 4
  %37 = load i32, i32* %7, align 4
  %38 = add nsw i32 %37, 1
  %39 = load i32, i32* %3, align 4
  %40 = mul nsw i32 %39, 20
  %41 = add nsw i32 %40, %38
  %42 = bitcast [10005 x [20 x i32]]* @f to i32*
  %43 = getelementptr inbounds i32, i32* %42, i32 %41
  store i32 %36, i32*  %43, align 4
  %44 = load i32, i32* %7, align 4
  %45 = add nsw i32 %44, 1
  store i32 %45, i32* %7, align 4
  br label %14

46:
  %47 = load i32, i32* %3, align 4
  %48 = add nsw i32 0, %47
  %49 = bitcast [10005 x i32]* @head to i32*
  %50 = getelementptr inbounds i32, i32* %49, i32 %48
  %51 = load i32, i32* %50, align 4
  store i32 %51, i32* %7, align 4
  br label %52

52:
  %53 = load i32, i32* %7, align 4
  %54 = sub nsw i32 0, 1
  %55 = icmp ne i32 %53, %54
  %56 = icmp ne i1 %55, 0
  br i1 %56,  label %57,   label %71

57:
  %58 = load i32, i32* %7, align 4
  %59 = add nsw i32 0, %58
  %60 = bitcast [10005 x i32]* @to to i32*
  %61 = getelementptr inbounds i32, i32* %60, i32 %59
  %62 = load i32, i32* %61, align 4
  store i32 %62, i32* %8, align 4
  %63 = load i32, i32* %8, align 4
  %64 = load i32, i32* %4, align 4
  %65 = add nsw i32 %64, 1
  call void @tree(i32 %63, i32 %65)
  %66 = load i32, i32* %7, align 4
  %67 = add nsw i32 0, %66
  %68 = bitcast [10005 x i32]* @next to i32*
  %69 = getelementptr inbounds i32, i32* %68, i32 %67
  %70 = load i32, i32* %69, align 4
  store i32 %70, i32* %7, align 4
  br label %52

71:
  br label %72

72:
  %73 = load i32, i32* %5, align 4
  ret void
}
define dso_local i32 @LCA(i32 %0, i32 %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  store i32 0, i32* %5, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  br label %9

9:
  %10 = load i32, i32* %3, align 4
  %11 = add nsw i32 0, %10
  %12 = bitcast [10005 x i32]* @dep to i32*
  %13 = getelementptr inbounds i32, i32* %12, i32 %11
  %14 = load i32, i32* %13, align 4
  %15 = load i32, i32* %4, align 4
  %16 = add nsw i32 0, %15
  %17 = bitcast [10005 x i32]* @dep to i32*
  %18 = getelementptr inbounds i32, i32* %17, i32 %16
  %19 = load i32, i32* %18, align 4
  %20 = icmp slt i32 %14, %19
  %21 = icmp ne i1 %20, 0
  br i1 %21,  label %22,   label %26

22:
  %23 = load i32, i32* %3, align 4
  store i32 %23, i32* %7, align 4
  %24 = load i32, i32* %4, align 4
  store i32 %24, i32* %3, align 4
  %25 = load i32, i32* %7, align 4
  store i32 %25, i32* %4, align 4
  br label %26

26:
  store i32 19, i32* %8, align 4
  br label %27

27:
  %28 = load i32, i32* %3, align 4
  %29 = add nsw i32 0, %28
  %30 = bitcast [10005 x i32]* @dep to i32*
  %31 = getelementptr inbounds i32, i32* %30, i32 %29
  %32 = load i32, i32* %31, align 4
  %33 = load i32, i32* %4, align 4
  %34 = add nsw i32 0, %33
  %35 = bitcast [10005 x i32]* @dep to i32*
  %36 = getelementptr inbounds i32, i32* %35, i32 %34
  %37 = load i32, i32* %36, align 4
  %38 = icmp sgt i32 %32, %37
  %39 = icmp ne i1 %38, 0
  br i1 %39,  label %40,   label %85

40:
  br label %41

41:
  %42 = load i32, i32* %3, align 4
  %43 = mul nsw i32 %42, 20
  %44 = load i32, i32* %8, align 4
  %45 = add nsw i32 %43, %44
  %46 = bitcast [10005 x [20 x i32]]* @f to i32*
  %47 = getelementptr inbounds i32, i32* %46, i32 %45
  %48 = load i32, i32* %47, align 4
  %49 = icmp ne i32 %48, 0
  br i1 %49,  label %50,   label %70

50:
  %51 = load i32, i32* %3, align 4
  %52 = mul nsw i32 %51, 20
  %53 = load i32, i32* %8, align 4
  %54 = add nsw i32 %52, %53
  %55 = bitcast [10005 x [20 x i32]]* @f to i32*
  %56 = getelementptr inbounds i32, i32* %55, i32 %54
  %57 = load i32, i32* %56, align 4
  %58 = add nsw i32 0, %57
  %59 = bitcast [10005 x i32]* @dep to i32*
  %60 = getelementptr inbounds i32, i32* %59, i32 %58
  %61 = load i32, i32* %60, align 4
  %62 = load i32, i32* %4, align 4
  %63 = add nsw i32 0, %62
  %64 = bitcast [10005 x i32]* @dep to i32*
  %65 = getelementptr inbounds i32, i32* %64, i32 %63
  %66 = load i32, i32* %65, align 4
  %67 = icmp sge i32 %61, %66
  %68 = icmp ne i1 %67, 0
  br i1 %68,  label %69,   label %70

69:
  store i32 1, i32* %6, align 4
  br label %71

70:
  store i32 0, i32* %6, align 4
  br label %71

71:
  %72 = load i32, i32* %6, align 4
  %73 = icmp ne i32 %72, 0
  br i1 %73,  label %74,   label %82

74:
  %75 = load i32, i32* %3, align 4
  %76 = mul nsw i32 %75, 20
  %77 = load i32, i32* %8, align 4
  %78 = add nsw i32 %76, %77
  %79 = bitcast [10005 x [20 x i32]]* @f to i32*
  %80 = getelementptr inbounds i32, i32* %79, i32 %78
  %81 = load i32, i32* %80, align 4
  store i32 %81, i32* %3, align 4
  br label %82

82:
  %83 = load i32, i32* %8, align 4
  %84 = sub nsw i32 %83, 1
  store i32 %84, i32* %8, align 4
  br label %27

85:
  br label %86

86:
  %87 = load i32, i32* %3, align 4
  %88 = load i32, i32* %4, align 4
  %89 = icmp eq i32 %87, %88
  %90 = icmp ne i1 %89, 0
  br i1 %90,  label %91,   label %93

91:
  %92 = load i32, i32* %3, align 4
  store i32 %92, i32* %5, align 4
  br label %141

93:
  store i32 19, i32* %8, align 4
  br label %94

94:
  %95 = load i32, i32* %8, align 4
  %96 = icmp sge i32 %95, 0
  %97 = icmp ne i1 %96, 0
  br i1 %97,  label %98,   label %134

98:
  br label %99

99:
  %100 = load i32, i32* %3, align 4
  %101 = mul nsw i32 %100, 20
  %102 = load i32, i32* %8, align 4
  %103 = add nsw i32 %101, %102
  %104 = bitcast [10005 x [20 x i32]]* @f to i32*
  %105 = getelementptr inbounds i32, i32* %104, i32 %103
  %106 = load i32, i32* %105, align 4
  %107 = load i32, i32* %4, align 4
  %108 = mul nsw i32 %107, 20
  %109 = load i32, i32* %8, align 4
  %110 = add nsw i32 %108, %109
  %111 = bitcast [10005 x [20 x i32]]* @f to i32*
  %112 = getelementptr inbounds i32, i32* %111, i32 %110
  %113 = load i32, i32* %112, align 4
  %114 = icmp ne i32 %106, %113
  %115 = icmp ne i1 %114, 0
  br i1 %115,  label %116,   label %131

116:
  %117 = load i32, i32* %3, align 4
  %118 = mul nsw i32 %117, 20
  %119 = load i32, i32* %8, align 4
  %120 = add nsw i32 %118, %119
  %121 = bitcast [10005 x [20 x i32]]* @f to i32*
  %122 = getelementptr inbounds i32, i32* %121, i32 %120
  %123 = load i32, i32* %122, align 4
  store i32 %123, i32* %3, align 4
  %124 = load i32, i32* %4, align 4
  %125 = mul nsw i32 %124, 20
  %126 = load i32, i32* %8, align 4
  %127 = add nsw i32 %125, %126
  %128 = bitcast [10005 x [20 x i32]]* @f to i32*
  %129 = getelementptr inbounds i32, i32* %128, i32 %127
  %130 = load i32, i32* %129, align 4
  store i32 %130, i32* %4, align 4
  br label %131

131:
  %132 = load i32, i32* %8, align 4
  %133 = sub nsw i32 %132, 1
  store i32 %133, i32* %8, align 4
  br label %94

134:
  %135 = load i32, i32* %3, align 4
  %136 = mul nsw i32 %135, 20
  %137 = add nsw i32 %136, 0
  %138 = bitcast [10005 x [20 x i32]]* @f to i32*
  %139 = getelementptr inbounds i32, i32* %138, i32 %137
  %140 = load i32, i32* %139, align 4
  store i32 %140, i32* %5, align 4
  br label %141

141:
  %142 = load i32, i32* %5, align 4
  ret i32 %142
}
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %8 = call i32 @quick_read()
  store i32 %8, i32* @n, align 4
  %9 = call i32 @quick_read()
  store i32 %9, i32* @m, align 4
  call void @init()
  store i32 1, i32* %3, align 4
  br label %10

10:
  %11 = load i32, i32* %3, align 4
  %12 = load i32, i32* @n, align 4
  %13 = icmp ne i32 %11, %12
  %14 = icmp ne i1 %13, 0
  br i1 %14,  label %15,   label %22

15:
  %16 = call i32 @quick_read()
  store i32 %16, i32* %4, align 4
  %17 = call i32 @quick_read()
  store i32 %17, i32* %5, align 4
  %18 = load i32, i32* %4, align 4
  %19 = load i32, i32* %5, align 4
  call void @add_edge(i32 %18, i32 %19)
  %20 = load i32, i32* %3, align 4
  %21 = add nsw i32 %20, 1
  store i32 %21, i32* %3, align 4
  br label %10

22:
  call void @tree(i32 1, i32 1)
  br label %23

23:
  %24 = load i32, i32* @m, align 4
  %25 = icmp ne i32 %24, 0
  br i1 %25,  label %26,   label %34

26:
  %27 = call i32 @quick_read()
  store i32 %27, i32* %6, align 4
  %28 = call i32 @quick_read()
  store i32 %28, i32* %7, align 4
  %29 = load i32, i32* %6, align 4
  %30 = load i32, i32* %7, align 4
  %31 = call i32 @LCA(i32 %29, i32 %30)
  call void  @putint(i32 %31)
  call void  @putch(i32 10)
  %32 = load i32, i32* @m, align 4
  %33 = sub nsw i32 %32, 1
  store i32 %33, i32* @m, align 4
  br label %23

34:
  store i32 0, i32* %1, align 4
  br label %35

35:
  %36 = load i32, i32* %1, align 4
  ret i32 %36
}
declare void @putint(i32) #1
declare i32 @getch(...) #1
declare void @putch(i32) #1
