#include <stdio.h>

int main(void)
{
    double num1, num2;
    char operation;

    printf("=================================\n");
    printf("       CODEALPHA CALCULATOR\n");
    printf("=================================\n");

    printf("Enter first number: ");
    if (scanf("%lf", &num1) != 1) {
        printf("Invalid number input.\n");
        return 1;
    }

    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &operation);

    printf("Enter second number: ");
    if (scanf("%lf", &num2) != 1) {
        printf("Invalid number input.\n");
        return 1;
    }

    switch (operation) {
        case '+':
            printf("Result: %.2f\n", num1 + num2);
            break;
        case '-':
            printf("Result: %.2f\n", num1 - num2);
            break;
        case '*':
            printf("Result: %.2f\n", num1 * num2);
            break;
        case '/':
            if (num2 == 0.0) {
                printf("Error: Division by zero is not allowed.\n");
            } else {
                printf("Result: %.2f\n", num1 / num2);
            }
            break;
        default:
            printf("Invalid operator. Please use +, -, * or /.\n");
    }

    return 0;
}
