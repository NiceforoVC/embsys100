int sum(int var0, int var1, int var2, int var3, int var4);
int inner(void);

int main()
{
  int result;
  int ivar0 = 1;
  int ivar1 = 2;
  int ivar2 = 3;
  int ivar3 = 4;
  int ivar4 = 5;
  
  result = sum(ivar0, ivar1, ivar2 , ivar3, ivar4);
  
  result = inner();
  
  return 0;
}
int sum(int var0, int var1, int var2, int var3, int var4)
{
  int lvar0;
  int lvar1;
  int lvar2;
  int lvar3;
  int lvar4;
  
  int sum;
  
  lvar0 = var0;
  lvar1 = var1;
  lvar2 = var2;
  lvar3 = var3;
  lvar4 = var4;
  
  sum = lvar0 + lvar1 + lvar2 + lvar3 + lvar4;
  
  return sum;
}

int inner()
{
  int innerSum;
  innerSum = sum(6, 7, 8, 9, 10);
  return innerSum;
}






