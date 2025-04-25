int func(int a, int b[][10])
{
    return b;
}

const int SIZE = 10;
int main()
{
    int i = 0;
    int a[SIZE];
    while (i < 10) {
        i = i + 1;
        if (i == 3)
            continue;
        if (i == 8)
            break;
    }
    return 0;
}
