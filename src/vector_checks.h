#pragma once
#include "vector.h"

template<int N, scalar T>
bool Vector<N, T>::isOrthogonal(const std::vector<Vector<N, T>>& vectors) {
    for (int i = 0; i < vectors.size(); i++) {
        for (int j = i; j < vectors.size(); j++) {
            if (i == j)
                continue;

            if (!compare(vectors[i].dot(vectors[j]), 0)) {
                return false;
            }
        }
    }

    return true;
}

template<int N, scalar T>
bool Vector<N, T>::isOrthonormal(const std::vector<Vector<N, T>>& vectors) {
    for (int i = 0; i < vectors.size(); i++) {
        if (!compare(vectors[i].dot(vectors[i]), 1)) {
            return false;
        }

        for (int j = i; j < vectors.size(); j++) {
            if (i == j)
                continue;

            if (!compare(vectors[i].dot(vectors[j]), 0)) {
                return false;
            }
        }
    }

    return true;
}