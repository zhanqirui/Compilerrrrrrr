define dso_local i32 @ififElse() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 5, i32* %1, align 4
  store i32 10, i32* %2, align 4
%3:
  %4 = load i32, i32* %1, align 4
  %5 = icmp eq %4,5
  bc %5,   label %6  label %11
%6:
  %7 = load i32, i32* %2, align 4
  %8 = icmp eq %7,10
  bc %8,   label   label 
  store i32 25, i32* %1, align 4
  %9 = load i32, i32* %1, align 4
  %10 = add nsw i32 %9, 15
  store i32 %10, i32* %1, align 4
%11:
  %12 = load i32, i32* %1, align 4
  ret i32 %12
}
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 @ififElse()
  ret i32 %2
}
