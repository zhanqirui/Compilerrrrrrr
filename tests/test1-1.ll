define dso_local i32 @main() #0 {
	%1 = alloca i32, align 4
	%2 = alloca i32*, align 4[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}}
	%3 = alloca i32*, align 4[4][2] = {{0, 0}, {1.000000, 2.000000}, {3.000000, 4.000000}, {5.000000, 6.000000}}
	store i32 0, i32* %1, align 4
	%4 = mul 2,2
	%5 = add nsw i32 %4, 0
	%6 = mul %5,4
	%7 = add nsw i32 %6, %2
	ret i32* %7
}
