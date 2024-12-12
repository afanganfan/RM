#include <stdio.h>
int factorial(int n)
{
    if (n <= 1)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

int main()
{
    int number;
    scanf("%d", &number);
    int result = factorial(number);
    printf("%llu\n",result);

    return 0;
}
