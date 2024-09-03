#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
    int temp;
    int A[100] = { 0, };
    int n = 0;
    FILE* fp = fopen("data.txt", "r");


    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    do {
        if (fscanf(fp, "%d", &temp) == 1) {
            A[n] = temp;
            n++;
        }
        else break;
    } while (A[n] != EOF);

    fclose(fp);

    printf("파일의 개수: %d\n\n", n);
    printf("파일에서 읽은 값들:\n\n");
    for (int i = 0; i < n; i++) {
        printf("%d\n", A[i]);
    }
    printf("\n");

    return 0;
}