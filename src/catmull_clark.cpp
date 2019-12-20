#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>
#include <vector>

#include <vertex_triangle_adjacency.h>

/**
 * Helper function declarations
 */


/**
 * Main function
 */
void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  ////////////////////////////////////////////////////////////////////////////
  /**
   * Sources:
   * https://en.wikipedia.org/wiki/Catmull%E2%80%93Clark_subdivision_surface
   * https://www.algosome.com/articles/catmull-clark-subdivision-algorithm.html
   */
  if (num_iters <= 0) {
    return;
  }

  SV = V;                      // SV  #SV by 3 list of vertex positions
  SF = F;                      // SF  #SF by 4 list of quad mesh indices into SV

  ////////////////////////////////////////////////////////////////////////////
}


/**
 * For each face at index <i> in F, we can find the center point of that face
 * at index <i> in the vector FP
 */
// std::vector<double> face_points(
//   const Eigen::MatrixXd & V,
//   const Eigen::MatrixXi & F)
// {
//   std::vector<double> FP;

//   for (int i = 0; i < F.rows(); i++) {
//     // Get the face center point
//     FP.emplace_back((V.row(F(i, 0)) + V.row(F(i, 1)) + V.row(F(i, 2)) + V.row(F(i, 3))) / 4.0);
//   }

//   return FP;
// }


// Eigen::Vector3d edge_point_ave(
//   const Eigen::RowVector3d & e1,
//   const Eigen::RowVector3d & e2,
//   const Eigen::RowVector3d & fp1,
//   const Eigen::RowVector3d & fp2)
// {
//   return (e1 + e2 + fp1 + fp2) / 4.0;
// }


// Eigen::RowVector3d face_point_center(
//   const Eigen::MatrixXd & V,
//   const Eigen::MatrixXi & F,
//   const int row)
// {
//   // center = (a + b + c + d) / 4
//   return (V.row(F(row, 0)) + V.row(F(row, 1)) + V.row(F(row, 2)) + V.row(F(row, 3))) / 4.0;
// }




// Conduct num_iters iterations of Catmull-Clark subdivision on a **pure quad**
// mesh (V,F).
//
// Inputs:
//   V  #V by 3 list of vertex positions
//   F  #F by 4 list of quad mesh indices into V
//   num_iters  number of iterations
// Outputs:
//   SV  #SV by 3 list of vertex positions
//   SF  #SF by 4 list of quad mesh indices into SV
