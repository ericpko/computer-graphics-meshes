#include "triangle_area_normal.h"
#include <Eigen/Geometry>

Eigen::RowVector3d triangle_area_normal(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c)
{
  ////////////////////////////////////////////////////////////////////////////
  Eigen::RowVector3d ab = b - a;
  Eigen::RowVector3d ac = c - a;

  // Compute the normal of the triangle
  Eigen::RowVector3d n = ab.cross(ac);

  // Compute the area of the triangle
  double area = (1.0 / 2.0) * n.norm();


  return area * n.normalized();
  ////////////////////////////////////////////////////////////////////////////
}
