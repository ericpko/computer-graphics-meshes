#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  ////////////////////////////////////////////////////////////////////////////
  /**
   * Write to an WaveFront .obj file.
   * https://en.wikipedia.org/wiki/Wavefront_.obj_file
   * https://www.andrewnoske.com/wiki/OBJ_file_format
   * https://www.cs.cmu.edu/~mbz/personal/graphics/obj.html
   */

  // Create an output file stream and open it
  std::ofstream ofs;                                 // ofs = output file stream
  ofs.open(filename, std::ios::trunc);                    // ios::out is default

  if (!ofs.is_open()) {
    // File didn't open properly
    perror("Error opening file");
    // exit(EXIT_FAILURE);
    return false;
  }

  // Write the vertices
  ofs << "# WaveFront .obj file.\n\n";
  ofs << "# List of vertices\n";
  for (int row = 0; row < V.rows(); row++) {
    // NOTE: indexing into Eigen vector or matrix uses parentheses: V(m, n) == V[m, n] == V[m][n]
    ofs << "v " << V(row, 0) << " " << V(row, 1) << " " << V(row, 2) << "\n";
  }

  // Write texture coordinates
  // NOTE: std::endl; also flushes the stream
  ofs << "\n# List of texture coordinates, in (u, v) coordinates, these will vary between 0 and 1" << std::endl;
  for (int r = 0; r < UV.rows(); r++) {
    ofs << "vt " << UV(r, 0) << " " << UV(r, 1) << "\n";
  }

  // Write vertex normals
  ofs << "\n# List of vertex normals in (x,y,z) form; normals might not be unit vectors" << std::endl;
  for (int r = 0; r < NV.rows(); r++) {
    ofs << "vn " << NV(r, 0) << " " << NV(r, 1) << " " << NV(r, 2) << "\n";
  }

  // Write our faces
  // f v1[/vt1][/vn1] v2[/vt2][/vn2] v3[/vt3][/vn3] ...
  ofs << "\n# List of faces and normals for each corner/vertex" << std::endl;
  for (int r = 0; r < F.rows(); r++) {
    ofs << "f ";

    // There could be any number of columns because we don't know if the face
    // is a triangle, quad, or general polygon
    for (int c = 0; c < F.cols(); c++) {
      // NOTE: Vertex numbers are continuous and start at 1
      // eg) f 1/5/3 2/8/4 3/6/1 4/3/8
      // UF[i, j] are indices into vt/UV and NF[i, j] are indices into vn/NV
      ofs << F(r, c) + 1 << "/" << UF(r, c) + 1 << "/" << NF(r, c) + 1 << " ";
    }
    ofs << "\n";
  }

  ofs.close();
  ////////////////////////////////////////////////////////////////////////////

  return true;
}
