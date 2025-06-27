int main()
{
    int a = 3;
    int b = 5;

    // 无条件跳转，后面的代码成为死代码
    goto end;

    // 下面这些代码永远不会被执行（死代码）
    a = a + b;
    b = b * 2;
    int c = a + b;
    c = c + 1;

end:
    return a;
}