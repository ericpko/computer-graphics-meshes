#include "sphere.h"
#include <iostream>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  /**
   * Sources:
   * Fundamentals of Computer Graphics: page 42, chap 11
   * James Stewart Multivariable Calculus: pages 1086, 1152
   */
  // Set up some constants
  int nvertices = (num_faces_u + 1) * (num_faces_v + 1);
  double rho = 1.0;                    // let rho = r = 1. Assume radius = 1

  // Set the 3D vertices, UV coordinates, and normals
  V.resize(nvertices, 3);
  UV.resize(nvertices, 2);
  NV.resize(nvertices, 3);

  // The parameter domain D = [0, pi] x [0, 2pi]
  int row = 0;
  for (int v_i = 0; v_i < num_faces_v + 1; v_i++) { // NOTE the + 1 since we're iterating over verts
    // Convert index v into it's normalized coordinate -- v in [0, 1]
    double v = static_cast<double>(v_i) / num_faces_v;
    // Convert v into theta. 0 <= theta <= 2pi
    double theta = v * 2.0 * M_PI;

    for (int u_i = 0; u_i < num_faces_u + 1; u_i++) {
      // Convert index u into it's normalized coordinate -- u in [0, 1]
      double u = static_cast<double>(u_i) / num_faces_u;
      // Convert u into phi. 0 <= phi <= pi
      double phi = u * M_PI;

      // Now that we have rho, theta, phi, we can find x, y, z
      double x = rho * sin(phi) * cos(theta);
      double y = rho * sin(phi) * sin(theta);
      double z = rho * -cos(phi);             // must be negative or else we get the map reflected

      // Remember - these are just arbitrary (not in this case though)
      V.row(row) = Eigen::RowVector3d(y, z, x);     // r(phi, theta) = <x, y, z>
      UV.row(row) = Eigen::RowVector2d(v, u);       // NOTE (u, v) are inverted
      NV.row(row++) = Eigen::RowVector3d(y, z, x);
    }
  }

  // Set the faces --- Order matters
  int nfaces = num_faces_u * num_faces_v;
  F.resize(nfaces, 4);
  UF.resize(nfaces, 4);
  NF.resize(nfaces, 4);
  row = 0;                                        // reset index
  for (int v_i = 0; v_i < num_faces_v; v_i++) {   // NOTE we iterate over the faces here
    for (int u_i = 0; u_i < num_faces_u; u_i++) {
      // Now we need to find the indices of the vertices
      int v1 = v_i * (num_faces_u + 1) + u_i; // row * (height) + col
      int v2 = v1 + 1;
      int v3 = (v_i + 1) * (num_faces_u + 1) + u_i + 1;
      int v4 = v3 - 1;

      // Set F -- Order matters -- indices into V
      F.row(row) = Eigen::RowVector4i(v1, v2, v3, v4);
      // Set the texture indices that correspond with F
      // UF[i, j] are indices into vt/UV
      UF.row(row) = Eigen::RowVector4i(v1, v2, v3, v4);
      // NF[i, j] are indices into vn/NV
      NF.row(row++) = Eigen::RowVector4i(v1, v2, v3, v4);
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}


/**
 * NOTE: The solution above works, however, this is quite miraculous.
 * There are a couple of pieces that I just played around with until
 * they worked (not good).
 * I will set this up by saying that my solution below is intuitive and works..
 * well sort of works. Everything gets mapped, but inverted, backwards, the
 * globe spins the wrong way, etc. It's weird. So instead of working out my
 * bugs logically (which I tried first), I just played around the variables
 * (since it was really close to working) until it just worked.
 *
 *
 * I don't know why adding the negative in z = -cos(phi) puts the proper
 * mirror image on the surface sphere S. (Florida points to the right!)
 *
 * I don't know why I had to invert the (u, v) coordinates in the UV matrix
 *
 * I don't know why on earth I had to put the xyz coordinates in V in the order:
 * y, z, x
 * That makes no sense to me, but it has to do with moving the image around
 * in libigl viewer.
 *
 * I have some guesses as to why changing these variables produces the correct
 * results, but honestly, it just seems like it works by magic.
 */














/**
 * This version below produces a completely accurate mapping, but turning
 * the globe is messed up
 */
// #include "sphere.h"
// #include <iostream>

// void sphere(
//   const int num_faces_u,
//   const int num_faces_v,
//   Eigen::MatrixXd & V,
//   Eigen::MatrixXi & F,
//   Eigen::MatrixXd & UV,
//   Eigen::MatrixXi & UF,
//   Eigen::MatrixXd & NV,
//   Eigen::MatrixXi & NF)
// {
//   ////////////////////////////////////////////////////////////////////////////
//   /**
//    * See page 42 in textbook and pages 1086, 1152 in Multivar calc book
//    */
//   // Set up some constants
//   int nvertices = (num_faces_u + 1) * (num_faces_v + 1);
//   double rho = 1.0;                    // let rho = r = 1. Assume radius = 1

//   // Set the 3D vertices, UV coordinates, and normals
//   V.resize(nvertices, 3);
//   UV.resize(nvertices, 2);
//   NV.resize(nvertices, 3);

//   // The parameter domain D = [0, pi] x [0, 2pi]
//   int row = 0;
//   for (int v_i = 0; v_i < num_faces_v + 1; v_i++) { // NOTE the + 1 since we're iterating over verts
//     // Convert index v into it's normalized coordinate -- v in [0, 1]
//     double v = static_cast<double>(v_i) / num_faces_v;
//     // Convert v into theta. 0 <= theta <= 2pi
//     double theta = v * 2.0 * M_PI;

//     for (int u_i = 0; u_i < num_faces_u + 1; u_i++) {
//       // Convert index u into it's normalized coordinate -- u in [0, 1]
//       double u = static_cast<double>(u_i) / num_faces_u;
//       // Convert u into phi. 0 <= phi <= pi
//       double phi = u * M_PI;

//       // Now that we have rho, theta, phi, we can find x, y, z
//       double x = rho * sin(phi) * cos(theta);
//       double y = rho * sin(phi) * sin(theta);
//       double z = rho * cos(phi);

//       // Remember - these are just arbitrary (not in this case though)
//       V.row(row) = Eigen::RowVector3d(x, y, z);     // r(phi, theta) = <x, y, z>
//       UV.row(row) = Eigen::RowVector2d(u, v);
//       NV.row(row++) = Eigen::RowVector3d(x, y, z);
//     }
//   }

//   // Set the faces --- Order matters
//   int nfaces = num_faces_u * num_faces_v;
//   F.resize(nfaces, 4);
//   UF.resize(nfaces, 4);
//   NF.resize(nfaces, 4);
//   row = 0;                                        // reset index
//   for (int v_i = 0; v_i < num_faces_v; v_i++) {   // NOTE we iterate over the faces here
//     for (int u_i = 0; u_i < num_faces_u; u_i++) {
//       // Now we need to find the vertices that make up each face in counter-clockwise order
//       int v1 = v_i * (num_faces_u + 1) + u_i; // row * (height) + col
//       int v2 = (v_i + 1) * (num_faces_u + 1) + u_i;
//       int v3 = v2 + 1;
//       int v4 = v1 + 1;

//       // Set F -- Order matters -- indices into V
//       F.row(row) = Eigen::RowVector4i(v1, v2, v3, v4);
//       // Set the texture indices that correspond with F
//       // UF[i, j] are indices into vt/UV
//       UF.row(row) = Eigen::RowVector4i(v1, v2, v3, v4);
//       // NF[i, j] are indices into vn/NV
//       NF.row(row++) = Eigen::RowVector4i(v1, v2, v3, v4);
//     }
//   }
//   ////////////////////////////////////////////////////////////////////////////
// }
