#ifndef MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COO_TRAITS
#define MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COO_TRAITS

#include <type_traits>
#include "mathpp/implementation/common/traits.h"

// forward declare
template<scalar T>
struct CooSparseVector;

template<scalar T>
struct CooSparseVectorView;

// coo_sparse_vector
template<typename>
struct is_coo_sparse_vector : std::false_type {};

template<typename U>
struct is_coo_sparse_vector<CooSparseVector<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_coo_sparse_vector_v = is_coo_sparse_vector<T>::value;

template<typename T>
concept coo_sparse_vector = is_coo_sparse_vector_v<T>;

// coo_sparse_vector_view
template<typename>
struct is_coo_sparse_vector_view : std::false_type {};

template<typename U>
struct is_coo_sparse_vector_view<CooSparseVectorView<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_coo_sparse_vector_view_v = is_coo_sparse_vector_view<T>::value;

template<typename T>
concept coo_sparse_vector_view = is_coo_sparse_vector_view_v<T>;

#endif // MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COO_TRAITS
