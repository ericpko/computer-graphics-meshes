#include "per_corner_normals.h"
#include "triangle_area_normal.h"
#include <iostream>
// Hint:
#include "vertex_triangle_adjacency.h"

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  ////////////////////////////////////////////////////////////////////////////
  /**
   * NOTE: the below solution works, but I am not content about the threshold
   * part. It is very sensitive and won't allow me to compare radians or
   * degrees, only when I convert both to their cosine values, even though
   * theoretically these comparisons should be the same.
   */
  N = Eigen::MatrixXd::Zero(F.rows() * 3, 3);

  // Convert corner_threshold from degrees to radians
  const double cos_threshold = cos(corner_threshold * M_PI / 180.0);

  // Get the triangle adjacency list
  std::vector<std::vector<int> > VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  // Iterate over each face
  for (int i = 0; i < F.rows(); i++) {
    Eigen::RowVector3d v1 = V.row(F(i, 0));
    Eigen::RowVector3d v2 = V.row(F(i, 1));
    Eigen::RowVector3d v3 = V.row(F(i, 2));

    Eigen::RowVector3d area_n1 = triangle_area_normal(v1, v2, v3);

    // Iterate over each index of V. (i.e. F(i, j) is an index into V)
    for (int j = 0; j < F.cols(); j++) {
      // Initialize the sum of area normal vectors to zero
      Eigen::RowVector3d area_normal_sum(0, 0, 0);

      // Iterate over the adjacency list
      for (int k : VF[F(i, j)]) {
        Eigen::RowVector3d v4 = V.row(F(k, 0));
        Eigen::RowVector3d v5 = V.row(F(k, 1));
        Eigen::RowVector3d v6 = V.row(F(k, 2));

        Eigen::RowVector3d area_n2 = triangle_area_normal(v4, v5, v6);

        double cos_theta = (area_n1.normalized()).dot((area_n2.normalized()));
        if (cos_theta > cos_threshold) {
          area_normal_sum += area_n2;
        }
      }

      N.row(i * 3 + j) = area_normal_sum.normalized();
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

// Compute per corner normals for a triangle mesh by computing the area-weighted
// average of normals at incident faces whose normals deviate less than the
// provided threshold.
//
// Inputs:
//   V  #V by 3 list of vertex positions
//   F  #F by 3 list of mesh triangle indices into V
//   corner_threshold  threshold in degrees on sharp angles
// Outputs:
//   N  #F*3 by 3 list of mesh vertex 3D normals, where the normal
//     for corner F(i,j) is at N.row(i*3+j)






/**
 * Below is my original solution. It doesn't quite work, but I think I was
 * onto something. I think it's possible to get this way to work, but w/e
 * I iterated over each vertex in this method
 */
// #include "per_corner_normals.h"
// #include "triangle_area_normal.h"
// // Hint:
// #include "vertex_triangle_adjacency.h"
// #include <iostream>

// void per_corner_normals(
//   const Eigen::MatrixXd & V,
//   const Eigen::MatrixXi & F,
//   const double corner_threshold,
//   Eigen::MatrixXd & N)
// {
//   ////////////////////////////////////////////////////////////////////////////
//   N = Eigen::MatrixXd::Zero(F.rows() * 3, 3);

//   // Convert corner_threshold from degrees to radians
//   const double threshold = cos(corner_threshold * M_PI / 180.0);

//   // Get the triangle adjacency list
//   std::vector<std::vector<int> > VF;
//   vertex_triangle_adjacency(F, V.rows(), VF);

//   for (int i = 0; i < V.rows(); i++) {
//     // Initialize the sum of area normal vectors to zero
//     Eigen::RowVector3d area_normal_sum(0, 0, 0);

//     // Our vertex of interest is: V[i]

//     // Get the jth face among those incident on vertex i as our benchmark
//     for (int j : VF[i]) {
//       // Get one of the faces of vertex i
//       Eigen::RowVector3d v1 = V.row(F(j, 0));
//       Eigen::RowVector3d v2 = V.row(F(j, 1));
//       Eigen::RowVector3d v3 = V.row(F(j, 2));

//       Eigen::RowVector3d area_n1 = triangle_area_normal(v1, v2, v3);  // n_f

//       // Check all the adjacency faces of vertext V[i]
//       for (int k : VF[i]) {
//         // Check the comparing faces normals against the zeroeth's face normal
//         Eigen::RowVector3d v4 = V.row(F(k, 0));
//         Eigen::RowVector3d v5 = V.row(F(k, 1));
//         Eigen::RowVector3d v6 = V.row(F(k, 2));

//         Eigen::RowVector3d area_n2 = triangle_area_normal(v4, v5, v6);  //n_g

//         // Check the angle between the normals
//         double theta = (area_n1.normalized()).dot((area_n2.normalized()));
//         if (theta > threshold) {
//           area_normal_sum += area_n2;
//         }
//       }
//     }

//     // Now we can set the unit normal for this vertex
//     N.row(i) = area_normal_sum.normalized();
//   }
//   ////////////////////////////////////////////////////////////////////////////
// }
