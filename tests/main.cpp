#include "gtest/gtest.h"
#include "mathpp/math.h"

int main(int argc, char** argv) {
    SparseMatrix<float> a(3, 3);
    a.set(0, 0, 1);
    a.set(1, 1, 5);
    a.set(2, 1, 6);
    a.set(2, 2, 9);
    std::cout << "RowIndices" << std::endl;
    std::cout << a.rowIndices()[0] << std::endl;
    std::cout << a.rowIndices()[1] << std::endl;
    std::cout << a.rowIndices()[2] << std::endl;
    std::cout << a.rowIndices()[3] << std::endl;
    std::cout << "Values" << std::endl;
    std::cout << a.values()[0] << std::endl;
    std::cout << a.values()[1] << std::endl;
    std::cout << a.values()[2] << std::endl;
    std::cout << a.values()[3] << std::endl;
    std::cout << "ColOffsets" << std::endl;
    std::cout << a.colOffsets()[0] << std::endl;
    std::cout << a.colOffsets()[1] << std::endl;
    std::cout << a.colOffsets()[2] << std::endl;
    std::cout << a.colOffsets()[3] << std::endl;
    SparseMatrix<float> b(3, 3, {{1, 0, 0}, {5, 1, 1}, {6, 2, 1}, {9, 2, 2}});
    std::cout << "RowIndices" << std::endl;
    std::cout << b.rowIndices()[0] << std::endl;
    std::cout << b.rowIndices()[1] << std::endl;
    std::cout << b.rowIndices()[2] << std::endl;
    std::cout << b.rowIndices()[3] << std::endl;
    std::cout << "Values" << std::endl;
    std::cout << b.values()[0] << std::endl;
    std::cout << b.values()[1] << std::endl;
    std::cout << b.values()[2] << std::endl;
    std::cout << b.values()[3] << std::endl;
    std::cout << "ColOffsets" << std::endl;
    std::cout << b.colOffsets()[0] << std::endl;
    std::cout << b.colOffsets()[1] << std::endl;
    std::cout << b.colOffsets()[2] << std::endl;
    std::cout << b.colOffsets()[3] << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}