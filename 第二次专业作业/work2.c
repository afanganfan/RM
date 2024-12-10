#include <stdio.h>
    int factorial(int n)
 {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}
 
int main() {
    int number;
    printf("请输入一个整数: ");
    scanf("%d", &number);
 
    if (number < 0) {
        printf("负数没有阶乘。\n");
    } else {
        int result = factorial(number);
        printf("%d 的阶乘是 %llu\n", number, result);
    }
 
    return 0;
}
