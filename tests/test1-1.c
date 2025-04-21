int main()
{
	int a[10], b[10];
    int i = 0;
    while(i < 10)
	{
        a[i] = i;
        i = i + 1;
    }
    i = 0;
    while (i < 10) {
		if(a[i] % 2 == 0)
		{
			b[i] = a[i] * 2;
		}
		else 
		{
			b[i] = a[i] / 3;
		
		}
		i = i + 1;
    }

    return b[0];
}
