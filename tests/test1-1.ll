define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 0, i32* %2, align 4
  store i32 0, i32* %3, align 4
  br label %4

4:
  %5 = load i32, i32* %2, align 4
  %6 = icmp slt i32 %5, 100
  br i1 %6,  label %7,   label %18

7:
  br label %8

8:
  %9 = load i32, i32* %2, align 4
  %10 = icmp eq i32 %9, 50
  br i1 %10,  label %11,   label %12

11:
  br label %18

12:
  %13 = load i32, i32* %3, align 4
  %14 = load i32, i32* %2, align 4
  %15 = add nsw i32 %13, %14
  store i32 %15, i32* %3, align 4
  %16 = load i32, i32* %2, align 4
  %17 = add nsw i32 %16, 1
  store i32 %17, i32* %2, align 4
  br label %4

18:
  %19 = load i32, i32* %3, align 4
  store i32 %19, i32* %1, align 4
  %20 = load i32, i32* %1, align 4
  ret i32 %20
}

declare void @putint(i32) #0
