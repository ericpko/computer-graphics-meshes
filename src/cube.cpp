#include "cube.h"

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  /**
   * https://en.wikipedia.org/wiki/Polygon_mesh
   * Picture: http://ilkinulas.github.io/development/unity/2016/04/30/cube-mesh-in-unity3d.html
   */

  // Add the vertices of the cube. Arbitrary order
  V.resize(8,3);
  V << 0, 0, 0,
       0, 1, 0,
       1, 1, 0,
       1, 0, 0,
       0, 0, 1,
       1, 0, 1,
       1, 1, 1,
       0, 1, 1;


  // Six faces of a cube. --- bottom, top, front, back, left, right
  // See Ipad, normals must point outward
  F.resize(6,4);
  F << 0, 1, 2, 3,
       4, 5, 6, 7,
       5, 3, 2, 6,
       4, 7, 1, 0,
       5, 4, 0, 3,
       6, 2, 1, 7;

  // Set the texture coordinates. These are arbitrarily ordered just like vertices list
  UV.resize(14,2);
  UV << 0.0, 0.5,
        0.25, 0.5,
        0.5, 0.5,
        0.75, 0.5,
        1.0, 0.5,
        1.0, 0.25,
        0.75, 0.25,
        0.5, 0.25,
        0.25, 0.25,
        0.0, 0.25,
        0.25, 0.75,
        0.5, 0.75,
        0.25, 0.0,
        0.5, 0.0;

  // Set the texture indices that correspond with F
  // UF[i, j] are indices into vt/UV
  // From webpage, bottom = white, front = blue, top = yellow, left = green, back = red, right = orange
  UF.resize(6,4);
  UF << 8, 7, 13, 12,
        10, 11, 2, 1,
        2, 3, 6, 7,
        0, 1, 8, 9,
        1, 2, 7, 8,
        3, 4, 5, 6;


  // These are arbitrarily ordered --- bottom, top, front, back, left, right
  NV.resize(6,3);
  NV << 0, 0, -1,
        0, 0, 1,
        1, 0, 0,
        -1, 0, 0,
        0, -1, 0,
        0, 1, 0;

  // NF[i, j] are indices into vn/NV
  NF.resize(6,4);
  NF << 0, 0, 0, 0,
        1, 1, 1, 1,
        2, 2, 2, 2,
        3, 3, 3, 3,
        4, 4, 4, 4,
        5, 5, 5, 5;
  ////////////////////////////////////////////////////////////////////////////
}
