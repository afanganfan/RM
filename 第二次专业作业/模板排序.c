#include <stdio.h>

int main()
{
    int N;
    scanf("%d", &N);
    int a[N];

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        printf("%d\t", a[i]);
    }
    printf("\n");

    return 0;
}