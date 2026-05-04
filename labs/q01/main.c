#include <stdio.h>

#define PI 3.14159

int main(void) {
    int radius = 0;

    scanf("%d", &radius);

    printf("%.2f\n", PI * radius * radius);

    return 0;
}
