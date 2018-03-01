/* Example code for Exercises in C.

Copyright 2018 Allen Downey
MIT License

1) Fill in the body of make_rectangle.  Make a copy of corner.

2) Fill in the body of free_rectangle.

3) Fill in the body of point_in_rect.

4) Check that the results of the tests look correct.

5) Check for memory leaks; does everything that gets allocated get freed?
   How much harder would this be if we did not make a safety copy in make_rectangle?

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 100

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point *corner;
    double width, height;
} Rectangle;

/* Return a new Point

x, y: coordinates

returns: new Point; use free_point to free
*/
Point *make_point(double x, double y) {
    Point *new = malloc(sizeof(Point));
    new->x = x;
    new->y = y;
    return new;
}

/* Return string representation

point: Point
*/
char *point_to_string(Point *point) {
    char *buffer = malloc(BUFSIZE);
    snprintf(buffer, BUFSIZE, "Point(%f, %f)", point->x, point->y);
    return buffer;
}

/* Free a Point

point: Point
*/
void free_point(Point *point) {
    free(point);
}

/* Return a new Rectangle

x, y: coordinates

returns: new Rectangle; use free_rectangle to free
*/
Rectangle *make_rectangle(Point *corner, double width, double height) {
    Rectangle *new = malloc(sizeof(Rectangle));

    // make a safety copy of corner
    new->corner = make_point(corner->x, corner->y);
    new->width = width;
    new->height = height;
    return new;
}

/* Return string representation

rectangle: Rectangle
*/
char *rectangle_to_string(Rectangle *rectangle) {
    char *buffer = malloc(BUFSIZE);
    char *s = point_to_string(rectangle->corner);

    snprintf(buffer, BUFSIZE, "Rectangle(%s, %f, %f)",
                               s, rectangle->width, rectangle->height);
    return buffer;
}

/* Free a Rectangle

rectangle: Rectangle
*/
void free_rectangle(Rectangle *rectangle) {
    free(rectangle->corner);
    free(rectangle);
}

/* Check whether a point is inside a rectangle.

The corner indicates the lower-left corner, and the positive-y axis is up.

On the line is in.

returns: 1 if the point is in the rectangle, else 0
*/
int point_in_rect(Point *p, Rectangle *rect) {
    double x = rect->corner->x;
    double y = rect->corner->y;

    if (p->x < x) return 0;
    if (p->y < y) return 0;
    if (p->x > x + rect->width) return 0;
    if (p->y > y + rect->height) return 0;

    return 1;
}

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
