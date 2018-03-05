/* Example code for Exercises in C.

Copyright 2018 Allen Downey
MIT License

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
Point *make_point(double x, double y);

/* Return string representation

point: Point
*/
char *point_to_string(Point *point);

/* Free a Point

point: Point
*/
void free_point(Point *point);

/* Return a new Rectangle

x, y: coordinates

returns: new Rectangle; use free_rectangle to free
*/
Rectangle *make_rectangle(Point *corner, double width, double height);

/* Return string representation

rectangle: Rectangle
*/
char *rectangle_to_string(Rectangle *rectangle);

/* Free a Rectangle

rectangle: Rectangle
*/
void free_rectangle(Rectangle *rectangle);

/* Check whether a point is inside a rectangle.

The corner indicates the lower-left corner, and the positive-y axis is up.

On the line is in.

returns: 1 if the point is in the rectangle, else 0
*/
int point_in_rect(Point *p, Rectangle *rect);
