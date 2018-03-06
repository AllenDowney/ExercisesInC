/* Example code for Exercises in C.

1. write a function called `make_line` that
takes two pointers to `Point` as parameters and returns a pointer
to a freshly-allocated `Line`.  It should not allocate any new
`Point` objects.

2. Draw a stack diagram that shows the state of `main`
and `upper_right_rect` at the instant before `upper_right_rect`
completes.

3. Optional: Write a function called `diagonal_rect` that takes
a Rectangle pointer and returns a new Line that connects the
upper left and lower right corners of the Rectangle.

4. Optional: `equal_point` compares floating-point numbers, which
is unreliable.  Read about comparing floating-point numbers, and
implement a better version of `equal_point`.

See https://bitbashing.io/comparing-floats.html

Copyright 2018 Allen Downey
MIT License

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "shapes.h"

typedef struct {
    Point *start, *end;
} Line;

/* Return a new Line

x, y: coordinates

returns: new Line; use free_line to free
*/
// TODO: Write this function

/* Return string representation

line: Line
*/
char *line_to_string(Line *line) {
    char *buffer = malloc(BUFSIZE);
    char *start_str = point_to_string(line->start);
    char *end_str = point_to_string(line->end);
    snprintf(buffer, BUFSIZE, "Line(%s, %s)", start_str, end_str);
    return buffer;
}

/* Free a Line

line: Line
*/
void free_line(Line *line) {
    // Optional TODO: free embedded Points?
    free(line);
}

/* Find the line from the upper left to the lower right.

rect: Rectangle

returns: Line
*/
// Optional TODO: Write this function


/* Check whether two points are equal.

p1, p1: Points

returns: 1 if equal else 0
*/

int equal_point(Point *p1, Point *p2) {
    // Optional TODO: handle floating point comparison properly
    if (p1->x != p2->x) return 0;
    if (p1->y != p2->y) return 0;
    return 1;
}

/* Find the upper right corner of a Rectangle.

rect: Rectangle

returns: Point
*/
Point *upper_right_rect(Rectangle *rect) {
    double x = rect->corner->x;
    double y = rect->corner->y;
    Point *p = make_point(x + rect->width, y + rect->height);
    return p;
}

void main (int argc, char *argv[]) {
    Point *lower_left = make_point(3.0, 4.0);
    Point *upper_right = make_point(5.0, 6.0);

    printf("%s\n", point_to_string(lower_left));
    printf("%s\n", point_to_string(upper_right));

    Rectangle *rectangle = make_rectangle(lower_left, 2.0, 2.0);
    printf("%s\n", rectangle_to_string(rectangle));

    Point *result = upper_right_rect(rectangle);
    printf("%s\n", point_to_string(result));

    assert(equal_point(result, upper_right));
}
