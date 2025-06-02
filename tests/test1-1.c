int main()
{
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    int flag = 0;
    if(a == 1){
        flag = flag + 2;
        if(b == 2){
            flag = flag + 2;
            if(c == 3){
                flag = flag + 2;
                if(d == 4){
                    flag = flag + 2;
                }
                else{
                    flag = flag + 1;
                }
            }
            else{
                flag = flag + 1;
            }
        }
        else{
            flag = flag + 1;
        }
    }
    else{
        flag = flag + 1;
    }
    return flag;
}
