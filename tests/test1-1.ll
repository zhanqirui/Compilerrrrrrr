@a = dso_local constant [3 x [5 x [5 x [20 x i32]]]] [[5 x [5 x [20 x i32]]] [[5 x [20 x i32]] [[20 x i32] [i32 0, i32 1, i32 2, i32 3, i32 4, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0], [20 x i32] zeroinitializer, [20 x i32] zeroinitializer, [20 x i32] zeroinitializer, [20 x i32] zeroinitializer], [5 x [20 x i32]] zeroinitializer, [5 x [20 x i32]] zeroinitializer, [5 x [20 x i32]] zeroinitializer, [5 x [20 x i32]] zeroinitializer], [5 x [5 x [20 x i32]]] zeroinitializer, [5 x [5 x [20 x i32]]] zeroinitializer], align 16
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 0, i32* %1, align 4
  %2 = load i32, i32* %1, align 4
  ret i32 %2
}
