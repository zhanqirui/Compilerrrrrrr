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
%8:
  %9 = load i32, i32* %4, align 4
  %10 = add nsw i32 2, %9
  %11 = icmp lt %10,6
  %12 = icmp and %11,1
  bc %12,   label %13  label 1
%13:
%14:
  %15 = load i32, i32* %6, align 4
  %16 = load i32, i32* %2, align 4
  %17 = add nsw i32 0, %16
  %18 = add nsw i32 %17, 0
  %19 = icmp or %15,%18
  bc %19,   label %20  label 2
%20:
%21:
  %22 = icmp gt 9,2
  %23 = icmp and 0,%22
  bc %23,   label 3  label %24
%24:
%25:
  %26 = icmp ne 0,0
  %27 = load i32, i32* %6, align 4
  %28 = icmp and %26,%27
  bc %28,   label 4  label %29
%29:
%30:
  %31 = load i32, i32* %2, align 4
  %32 = add nsw i32 2, %31
  %33 = icmp ge %32,2
  bc %33,   label %34  label 5
%34:
%35:
  %36 = icmp ge -1,0
  %37 = icmp or %36,0
  bc %37,   label 6  label %38
%38:
%39:
  bc 1,   label %40  label 7
%40:
%41:
  %42 = load i32, i32* %3, align 4
  %43 = add nsw i32 %42, 20
  %44 = icmp gt %43,10
  bc %44,   label %45  label 8
%45:
%46:
  %47 = load i32, i32* %7, align 4
  %48 = add nsw i32 0, %47
  bc %48,   label 9  label 10
  ret i32 1
}
