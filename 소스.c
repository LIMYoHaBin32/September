#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#define MAX_POINTS 100  // 최대 포인트 개수

int n = 0;  // 읽은 포인트의 개수

void read_fp(const char* filename, double X[], double Y[], double Angle[]) // 파일에서 웨이포인트 데이터를 읽어오는 함수

{
    FILE* fp = fopen(filename, "r");

    if (!fp)
    {
        printf("파일을 찾을 수 없어용.\n");
        return;
    }

    while (fscanf(fp, "%lf %lf %lf", &X[n], &Y[n], &Angle[n]) != EOF && n < MAX_POINTS) // 파일에서 데이터 읽기
    {
        n++;
    }

    fclose(fp);
}

void calculate_yaw_angles(double x[], double y[], double yaw_angle[]) // 두 웨이포인트 간의 요aw 각도를 계산하는 함수
{
    for (int i = 0; i < n - 1; i++)
    {
        double dx = x[i + 1] - x[i];  // x 방향 차이
        double dy = y[i + 1] - y[i];  // y 방향 차이

        double angle = atan2(dy, dx) * 180.0 / 3.141592; // atan2 함수를 사용하여 각도 계산 (라디안 -> 도 단위 변환)

        if (angle < 0) angle += 360.0; // 음수 각도를 양수로 변환

        yaw_angle[i] = angle;
    }
}

void print_waypoints(double X[], double Y[], double Angle[]) // 웨이포인트 데이터를 출력하는 함수

{
    for (int i = 0; i < n; i++)
        printf("X[%d] = %lf, Y[%d] = %lf, Angle[%d] = %lf\n", i, X[i], i, Y[i], i, Angle[i]);
}

void print_yaw_angles(double yaw_angle[]) // 계산된 yaw 각도를 출력하는 함수
{
    for (int i = 0; i < n - 1; i++)
        printf("Yaw angle between waypoint %d and %d: %.2f degrees\n", i, i + 1, yaw_angle[i]);
}

int main(void)
{
    double X[MAX_POINTS] = { 0.0 }, Y[MAX_POINTS] = { 0.0 }, Angle[MAX_POINTS] = { 0.0 };
    double yaw_angle[MAX_POINTS] = { 0.0 };
    read_file("waypoint.txt", X, Y, Angle); // 파일에서 웨이포인트 데이터 읽기

    printf("waypoint data:\n");
    print_waypoints(X, Y, Angle);

    printf("\n Yaw angles between waypoints:\n"); // yaw 각도 계산 및 출력
    calculate_yaw_angles(X, Y, yaw_angle);
    print_yaw_angles(yaw_angle);

    return 0;
}
