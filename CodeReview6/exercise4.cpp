#include <iostream>
#include <optional>
#include <vector>
#include <functional>
#include <algorithm>
#include <concepts>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

/*
left matrix division for 2x2 matrices
using a monad (=MatrixResult) for error management
solving M * A = B where M is invertible -> left divison => A = M^(-1) * B  

*/

// using alias for nxn matrix
using Matrix = vector<vector<double>>;

struct MatrixResult {
    optional<Matrix> value;

    MatrixResult bind(const auto& transform) const {
        if (!value.has_value())
            return *this;
        return transform(*value);
    }
};

MatrixResult unit(const Matrix& m) {
    return MatrixResult{ make_optional(m) };
}

// checking if rows = 2, fist row has 2 vals and second row has 2 as well!
// note that if row1.size() != row2.size() it cant be considered a matrix
auto has_wrong_dimensions = [](const Matrix& m) -> bool {
    return m.size() != 2 || m[0].size() != 2 || m[1].size() != 2;
};

auto invert_matrix = [](const Matrix& m) -> MatrixResult {
    if (has_wrong_dimensions(m)) {
        // cout << "Matrix is not 2x2, cant invert";
        return { nullopt };
    }

    double a = m[0][0], b = m[0][1];
    double c = m[1][0], d = m[1][1];

    double det = a * d - b * c;

    // for floating point instead of checking == 0 using 1*10^-10 = 0,0000000001 instead
    if(abs(det) < 1e-10){
        // cout << "Determinant: 0, cant invert";
        return {nullopt};
    }

    double div = 1.0 / det;

    Matrix inv = {
        { d * div, -b * div },
        { -c * div, a * div }
    };

    return unit(inv);
};
/*
Takes to params:
m => invertible matrix
b => to be multiplied with invertible
m^(-1) * b = Resultmatrix A 
 */
auto divide_matrix = [](const Matrix& m, const Matrix& b) -> MatrixResult{
    auto invertedRes = invert_matrix(m); 

    // if m cannot be inverted or b has wrong dimensions, dont continue
    if(!invertedRes.value.has_value() || has_wrong_dimensions(b)){
        return {nullopt};
    }   

    const Matrix& inv = *invertedRes.value;
    
    Matrix result(2, vector<double>(2, 0.0));

    // => for matter of simplicity i kept the for loop, could be replaced by a 3D transform 
    for (int i = 0; i < 2; ++i) {          // Rows of inv
        for (int j = 0; j < 2; ++j) {      // Columns of b
            for (int k = 0; k < 2; ++k) {  // Dot product
                result[i][j] += inv[i][k] * b[k][j];
            }
        }
    }

    return unit(result);
};

auto print_result = [](const Matrix& m) -> MatrixResult {
    for (const auto& row : m) {
        for (double val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    return unit(m); // oder einfach return {m}; aber unit(m) ist schöner
};


TEST_CASE("Matrix M has invalid dimensions") {
    Matrix M = {
        {1, 2, 3},
        {4, 5, 6}
    };

    Matrix B = {
        {5, 6},
        {7, 8}
    };

    auto result = divide_matrix(M,B)
                    .bind(print_result);

    CHECK(result.value.has_value() == false);
}

TEST_CASE("Matrix division fails when M is not invertible") {
    Matrix M = {
        {2, 4},
        {1, 2}
    };

    Matrix B = {
        {5, 6},
        {7, 8}
    };

    auto result = divide_matrix(M, B);
    CHECK_FALSE(result.value.has_value());
}

TEST_CASE("Matrix division returns valid result for invertible input") {
    Matrix M = {
        {1, 2},
        {3, 4}
    };

    Matrix B = {
        {5, 6},
        {7, 8}
    };

    auto result = divide_matrix(M, B).bind(print_result);
    REQUIRE(result.value.has_value());

    const Matrix& A = *result.value;

    // Expected result of A = M^-1 * B is:
    // [-3 -4]
    // [ 4  5]
    CHECK(A[0][0] == doctest::Approx(-3.0));
    CHECK(A[0][1] == doctest::Approx(-4.0));
    CHECK(A[1][0] == doctest::Approx(4.0));
    CHECK(A[1][1] == doctest::Approx(5.0));
}



// int main(){

//     // Test 1 : should return divided matrix A
//     cout << "Example 1 - should return divided matrix A\n";
//     Matrix M = {
//         {1, 2},
//         {3, 4}
//     };

//     Matrix B = {
//         {5, 6},
//         {7, 8}
//     };

//     // tries to divide and only prints result if dividing was successful
//     auto resultA = divide_matrix(M, B)
//         .bind(print_result);

//     // Test 2 : should return nothing since m is not invertible
//     cout << "Test 2 - should return nothing since m is not invertible\n";
//     Matrix M2 = {
//         {2, 4},
//         {1, 2}
//     };


//     Matrix B2 = {
//         {5, 6},
//         {7, 8}
//     };

//     divide_matrix(M2, B2)
//         .bind(print_result);
    
//     return 0;
// }