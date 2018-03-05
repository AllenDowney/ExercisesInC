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
#include "shapes.h"


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
    free_point(rectangle->corner);
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
