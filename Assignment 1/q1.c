// Added four lines of code, right underneath the gcd portion;
// Two for handling the case where either of the numbers is 0, since if we end up subtracting 0 from the other number, 
// we will get the other number as the result, which is not what we want, since we run into an infinite loop;
// Also added two lines of code to take the absolute value of the numbers, since we want to make sure we are dealing with positive numbers;

#include <stdlib.h>
// Added the stdlib.h header file to use the abs function;
#include <stdio.h>
// Added the stdio.h header file to use the printf and scanf functions;

int gcd(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    if (a < 0) a = abs(a);
    if (b < 0) b = abs(b);
    while (a != b) {
        if (a > b) a = a - b;
        else b = b - a;
    }
    return a;
}

int main() {
    int num1, num2;
    
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    
    int result = gcd(num1, num2);
    printf("GCD of %d and %d is: %d\n", num1, num2, result);
    
    return 0;
}