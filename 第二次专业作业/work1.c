#include <stdio.h>
int main()
{
    int n1,n2,n,a,b;
    n1=1;
    n2=1;
    scanf("%d",&a);
    for(int i=0;i<a;i++)
    {
        scanf("%d",&b);
        for(int l=1;l<b;l++)
        {
            n=n1;
            n1=n2+n;
            n=n2;
            n2=n1;
            n1=n;
        }   
        printf("%d\n",n1);
        n1=1;
        n2=1;
    }
    return 0;       
}