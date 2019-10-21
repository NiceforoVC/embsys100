int globalCounter = 0x0;

int noPointers() {
  unsigned int counter = 0x7FFFFFFF;
  counter++;
  counter++;
  counter++;
  counter++;
  return 0;
}

int withPointers() {
  int *p_int = (int *)0x20000000;
  ++(*p_int);
  ++(*p_int);
  ++(*p_int);
  globalCounter ++;
  return 0;
}

int main() {
  noPointers();
  withPointers();
  return 0;
}
