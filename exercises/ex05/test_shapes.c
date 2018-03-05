/* Example code for Exercises in C.

Copyright 2018 Allen Downey
MIT License

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shapes.h"


void test_point()
{
    Point *point = make_point(3.0, 4.0);
    char *s = point_to_string(point);
    printf("%s\n", s);
    free_point(point);
}

void test_rectangle()
{
    Point *corner = make_point(3.0, 4.0);
    Rectangle *rectangle = make_rectangle(corner, 5.0, 6.0);
    char *s = rectangle_to_string(rectangle);
    printf("%s\n", s);
    free_point(corner);
    free_rectangle(rectangle);
}

void test_point_in_rect(Point *point, Rectangle *rectangle)
{
    char *res;

    char *p_str = point_to_string(point);
    char *r_str = rectangle_to_string(rectangle);

    if (point_in_rect(point, rectangle)) {
        res = "is in";
    } else {
        res = "is not in";
    }
    printf("%s %s %s\n", p_str, res, r_str);
}

void main (int argc, char *argv[])
{
    test_point();
    test_rectangle();

    Point *corner = make_point(3.0, 4.0);
    Rectangle *rectangle = make_rectangle(corner, 5.0, 6.0);
    test_point_in_rect(corner, rectangle);

    Point *point2 = make_point(9.0, 5.0);
    printf("%s\n", point_to_string(point2));
    printf("%s\n", rectangle_to_string(rectangle));

    test_point_in_rect(point2, rectangle);

    free_point(corner);
    free_point(point2);
    free_rectangle(rectangle);
}
