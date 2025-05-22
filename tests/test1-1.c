void stack_push(int s[]) {
  s[1] = 3;
}
int eval() {
  int ops[3] = {};
  stack_push(ops);
  return ops[1];
}

int main(){
  int i = eval();
  return i;
}