#include "vertex_triangle_adjacency.h"

void vertex_triangle_adjacency(
  const Eigen::MatrixXi & F,
  const int num_vertices,
  std::vector<std::vector<int> > & VF)
{
  VF.resize(num_vertices);
  ////////////////////////////////////////////////////////////////////////////
  // Iterate through all the vertices V[i]
  for (int i = 0; i < num_vertices; i++) {

    // Iterate through all the faces
    for (int j = 0; j < F.rows(); j++) {
      int idx1 = F(j, 0);
      int idx2 = F(j, 1);
      int idx3 = F(j, 2);

      if (i == idx1 || i == idx2 || i == idx3) {
        // Then this face corresponds with vertex i
        VF[i].push_back(j);
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

/**
 * NOTE: VF[i] is a vector of indices to row indices of F that share vertex V[i]
 *
 * eg) If I have a vertex index in V, say k,
 * then VF[k] is a list of all the indices to rows of F that share the vertex
 * given by V[k]
 *
 * VF  num_verticess-long list of lists so that f=VF[i][j] means that face f
 * is the jth face among those incident on vertex i. Adjacency faces are listed
 * in no particular order (but no duplicates).
 */
