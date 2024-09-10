#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#define MAX_POINTS 100  // �ִ� ����Ʈ ����

int n = 0;  // ���� ����Ʈ�� ����

void read_fp(const char* filename, double X[], double Y[], double Angle[]) // ���Ͽ��� ��������Ʈ �����͸� �о���� �Լ�

{
    FILE* fp = fopen(filename, "r");

    if (!fp)
    {
        printf("������ ã�� �� �����.\n");
        return;
    }

    while (fscanf(fp, "%lf %lf %lf", &X[n], &Y[n], &Angle[n]) != EOF && n < MAX_POINTS) // ���Ͽ��� ������ �б�
    {
        n++;
    }

    fclose(fp);
}

void calculate_yaw_angles(double x[], double y[], double yaw_angle[]) // �� ��������Ʈ ���� ��aw ������ ����ϴ� �Լ�
{
    for (int i = 0; i < n - 1; i++)
    {
        double dx = x[i + 1] - x[i];  // x ���� ����
        double dy = y[i + 1] - y[i];  // y ���� ����

        double angle = atan2(dy, dx) * 180.0 / 3.141592; // atan2 �Լ��� ����Ͽ� ���� ��� (���� -> �� ���� ��ȯ)

        if (angle < 0) angle += 360.0; // ���� ������ ����� ��ȯ

        yaw_angle[i] = angle;
    }
}

void print_waypoints(double X[], double Y[], double Angle[]) // ��������Ʈ �����͸� ����ϴ� �Լ�

{
    for (int i = 0; i < n; i++)
        printf("X[%d] = %lf, Y[%d] = %lf, Angle[%d] = %lf\n", i, X[i], i, Y[i], i, Angle[i]);
}

void print_yaw_angles(double yaw_angle[]) // ���� yaw ������ ����ϴ� �Լ�
{
    for (int i = 0; i < n - 1; i++)
        printf("Yaw angle between waypoint %d and %d: %.2f degrees\n", i, i + 1, yaw_angle[i]);
}

int main(void)
{
    double X[MAX_POINTS] = { 0.0 }, Y[MAX_POINTS] = { 0.0 }, Angle[MAX_POINTS] = { 0.0 };
    double yaw_angle[MAX_POINTS] = { 0.0 };
    read_file("waypoint.txt", X, Y, Angle); // ���Ͽ��� ��������Ʈ ������ �б�

    printf("waypoint data:\n");
    print_waypoints(X, Y, Angle);

    printf("\n Yaw angles between waypoints:\n"); // yaw ���� ��� �� ���
    calculate_yaw_angles(X, Y, yaw_angle);
    print_yaw_angles(yaw_angle);

    return 0;
}
