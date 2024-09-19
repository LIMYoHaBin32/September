#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void matrixAdd(int a[][3], int b[][3], int c[][3])
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            c[i][j] = a[i][j] + b[i][j];
}

void scalarMultiply(int a[][3], int scalar, int c[][3])
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            c[i][j] = a[i][j] * scalar;
}

void printMatrix(int a[][3])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            printf("%5d", a[i][j]);
        }
        printf("\n");
    }
}

void readMatrix(int a[][3])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            scanf_s("%d", &a[i][j]);
        }
    }
}

int main(void)
{
    int A[3][3], B[3][3], C[3][3];

    printf("(3 x 3) ��� A �Է� : \n");
    readMatrix(A);

    printf("(3 x 3) ��� B �Է�: \n");
    readMatrix(B);

    matrixAdd(A, B, C);
    printf("��� A�� B�� ��:\n");
    printMatrix(C);

    int scalar;

    printf("��Į�� �� �Է�: ");
    scanf_s("%d", &scalar);

    scalarMultiply(A, scalar, C);
    printf("A�� ���� ��Į�� ��:\n");
    printMatrix(C);

    scalarMultiply(B, scalar, C);
    printf("B�� ���� ��Į�� ��:\n");
    printMatrix(C);

    return 0;
}
