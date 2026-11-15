#include <stdio.h>

#define MAX 10

void readMatrix(int matrix[MAX][MAX], int rows, int cols, char name)
{
    int i, j;
    printf("Enter elements of Matrix %c (%d x %d):\n", name, rows, cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%c[%d][%d]: ", name, i + 1, j + 1);
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("Invalid input.\n");
                return;
            }
        }
    }
}

void displayMatrix(int matrix[MAX][MAX], int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%6d", matrix[i][j]);
        }
        printf("\n");
    }
}

void addMatrices(int A[MAX][MAX], int B[MAX][MAX],
                 int result[MAX][MAX], int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            result[i][j] = A[i][j] + B[i][j];
}

void multiplyMatrices(int A[MAX][MAX], int B[MAX][MAX],
                      int result[MAX][MAX],
                      int r1, int c1, int c2)
{
    int i, j, k;
    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (k = 0; k < c1; k++)
                result[i][j] += A[i][k] * B[k][j];
        }
    }
}

void transposeMatrix(int source[MAX][MAX], int result[MAX][MAX],
                     int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            result[j][i] = source[i][j];
}

int main(void)
{
    int A[MAX][MAX], B[MAX][MAX], result[MAX][MAX];
    int r1, c1, r2, c2, choice;

    printf("=================================\n");
    printf("       CODEALPHA MATRIX TOOL\n");
    printf("=================================\n");

    printf("Enter rows and columns for Matrix A (1-%d): ", MAX);
    if (scanf("%d %d", &r1, &c1) != 2 || r1 < 1 || r1 > MAX || c1 < 1 || c1 > MAX) {
        printf("Invalid dimensions for Matrix A.\n");
        return 1;
    }

    printf("Enter rows and columns for Matrix B (1-%d): ", MAX);
    if (scanf("%d %d", &r2, &c2) != 2 || r2 < 1 || r2 > MAX || c2 < 1 || c2 > MAX) {
        printf("Invalid dimensions for Matrix B.\n");
        return 1;
    }

    readMatrix(A, r1, c1, 'A');
    readMatrix(B, r2, c2, 'B');

    do {
        printf("\n----------- MENU -----------\n");
        printf("1. Matrix Addition\n");
        printf("2. Matrix Multiplication\n");
        printf("3. Transpose of Matrix A\n");
        printf("4. Transpose of Matrix B\n");
        printf("5. Display both matrices\n");
        printf("0. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid menu input.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                if (r1 != r2 || c1 != c2) {
                    printf("Addition is not possible: dimensions must match.\n");
                } else {
                    addMatrices(A, B, result, r1, c1);
                    printf("A + B:\n");
                    displayMatrix(result, r1, c1);
                }
                break;

            case 2:
                if (c1 != r2) {
                    printf("Multiplication is not possible: columns of A must equal rows of B.\n");
                } else {
                    multiplyMatrices(A, B, result, r1, c1, c2);
                    printf("A x B:\n");
                    displayMatrix(result, r1, c2);
                }
                break;

            case 3:
                transposeMatrix(A, result, r1, c1);
                printf("Transpose of A:\n");
                displayMatrix(result, c1, r1);
                break;

            case 4:
                transposeMatrix(B, result, r2, c2);
                printf("Transpose of B:\n");
                displayMatrix(result, c2, r2);
                break;

            case 5:
                printf("Matrix A:\n");
                displayMatrix(A, r1, c1);
                printf("Matrix B:\n");
                displayMatrix(B, r2, c2);
                break;

            case 0:
                printf("Exiting Matrix Operations.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
