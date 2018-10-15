#include "circle.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>

#include "point.h"
Circle::Circle() : r(0) {}
Circle::Circle(Point p, const double rin) : ctr(p), r(rin) {}
void Circle::move(double dx, double dy) {
  ctr.move(dx, dy);
}
double Circle::intersectionArea(const Circle & otherCircle) {
  double d = ctr.distanceFrom(otherCircle.ctr);
  double r2 = otherCircle.r;
  double d1 = (pow(r, 2) - pow(r2, 2) + pow(d, 2)) / (2 * d);
  double d2 = d - d1;
  if (this != &otherCircle) {
    if (d < abs(r - r2))
      return std::min(pow(r, 2), pow(r, 2)) * atan(1) * 4;  // *pi
    else {
      double intersect = pow(r, 2) * acos(d1 / r) - d1 * sqrt(pow(r, 2) - pow(d1, 2)) +
                         pow(r2, 2) * acos(d2 / r2) - d2 * sqrt(pow(r2, 2) - pow(d2, 2));
      return intersect;
    }
  }
  else
    return pow(r, 2) * atan(1) * 4;
}
