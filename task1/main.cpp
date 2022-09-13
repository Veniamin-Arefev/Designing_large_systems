#include <iostream>
#include <array>


template<std::size_t N>
constexpr std::array<std::array<int, N - 1>, N - 1>
get_submatrix(const std::array<std::array<int, N>, N> &matrix, int row) {
    std::array<std::array<int, N - 1>, N - 1> submatrix{};
    for (int i = 0; i != N - 1; ++i) {
        for (int j = 0; j != N - 1; ++j) {
            (&std::get<0>(((&std::get<0>(submatrix))[i])))[j] = matrix[i + (i >= row ? 1 : 0)][j + 1];
        }
    }
    return submatrix;
}

template<std::size_t N>
constexpr int det(const std::array<std::array<int, N>, N> &matrix) {
    int my_det = 0;


    for (int i = 0; i < N; i++) {
        int cur_res = det(get_submatrix(matrix, i));


        my_det += cur_res * ((i % 2 == 0) ? matrix[i][0] : -matrix[i][0]);
    }


    return my_det;
}

template<>
constexpr int det(const std::array<std::array<int, 2>, 2> &matrix) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

template<>
constexpr int det(const std::array<std::array<int, 1>, 1> &matrix) {
    return matrix[0][0];
}


int main() {
    constexpr std::array<std::array<int, 3>, 3> A = {{
                                                             {0, 1, 2},
                                                             {1, 2, 3},
                                                             {2, 3, 7}
                                                     }};


    constexpr int res = det<>(A);


    std::cout << "Determinant is " << res << std::endl;
    return 0;
}
