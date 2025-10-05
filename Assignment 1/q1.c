// Added four lines of code, right underneath the gcd portion;
// Two for handling the case where either of the numbers is 0, since if we end up subtracting 0 from the other number, 
// we will get the other number as the result, which is not what we want, since we run into an infinite loop;
// Also added two lines of code to take the absolute value of the numbers, since we want to make sure we are dealing with positive numbers;

int gcd(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    a = abs(a);
    b = abs(b);
    while (a != b) {
        if (a > b) a = a - b;
        else b = b - a;
    }
    return a;
}