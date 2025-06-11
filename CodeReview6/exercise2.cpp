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

// getting inverse matrix of 2x2 matrix
// so that A*A^(-1) = Einheitsmatrix
// first check if its invertable 
// if yes -> invert it 
// if no -> return nullopt

// using alias for nxn matrix  
using Matrix = vector<vector<double>>;

struct MatrixResult {
    optional<Matrix> value;
    optional<string> error;

    MatrixResult bind(const auto& transform) const {
        if (!value.has_value())
            return *this;
        return transform(*value);
    }

    static MatrixResult success(const Matrix& m) {
        return MatrixResult{ make_optional(m), nullopt };
    }

    static MatrixResult failure(const string& msg) {
        return MatrixResult{ nullopt, make_optional(msg) };
    }
};

MatrixResult unit(const Matrix& m) {
    return MatrixResult::success(m);
}

// checks if rows == 2 AND cols == 2 => which means its a 2x2 matrix
auto has_wrong_dimensions = [](const Matrix& m) {
    return m.size() != 2 || m[0].size() != 2;
};

auto invert_matrix = [](const Matrix& m) {
    if (has_wrong_dimensions(m)) {
        return MatrixResult::failure("Only 2x2 matrices are allowed");
    }

    double a = m[0][0], b = m[0][1];
    double c = m[1][0], d = m[1][1];

    double det = a * d - b * c;

    // for floating point instead of checking == 0 using 1*10^-10 = 0,0000000001 instead
    if(abs(det) < 1e-10){
        return MatrixResult::failure("Matrix is not invertible (det = 0).");
    }

    double div = 1.0 / det;

    Matrix inv = {
        { d * div, -b * div },
        { -c * div, a * div }
    };

    return MatrixResult::success(inv);
};

auto print_result = [](const Matrix& m) -> MatrixResult {
    for (const auto& row : m) {
        for (double val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    return unit(m); 
};

TEST_CASE("Matrix has invalid dimensions") {
    Matrix badMatrix = {
        {1, 2, 3},
        {4, 5, 6}
    };

    auto result = unit(badMatrix)
                    .bind(invert_matrix)
                    .bind(print_result);

    CHECK(result.value.has_value() == false);
    CHECK(result.error.has_value());
    CHECK_EQ(result.error.value(), "Only 2x2 matrices are allowed");
}

TEST_CASE("Matrix is 2x2 but not invertible (det = 0)") {
    Matrix singularMatrix = {
        {2, 4},
        {1, 2}
    };

    auto result = unit(singularMatrix)
                    .bind(invert_matrix)
                    .bind(print_result);
    
    CHECK_FALSE(result.value.has_value());
    CHECK(result.error.has_value());
    CHECK_EQ(result.error.value(), "Matrix is not invertible (det = 0).");
}

TEST_CASE("Matrix is invertible and bind works correctly") {
    Matrix invertibleMatrix = {
        {1, 2},
        {3, 4}
    };

    auto result = unit(invertibleMatrix)
                    .bind(invert_matrix)
                    .bind(print_result);

    REQUIRE(result.value.has_value());
    const Matrix& inv = result.value.value();

    // expected inverse:
    // [ -2.0  1.0 ]
    // [ 1.5  -0.5 ]
    CHECK_EQ(inv[0][0], doctest::Approx(-2.0));
    CHECK_EQ(inv[0][1], doctest::Approx(1.0));
    CHECK_EQ(inv[1][0], doctest::Approx(1.5));
    CHECK_EQ(inv[1][1], doctest::Approx(-0.5));
}




// int main() {

//     // Test 1: Should return inverted matrix
//     Matrix invertibleMatrix{
//         {1, 2},
//         {3, 4}
//     };

//     auto resultInvertible = unit(invertibleMatrix)
//         .bind(invert_matrix);

//     if (resultInvertible.error.has_value()) {
//         cout << resultInvertible.error.value() << endl;
//     } else {
//         cout << "Inverted Matrix:\n";
//         print_matrix(resultInvertible.value.value());
//     }

//     // Test 2 : Should return error
//     // Matrix notInvertibleMatrix{
//     //     {2, 4},
//     //     {1, 2}
//     // };

//     // auto resultNotInvertible = unit(notInvertibleMatrix)
//     //     .bind(invert_matrix);

//     // if (resultNotInvertible.error.has_value()) {
//     //     cout << resultNotInvertible.error.value() << endl;
//     // } else {
//     //     cout << "Inverted Matrix:\n";
//     //     print_matrix(resultNotInvertible.value.value());
//     // }

//     return 0;
// }