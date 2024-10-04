#include <stdio.h>

// Sum Function
int sumNum(int a, int b){
    return a + b;
}
int main(void){
    int a,b;
    // Prompt user for Integer input
    printf("Enter an integer: ");
    scanf("%d", &a);

    printf("Enter another integer: ");
    scanf("%d", &b);

    // Output Sum
    printf("%d + %d = %d", a, b, sumNum(a,b));
    return 0;
}