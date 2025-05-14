const int N = -1;
int arr[N + 2 * 4 - 99 / 99] = {1, 2, 33, 4, 5, 6};

int main() {
  int i = 0, sum = 0;
  while (i < 6) {
    sum = sum + arr[i];
    i = i + 1;
  }
  return sum;
}

// @N = dso_local constant i32 -1, align 4
// @arr = dso_local global [6 x i32] [i32 1, i32 2, i32 33, i32 4, i32 5, i32 6], align 16
