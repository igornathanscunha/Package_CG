#ifndef CG_MATH_ROTATION2D_H
#define CG_MATH_ROTATION2D_H

#include "cg/geometry/point2d.h"

double degrees_to_radians(int angle);
int rotate_plan_2d_x(int x, int y, double radians);
int rotate_plan_2d_y(int x, int y, double radians);
point_2d rotate_plan_2d(int x, int y, double radians);
point_2d rotate_inverse_plan_2d(int x, int y, double radians);
point_2d rotate_plan_2d_cisalhamento(int x, int y, int angle);

#endif