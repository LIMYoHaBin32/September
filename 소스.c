#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int n = 0;

void read_file(const char* filename, double X[], double Y[], double Angle[])
{
    FILE* file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("파일을 찾을 수 없어용~\n");
        return;
    }

    while (fscanf(file, "%lf %lf %lf", &X[n], &Y[n], &Angle[n]) != EOF)
    {
        n++;
        if (n >= 100)
        {
            break;
        }
    }

    fclose(file);
}

void interval(double X_ref[], double Y_ref[], double X[], double Y[])
{
    for (int i = 1; i < n; ++i)
    {
        X_ref[i] = X[i] - X[i - 1];
        Y_ref[i] = Y[i] - Y[i - 1];
    }
}

void relative_coordinate(double X_ref[], double Y_ref[], double X[], double Y[])
{
    for (int i = 0; i < n; ++i)
    {
        X_ref[i] = X[i] - X[0];
        Y_ref[i] = Y[i] - Y[0];
    }
}

void DIST(double X[], double Y[], double Dist[])
{
    for (int i = 1; i < n; ++i)
    {
        Dist[i] = sqrt((X[i] - X[i - 1]) * (X[i] - X[i - 1]) + (Y[i] - Y[i - 1]) * (Y[i] - Y[i - 1]));
    }
}

void YawAngles(double x[], double y[], int count, double yaw_angle[])
{
    for (int i = 0; i < n - 1; i++)
    {
        double dx = x[i + 1] - x[i];
        double dy = y[i + 1] - y[i];

        double angle = atan2(dy, dx) * 180.0 / 3.141592;

        if (angle < 0) angle += 360.0;

        yaw_angle[i] = angle;
    }

}

void ascending_sort(double X[], double Y[], double Angle[], double Dist[], int column)
{
    double temp = 0;
    for (int i = 0; i < column; i++)
    {
        for (int j = i; j < column; j++)
        {
            if (Dist[i] > Dist[j])
            {
                temp = Dist[i];
                Dist[i] = Dist[j];
                Dist[j] = temp;

                temp = X[i];
                X[i] = X[j];
                X[j] = temp;

                temp = Y[i];
                Y[i] = Y[j];
                Y[j] = temp;

                temp = Angle[i];
                Angle[i] = Angle[j];
                Angle[j] = temp;
            }
        }
    }
}

void descending_sort(double X[], double Y[], double Angle[], double Dist[], int column)
{   
    double temp = 0;
    for (int i = 0; i < column; i++)
    {
        for (int j = i; j < column; j++)
        {
            if (Dist[i] < Dist[j])
            {
                temp = Dist[i];
                Dist[i] = Dist[j];
                Dist[j] = temp;

                temp = X[i];
                X[i] = X[j];
                X[j] = temp;

                temp = Y[i];
                Y[i] = Y[j];
                Y[j] = temp;

                temp = Angle[i];
                Angle[i] = Angle[j];
                Angle[j] = temp;
            }
        }
    }
}

void Equation(double X[], double Y[], double a[], double b[])
{
    for (int i = 0; i < n; ++i)
    {
        a[i] = (Y[i + 1] - Y[i]) / (X[i + 1] - X[i]);
        b[i] = Y[i] - (a[i] * X[i]);
    }
}



int main(void)
{
    double X[100] = { 0.0 };
    double Y[100] = { 0.0 };
    double Angle[100] = { 0.0 };
    double X_ref[100] = { 0.0 };
    double Y_ref[100] = { 0.0 };
    double Dist[100] = { 0.0 };
    double yaw_angle[100] = { 0.0 };
    double Distance[100] = { 0.0 };
    double a[100] = { 0.0 };
    double b[100] = { 0,0 };
    int num = 0;

    read_file("waypoint.txt", X, Y, Angle);
    
    Equation(X, Y, a, b);
    for (int i = 0; i < n-1; i++)
    {
        printf("직선의 방정식 : [%d ~ %d]: y = %lfx + %lf \n ", i, i + 1, a[i], b[i]);
    }
    return 0;
}