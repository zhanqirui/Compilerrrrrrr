@arr1 = dso_local global [10 x [2 x [3 x [4 x [5 x [6 x [2 x i32]]]]]]] zeroinitializer, align 16
@arr2 = dso_local global [10 x [2 x [3 x [2 x [4 x [8 x [7 x i32]]]]]]] zeroinitializer, align 16
define dso_local void @loop1(i32 %0, i32 %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  store i32 0, i32* %6, align 4
  br label %13

13:
  %14 = load i32, i32* %6, align 4
  %15 = load i32, i32* %3, align 4
  %16 = icmp slt i32 %14, %15
  %17 = icmp ne i1 %16, 0
  br i1 %17,  label %18,   label %24

18:
  %19 = load i32, i32* %6, align 4
  %20 = load i32, i32* %4, align 4
  %21 = icmp slt i32 %19, %20
  %22 = icmp ne i1 %21, 0
  br i1 %22,  label %23,   label %24

23:
  store i32 1, i32* %5, align 4
  br label %25

24:
  store i32 0, i32* %5, align 4
  br label %25

25:
  %26 = load i32, i32* %5, align 4
  %27 = icmp ne i32 %26, 0
  br i1 %27,  label %28,   label %122

28:
  store i32 0, i32* %7, align 4
  br label %29

29:
  %30 = load i32, i32* %7, align 4
  %31 = icmp slt i32 %30, 2
  %32 = icmp ne i1 %31, 0
  br i1 %32,  label %33,   label %119

33:
  store i32 0, i32* %8, align 4
  br label %34

34:
  %35 = load i32, i32* %8, align 4
  %36 = icmp slt i32 %35, 3
  %37 = icmp ne i1 %36, 0
  br i1 %37,  label %38,   label %116

38:
  store i32 0, i32* %9, align 4
  br label %39

39:
  %40 = load i32, i32* %9, align 4
  %41 = icmp slt i32 %40, 4
  %42 = icmp ne i1 %41, 0
  br i1 %42,  label %43,   label %113

43:
  store i32 0, i32* %10, align 4
  br label %44

44:
  %45 = load i32, i32* %10, align 4
  %46 = icmp slt i32 %45, 5
  %47 = icmp ne i1 %46, 0
  br i1 %47,  label %48,   label %110

48:
  store i32 0, i32* %11, align 4
  br label %49

49:
  %50 = load i32, i32* %11, align 4
  %51 = icmp slt i32 %50, 6
  %52 = icmp ne i1 %51, 0
  br i1 %52,  label %53,   label %107

53:
  store i32 0, i32* %12, align 4
  br label %54

54:
  %55 = load i32, i32* %12, align 4
  %56 = icmp slt i32 %55, 2
  %57 = icmp ne i1 %56, 0
  br i1 %57,  label %58,   label %104

58:
  %59 = load i32, i32* %6, align 4
  %60 = load i32, i32* %7, align 4
  %61 = add nsw i32 %59, %60
  %62 = load i32, i32* %8, align 4
  %63 = add nsw i32 %61, %62
  %64 = load i32, i32* %9, align 4
  %65 = add nsw i32 %63, %64
  %66 = load i32, i32* %10, align 4
  %67 = add nsw i32 %65, %66
  %68 = load i32, i32* %11, align 4
  %69 = add nsw i32 %67, %68
  %70 = load i32, i32* %12, align 4
  %71 = add nsw i32 %69, %70
  %72 = load i32, i32* %3, align 4
  %73 = add nsw i32 %71, %72
  %74 = load i32, i32* %4, align 4
  %75 = add nsw i32 %73, %74
  %76 = load i32, i32* %6, align 4
  %77 = mul nsw i32 %76, 2
  %78 = load i32, i32* %7, align 4
  %79 = add nsw i32 %77, %78
  %80 = load i32, i32* %7, align 4
  %81 = mul nsw i32 %80, 3
  %82 = load i32, i32* %8, align 4
  %83 = add nsw i32 %81, %82
  %84 = load i32, i32* %8, align 4
  %85 = mul nsw i32 %84, 4
  %86 = load i32, i32* %9, align 4
  %87 = add nsw i32 %85, %86
  %88 = load i32, i32* %9, align 4
  %89 = mul nsw i32 %88, 5
  %90 = load i32, i32* %10, align 4
  %91 = add nsw i32 %89, %90
  %92 = load i32, i32* %10, align 4
  %93 = mul nsw i32 %92, 6
  %94 = load i32, i32* %11, align 4
  %95 = add nsw i32 %93, %94
  %96 = load i32, i32* %11, align 4
  %97 = mul nsw i32 %96, 2
  %98 = load i32, i32* %12, align 4
  %99 = add nsw i32 %97, %98
  %100 = bitcast [10 x [2 x [3 x [4 x [5 x [6 x [2 x i32]]]]]]]* @arr1 to i32*
  %101 = getelementptr inbounds i32, i32* %100, i32 %99
  store i32 %75, i32*  %101, align 4
  %102 = load i32, i32* %12, align 4
  %103 = add nsw i32 %102, 1
  store i32 %103, i32* %12, align 4
  br label %54

104:
  %105 = load i32, i32* %11, align 4
  %106 = add nsw i32 %105, 1
  store i32 %106, i32* %11, align 4
  br label %49

107:
  %108 = load i32, i32* %10, align 4
  %109 = add nsw i32 %108, 1
  store i32 %109, i32* %10, align 4
  br label %44

110:
  %111 = load i32, i32* %9, align 4
  %112 = add nsw i32 %111, 1
  store i32 %112, i32* %9, align 4
  br label %39

113:
  %114 = load i32, i32* %8, align 4
  %115 = add nsw i32 %114, 1
  store i32 %115, i32* %8, align 4
  br label %34

116:
  %117 = load i32, i32* %7, align 4
  %118 = add nsw i32 %117, 1
  store i32 %118, i32* %7, align 4
  br label %29

119:
  %120 = load i32, i32* %6, align 4
  %121 = add nsw i32 %120, 1
  store i32 %121, i32* %6, align 4
  br label %13

122:
  %123 = load i32, i32* %5, align 4
  ret void
}
define dso_local void @loop2() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  store i32 0, i32* %2, align 4
  br label %9

9:
  %10 = load i32, i32* %2, align 4
  %11 = icmp slt i32 %10, 10
  %12 = icmp ne i1 %11, 0
  br i1 %12,  label %13,   label %97

13:
  store i32 0, i32* %3, align 4
  br label %14

14:
  %15 = load i32, i32* %3, align 4
  %16 = icmp slt i32 %15, 2
  %17 = icmp ne i1 %16, 0
  br i1 %17,  label %18,   label %94

18:
  store i32 0, i32* %4, align 4
  br label %19

19:
  %20 = load i32, i32* %4, align 4
  %21 = icmp slt i32 %20, 3
  %22 = icmp ne i1 %21, 0
  br i1 %22,  label %23,   label %91

23:
  store i32 0, i32* %5, align 4
  br label %24

24:
  %25 = load i32, i32* %5, align 4
  %26 = icmp slt i32 %25, 2
  %27 = icmp ne i1 %26, 0
  br i1 %27,  label %28,   label %88

28:
  store i32 0, i32* %6, align 4
  br label %29

29:
  %30 = load i32, i32* %6, align 4
  %31 = icmp slt i32 %30, 4
  %32 = icmp ne i1 %31, 0
  br i1 %32,  label %33,   label %85

33:
  store i32 0, i32* %7, align 4
  br label %34

34:
  %35 = load i32, i32* %7, align 4
  %36 = icmp slt i32 %35, 8
  %37 = icmp ne i1 %36, 0
  br i1 %37,  label %38,   label %82

38:
  store i32 0, i32* %8, align 4
  br label %39

39:
  %40 = load i32, i32* %8, align 4
  %41 = icmp slt i32 %40, 7
  %42 = icmp ne i1 %41, 0
  br i1 %42,  label %43,   label %79

43:
  %44 = load i32, i32* %2, align 4
  %45 = load i32, i32* %3, align 4
  %46 = add nsw i32 %44, %45
  %47 = load i32, i32* %5, align 4
  %48 = add nsw i32 %46, %47
  %49 = load i32, i32* %8, align 4
  %50 = add nsw i32 %48, %49
  %51 = load i32, i32* %2, align 4
  %52 = mul nsw i32 %51, 2
  %53 = load i32, i32* %3, align 4
  %54 = add nsw i32 %52, %53
  %55 = load i32, i32* %3, align 4
  %56 = mul nsw i32 %55, 3
  %57 = load i32, i32* %4, align 4
  %58 = add nsw i32 %56, %57
  %59 = load i32, i32* %4, align 4
  %60 = mul nsw i32 %59, 2
  %61 = load i32, i32* %5, align 4
  %62 = add nsw i32 %60, %61
  %63 = load i32, i32* %5, align 4
  %64 = mul nsw i32 %63, 4
  %65 = load i32, i32* %6, align 4
  %66 = add nsw i32 %64, %65
  %67 = load i32, i32* %6, align 4
  %68 = mul nsw i32 %67, 8
  %69 = load i32, i32* %7, align 4
  %70 = add nsw i32 %68, %69
  %71 = load i32, i32* %7, align 4
  %72 = mul nsw i32 %71, 7
  %73 = load i32, i32* %8, align 4
  %74 = add nsw i32 %72, %73
  %75 = bitcast [10 x [2 x [3 x [2 x [4 x [8 x [7 x i32]]]]]]]* @arr2 to i32*
  %76 = getelementptr inbounds i32, i32* %75, i32 %74
  store i32 %50, i32*  %76, align 4
  %77 = load i32, i32* %8, align 4
  %78 = add nsw i32 %77, 1
  store i32 %78, i32* %8, align 4
  br label %39

79:
  %80 = load i32, i32* %7, align 4
  %81 = add nsw i32 %80, 1
  store i32 %81, i32* %7, align 4
  br label %34

82:
  %83 = load i32, i32* %6, align 4
  %84 = add nsw i32 %83, 1
  store i32 %84, i32* %6, align 4
  br label %29

85:
  %86 = load i32, i32* %5, align 4
  %87 = add nsw i32 %86, 1
  store i32 %87, i32* %5, align 4
  br label %24

88:
  %89 = load i32, i32* %4, align 4
  %90 = add nsw i32 %89, 1
  store i32 %90, i32* %4, align 4
  br label %19

91:
  %92 = load i32, i32* %3, align 4
  %93 = add nsw i32 %92, 1
  store i32 %93, i32* %3, align 4
  br label %14

94:
  %95 = load i32, i32* %2, align 4
  %96 = add nsw i32 %95, 1
  store i32 %96, i32* %2, align 4
  br label %9

97:
  %98 = load i32, i32* %1, align 4
  ret void
}
define dso_local i32 @loop3(i32 %0, i32 %1, i32 %2, i32 %3, i32 %4, i32 %5, i32 %6) #0 {
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca i32, align 4
  %17 = alloca i32, align 4
  %18 = alloca i32, align 4
  %19 = alloca i32, align 4
  %20 = alloca i32, align 4
  %21 = alloca i32, align 4
  %22 = alloca i32, align 4
  %23 = alloca i32, align 4
  store i32 0, i32* %15, align 4
  store i32 %0, i32* %8, align 4
  store i32 %1, i32* %9, align 4
  store i32 %2, i32* %10, align 4
  store i32 %3, i32* %11, align 4
  store i32 %4, i32* %12, align 4
  store i32 %5, i32* %13, align 4
  store i32 %6, i32* %14, align 4
  store i32 0, i32* %23, align 4
  store i32 0, i32* %16, align 4
  br label %24

24:
  %25 = load i32, i32* %16, align 4
  %26 = icmp slt i32 %25, 10
  %27 = icmp ne i1 %26, 0
  br i1 %27,  label %28,   label %186

28:
  store i32 0, i32* %17, align 4
  br label %29

29:
  %30 = load i32, i32* %17, align 4
  %31 = icmp slt i32 %30, 100
  %32 = icmp ne i1 %31, 0
  br i1 %32,  label %33,   label %176

33:
  store i32 0, i32* %18, align 4
  br label %34

34:
  %35 = load i32, i32* %18, align 4
  %36 = icmp slt i32 %35, 1000
  %37 = icmp ne i1 %36, 0
  br i1 %37,  label %38,   label %166

38:
  store i32 0, i32* %19, align 4
  br label %39

39:
  %40 = load i32, i32* %19, align 4
  %41 = icmp slt i32 %40, 10000
  %42 = icmp ne i1 %41, 0
  br i1 %42,  label %43,   label %156

43:
  store i32 0, i32* %20, align 4
  br label %44

44:
  %45 = load i32, i32* %20, align 4
  %46 = icmp slt i32 %45, 100000
  %47 = icmp ne i1 %46, 0
  br i1 %47,  label %48,   label %146

48:
  store i32 0, i32* %21, align 4
  br label %49

49:
  %50 = load i32, i32* %21, align 4
  %51 = icmp slt i32 %50, 1000000
  %52 = icmp ne i1 %51, 0
  br i1 %52,  label %53,   label %136

53:
  store i32 0, i32* %22, align 4
  br label %54

54:
  %55 = load i32, i32* %22, align 4
  %56 = icmp slt i32 %55, 10000000
  %57 = icmp ne i1 %56, 0
  br i1 %57,  label %58,   label %126

58:
  %59 = load i32, i32* %23, align 4
  %60 = srem i32 %59, 817
  %61 = load i32, i32* %16, align 4
  %62 = mul nsw i32 %61, 2
  %63 = load i32, i32* %17, align 4
  %64 = add nsw i32 %62, %63
  %65 = load i32, i32* %17, align 4
  %66 = mul nsw i32 %65, 3
  %67 = load i32, i32* %18, align 4
  %68 = add nsw i32 %66, %67
  %69 = load i32, i32* %18, align 4
  %70 = mul nsw i32 %69, 4
  %71 = load i32, i32* %19, align 4
  %72 = add nsw i32 %70, %71
  %73 = load i32, i32* %19, align 4
  %74 = mul nsw i32 %73, 5
  %75 = load i32, i32* %20, align 4
  %76 = add nsw i32 %74, %75
  %77 = load i32, i32* %20, align 4
  %78 = mul nsw i32 %77, 6
  %79 = load i32, i32* %21, align 4
  %80 = add nsw i32 %78, %79
  %81 = load i32, i32* %21, align 4
  %82 = mul nsw i32 %81, 2
  %83 = load i32, i32* %22, align 4
  %84 = add nsw i32 %82, %83
  %85 = bitcast [10 x [2 x [3 x [4 x [5 x [6 x [2 x i32]]]]]]]* @arr1 to i32*
  %86 = getelementptr inbounds i32, i32* %85, i32 %84
  %87 = load i32, i32* %86, align 4
  %88 = add nsw i32 %60, %87
  %89 = load i32, i32* %16, align 4
  %90 = mul nsw i32 %89, 2
  %91 = load i32, i32* %17, align 4
  %92 = add nsw i32 %90, %91
  %93 = load i32, i32* %17, align 4
  %94 = mul nsw i32 %93, 3
  %95 = load i32, i32* %18, align 4
  %96 = add nsw i32 %94, %95
  %97 = load i32, i32* %18, align 4
  %98 = mul nsw i32 %97, 2
  %99 = load i32, i32* %19, align 4
  %100 = add nsw i32 %98, %99
  %101 = load i32, i32* %19, align 4
  %102 = mul nsw i32 %101, 4
  %103 = load i32, i32* %20, align 4
  %104 = add nsw i32 %102, %103
  %105 = load i32, i32* %20, align 4
  %106 = mul nsw i32 %105, 8
  %107 = load i32, i32* %21, align 4
  %108 = add nsw i32 %106, %107
  %109 = load i32, i32* %21, align 4
  %110 = mul nsw i32 %109, 7
  %111 = load i32, i32* %22, align 4
  %112 = add nsw i32 %110, %111
  %113 = bitcast [10 x [2 x [3 x [2 x [4 x [8 x [7 x i32]]]]]]]* @arr2 to i32*
  %114 = getelementptr inbounds i32, i32* %113, i32 %112
  %115 = load i32, i32* %114, align 4
  %116 = add nsw i32 %88, %115
  store i32 %116, i32* %23, align 4
  %117 = load i32, i32* %22, align 4
  %118 = add nsw i32 %117, 1
  store i32 %118, i32* %22, align 4
  br label %119

119:
  %120 = load i32, i32* %22, align 4
  %121 = load i32, i32* %14, align 4
  %122 = icmp sge i32 %120, %121
  %123 = icmp ne i1 %122, 0
  br i1 %123,  label %124,   label %125

124:
  br label %126

125:
  br label %54

126:
  %127 = load i32, i32* %21, align 4
  %128 = add nsw i32 %127, 1
  store i32 %128, i32* %21, align 4
  br label %129

129:
  %130 = load i32, i32* %21, align 4
  %131 = load i32, i32* %13, align 4
  %132 = icmp sge i32 %130, %131
  %133 = icmp ne i1 %132, 0
  br i1 %133,  label %134,   label %135

134:
  br label %136

135:
  br label %49

136:
  %137 = load i32, i32* %20, align 4
  %138 = add nsw i32 %137, 1
  store i32 %138, i32* %20, align 4
  br label %139

139:
  %140 = load i32, i32* %20, align 4
  %141 = load i32, i32* %12, align 4
  %142 = icmp sge i32 %140, %141
  %143 = icmp ne i1 %142, 0
  br i1 %143,  label %144,   label %145

144:
  br label %146

145:
  br label %44

146:
  %147 = load i32, i32* %19, align 4
  %148 = add nsw i32 %147, 1
  store i32 %148, i32* %19, align 4
  br label %149

149:
  %150 = load i32, i32* %19, align 4
  %151 = load i32, i32* %11, align 4
  %152 = icmp sge i32 %150, %151
  %153 = icmp ne i1 %152, 0
  br i1 %153,  label %154,   label %155

154:
  br label %156

155:
  br label %39

156:
  %157 = load i32, i32* %18, align 4
  %158 = add nsw i32 %157, 1
  store i32 %158, i32* %18, align 4
  br label %159

159:
  %160 = load i32, i32* %18, align 4
  %161 = load i32, i32* %10, align 4
  %162 = icmp sge i32 %160, %161
  %163 = icmp ne i1 %162, 0
  br i1 %163,  label %164,   label %165

164:
  br label %166

165:
  br label %34

166:
  %167 = load i32, i32* %17, align 4
  %168 = add nsw i32 %167, 1
  store i32 %168, i32* %17, align 4
  br label %169

169:
  %170 = load i32, i32* %17, align 4
  %171 = load i32, i32* %9, align 4
  %172 = icmp sge i32 %170, %171
  %173 = icmp ne i1 %172, 0
  br i1 %173,  label %174,   label %175

174:
  br label %176

175:
  br label %29

176:
  %177 = load i32, i32* %16, align 4
  %178 = add nsw i32 %177, 1
  store i32 %178, i32* %16, align 4
  br label %179

179:
  %180 = load i32, i32* %16, align 4
  %181 = load i32, i32* %8, align 4
  %182 = icmp sge i32 %180, %181
  %183 = icmp ne i1 %182, 0
  br i1 %183,  label %184,   label %185

184:
  br label %186

185:
  br label %24

186:
  %187 = load i32, i32* %23, align 4
  store i32 %187, i32* %15, align 4
  %188 = load i32, i32* %15, align 4
  ret i32 %188
}
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %11 = call i32 (...) @getint()
  store i32 %11, i32* %2, align 4
  %12 = call i32 (...) @getint()
  store i32 %12, i32* %3, align 4
  %13 = call i32 (...) @getint()
  store i32 %13, i32* %4, align 4
  %14 = call i32 (...) @getint()
  store i32 %14, i32* %5, align 4
  %15 = call i32 (...) @getint()
  store i32 %15, i32* %6, align 4
  %16 = call i32 (...) @getint()
  store i32 %16, i32* %7, align 4
  %17 = call i32 (...) @getint()
  store i32 %17, i32* %8, align 4
  %18 = call i32 (...) @getint()
  store i32 %18, i32* %9, align 4
  %19 = call i32 (...) @getint()
  store i32 %19, i32* %10, align 4
  %20 = load i32, i32* %2, align 4
  %21 = load i32, i32* %3, align 4
  call void @loop1(i32 %20, i32 %21)
  call void @loop2()
  %22 = load i32, i32* %4, align 4
  %23 = load i32, i32* %5, align 4
  %24 = load i32, i32* %6, align 4
  %25 = load i32, i32* %7, align 4
  %26 = load i32, i32* %8, align 4
  %27 = load i32, i32* %9, align 4
  %28 = load i32, i32* %10, align 4
  %29 = call i32 @loop3(i32 %22, i32 %23, i32 %24, i32 %25, i32 %26, i32 %27, i32 %28)
  store i32 %29, i32* %1, align 4
  %30 = load i32, i32* %1, align 4
  ret i32 %30
}
declare i32 @getint(...) #1
