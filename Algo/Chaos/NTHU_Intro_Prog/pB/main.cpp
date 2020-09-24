#include <iostream>

using namespace std;

int main() {
    int integer, fraction;
    scanf("%d.%d", &integer, &fraction);
    int a, b, c, x, y, z;
    c = integer % 10; integer /= 10;
    b = integer % 10; integer /= 10;
    a = integer % 10; integer /= 10;

    z = fraction % 10; fraction /= 10;
    y = fraction % 10; fraction /= 10;
    x = fraction % 10; fraction /= 10;

    double X, Y;
    X = a * 100 + b * 10 + c;
    X += 0.1F * x + 0.01F * y + 0.001F * z;

    Y = c * 100 + b * 10 + a;
    Y += 0.1F * z + 0.01F * y + 0.001F * x;

    printf("%.3lf", X + Y);
}
