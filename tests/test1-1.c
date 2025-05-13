//test array define
int main(){
    int a[4][2] = {};
    int b[4][2] = {1, 2, 3, 4, 5, 6, 7, 8};
    int e[4][2] = {{b[2][1], 12}, {3, 4}, {5, 6}, {7, 8}};
    return e[3][1];
}