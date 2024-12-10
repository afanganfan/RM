#include <stdio.h>

int main()
{
    int L;
    scanf("%d", &L);
    for (int a = 2; a <= L; a++)
    {
        int c = 0;
        for (int b = 1; b < a; b++)
        {
            if (a % b == 0)
            {
                c++;
            }
        }
        if (c == 2)
        {
            printf("%d\n", a);
        }
    }
    return 0;
}