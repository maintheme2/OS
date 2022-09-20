#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
}point_t;

double 
get_distance(point_t point1, point_t point2) {
    double x_diff = point2.x - point1.x;
    double y_diff = point2.y - point1.y;
    double distance = pow(pow(x_diff, 2) + pow(y_diff, 2), (double)0.5);
    return distance;
}

double
get_area(point_t A, point_t B, point_t C) {
    double side_AB_len = get_distance(A, B);
    double side_BC_len = get_distance(B, C);
    double side_AC_len = get_distance(A, C);
    double p = (side_AB_len + side_AC_len + side_BC_len) / 2;
    double area = pow((double)(p*(p-side_AB_len)*(p-side_BC_len)*(p-side_AC_len)), (double)0.5);
    return area;
}

int 
main(int argc, char const *argv[]) {
    point_t A = { 2.5, 6 };
    point_t B = { 1, 2.2 };
    point_t C = { 10, 6 };
    double distance = get_distance(A, B);
    double area = get_area(A, B, C);
    printf("%f\n", distance);
    printf("%f\n", area);
    return 0;
}