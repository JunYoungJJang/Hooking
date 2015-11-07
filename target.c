#include <stdio.h>
#include <stdlib.h>

int sum(int a, int b)
{
  return a + b;
}

int mul(int a, int b)
{
  return a * b;
}

int main(void)
{
  int a, b;
  
  printf("두 수 입력: ");
  scanf("%d %d", &a, &b);
  
  while(1)
  {
    printf("%d + %d = %d \n", a, b, sum(a, b));
    system("cls");
  }
  
  return 0;
}
