# Math++ Linear Algebra Math Library

***

# Building the library
- Uses c++23 features.
- Build and install using CMake.
  - To only build library and not tests, specify '-DMATHPP_BUILD_TESTS=OFF'.
- #include "mathpp/math.h"

# What is included
- 4 main types: 
  - DenseMatrixBase
    - DenseMatrix
    - DenseMatrixView
    - CustomDenseMatrix
  - SparseMatrixBase
    - SparseMatrix
    - SparseMatrixView
    - CustomSparseMatrix
  - DenseVectorBase
      - DenseVector
      - DenseVectorView
      - CustomDenseVector
  - SparseVectorBase
      - SparseVector
      - SparseVectorView
      - CustomSparseVector
- Lots of algorithms and operator overloading
- Easy to work with syntax
  ``` c++
  #include <iostream>
  #include "mathpp/math.h"
  
  int main() {
      DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
      DenseMatrix<float> b = DenseMatrix<float>::random(-1, 1);
  
      DenseMatrix<float> c = a * transpose(b);
  
      c -= a;
  
      std::cout << to_string(inverse(c), 3) << std::endl;
  }
  ```
  
# Tests
- Heavy testing of all funcitons/algorithms/helpers
- See tests/readme.md

# Roadmap
1. Fully move old algorithms to new dense matrix and dense vector types
2. Implement all old algorithms but specialized sparse algorithms, if applicable.
3. Bindings to other languages (python, c#, java)
   - c if possible
4. Command line based program to use library, similar to Math Notepad https://mathnotepad.com/
5. Implement every decomposition on https://en.wikipedia.org/wiki/Matrix_decomposition
6. Implement every eigen algorithm on https://en.wikipedia.org/wiki/Eigenvalue_algorithm
7. Optimize everything

# Contributing
See src/readme.md

# Credits
- Me
- My dad

# References
- https://en.wikipedia.org/wiki/Matrix_decomposition
- https://en.wikipedia.org/wiki/Eigenvalue_algorithm
- https://scipp-legacy.pbsci.ucsc.edu/~haber/ph116A/RotationMatrices.pdf
- https://sites.math.duke.edu/~jdr/2021f-218/materials/week11.pdf
- https://aalexan3.math.ncsu.edu/articles/qr_notes.pdf
- https://www.math.utah.edu/~zwick/Classes/Fall2012_2270/Lectures/Lecture33.pdf
- https://www.math.purdue.edu/~eremenko/dvi/lect4.9.pdf
- https://sites.math.duke.edu/~jdr/2021f-218/materials/week11.pdf
- https://math.mit.edu/~gs/dela/dela_7-2.pdf
- https://www.foo.be/docs-free/Numerical_Recipe_In_C/c11-5.pdf
- https://arxiv.org/pdf/math/9904077
- https://www.math.drexel.edu/~tolya/301_spd_cholesky.pdf
- https://www.sciencedirect.com/science/article/pii/0024379576900719?via%3Dihub