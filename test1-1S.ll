; ModuleID = './tests/test1-1S.ll'
source_filename = "./tests/test1-1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @ifElseIf() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 5, i32* %2, align 4
  store i32 10, i32* %3, align 4
  %4 = load i32, i32* %2, align 4
  %5 = icmp eq i32 %4, 6
  br i1 %5, label %9, label %6

6:                                                ; preds = %0
  %7 = load i32, i32* %3, align 4
  %8 = icmp eq i32 %7, 11
  br i1 %8, label %9, label %11

9:                                                ; preds = %6, %0
  %10 = load i32, i32* %2, align 4
  store i32 %10, i32* %1, align 4
  br label %34

11:                                               ; preds = %6
  %12 = load i32, i32* %3, align 4
  %13 = icmp eq i32 %12, 10
  br i1 %13, label %14, label %18

14:                                               ; preds = %11
  %15 = load i32, i32* %2, align 4
  %16 = icmp eq i32 %15, 1
  br i1 %16, label %17, label %18

17:                                               ; preds = %14
  store i32 25, i32* %2, align 4
  br label %31

18:                                               ; preds = %14, %11
  %19 = load i32, i32* %3, align 4
  %20 = icmp eq i32 %19, 10
  br i1 %20, label %21, label %27

21:                                               ; preds = %18
  %22 = load i32, i32* %2, align 4
  %23 = icmp eq i32 %22, -5
  br i1 %23, label %24, label %27

24:                                               ; preds = %21
  %25 = load i32, i32* %2, align 4
  %26 = add nsw i32 %25, 15
  store i32 %26, i32* %2, align 4
  br label %30

27:                                               ; preds = %21, %18
  %28 = load i32, i32* %2, align 4
  %29 = sub nsw i32 0, %28
  store i32 %29, i32* %2, align 4
  br label %30

30:                                               ; preds = %27, %24
  br label %31

31:                                               ; preds = %30, %17
  br label %32

32:                                               ; preds = %31
  %33 = load i32, i32* %2, align 4
  store i32 %33, i32* %1, align 4
  br label %34

34:                                               ; preds = %32, %9
  %35 = load i32, i32* %1, align 4
  ret i32 %35
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 @ifElseIf()
  %3 = call i32 (i32, i32, ...) bitcast (i32 (...)* @putint to i32 (i32, i32, ...)*)(i32 noundef %2, i32 noundef 1)
  ret i32 0
}

declare i32 @putint(...) #1

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
