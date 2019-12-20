#include "per_vertex_normals.h"
#include "triangle_area_normal.h"

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  ////////////////////////////////////////////////////////////////////////////
  N = Eigen::MatrixXd::Zero(V.rows(), 3);

  for (int i = 0; i < V.rows(); i++) {
    // Initialize the sum of area normal vectors to zero
    Eigen::RowVector3d area_normal_sum = Eigen::RowVector3d(0, 0, 0);

    // Get the vertex of interest
    Eigen::RowVector3d vertex = V.row(i);

    // Find all the faces that include this vertex
    for (int f = 0; f < F.rows(); f++) {
      Eigen::RowVector3d v1 = V.row(F(f, 0));
      Eigen::RowVector3d v2 = V.row(F(f, 1));
      Eigen::RowVector3d v3 = V.row(F(f, 2));

      if (vertex != v1 && vertex != v2 && vertex != v3) {
        continue;
      }

      // If we get here, then we know that this face shares vertex <vertex>
      area_normal_sum += triangle_area_normal(v1, v2, v3);
    }

    // Now we can set the unit normal for this vertex
    N.row(i) = area_normal_sum.normalized();
  }
  ////////////////////////////////////////////////////////////////////////////
}
