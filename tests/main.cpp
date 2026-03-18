#include "gtest/gtest.h"
#include "mathpp/math.h"

int main(int argc, char** argv) {
    DenseVector<int> e = {1, 2, 3, 4, 5};
    DenseVector<int>& f = e;
    DenseVector<int>* g = &e;

    DenseVectorView<int> h(e, 3, 1);
    DenseVectorView<int>& hh = h;
    DenseVectorView<int>* hhh = &h;

    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    CustomDenseVector<float> i(data, 3, 3);
    CustomDenseVector<float>& ii = i;
    CustomDenseVector<float>* iii = &i;

    SparseVector<float> j(5, {{2, 1}, {4, 3}, {5, 4}});
    SparseVector<float>& k = j;
    SparseVector<float>* l = &j;

    SparseVectorView<float> m(j, 3, 1);
    SparseVectorView<float>& mm = m;
    SparseVectorView<float>* mmm = &m;

    float* values = new float[2];
    values[0] = 1;
    values[1] = 3;
    int* indices = new int[2];
    indices[0] = 0;
    indices[1] = 2;
    int nnz = 2;

    CustomSparseVector<float> n(3, values, indices, nnz);
    CustomSparseVector<float>& nn = n;
    CustomSparseVector<float>* nnn = &n;

    nnn->set(1, 5);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
