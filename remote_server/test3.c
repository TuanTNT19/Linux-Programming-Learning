#include <stdio.h>
#include <math.h>
int checknt(int n)
{
    int check=0;
   for (int i=2;i<=sqrt(n);i++)
   {
    if (n%i==0) 
    {
        check++;
    }
   }
   if (check) 
   {
    return 0;
   }
   else 
   {
    return 1;
   }
}
int main()
{
    int n;
    printf("Nhap n: ");
    scanf("%d",&n);
    if (checknt(n))
    {
        printf("YES");

    }
    else 
    {
        printf("NO");
    }
    return 0;
}
