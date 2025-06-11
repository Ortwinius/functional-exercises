// file: example1_letters.cpp
// compile with: g++ -std=c++23 -Wall example1_letters.cpp

#include <iostream>
#include <optional>
#include <vector>
#include <functional>
#include <algorithm>
#include <concepts>

using namespace std;
using namespace std::placeholders;

// getting inverse matrix of 2x2 matrix
// so that A*A^(-1) = Einheitsmatrix
// first check if its invertable 
// if yes -> invert it 
// if no -> return nullopt

// using alias for nxn matrix
using Matrix = vector<vector<double>>;
struct Result {
    optional<Matrix> value;
    optional<string> error;

    Result bind(const function<Result(const Matrix&)>& transform) const {
        if (!value.has_value())
            return *this;
        return transform(*value);
    }

    static Result success(const Matrix& m) {
        return Result{ make_optional(m), nullopt };
    }

    static Result failure(const string& msg) {
        return Result{ nullopt, make_optional(msg) };
    }
};

Result unit(const Matrix& m) {
    return Result::success(m);
}

auto is_invertable = [](const Matrix& m) {
    if (m.size() != 2 || m[0].size() != 2 || m[1].size() != 2) {
        return Result::failure("Only 2x2 matrices are allowed");
    }

    double det = m[0][0] * m[1][1] - m[0][1] * m[1][0];
    if (det == 0) {
        return Result::failure("Matrix is not invertible (det = 0).");
    }

    return Result::success(m);
};

auto invert_matrix = [](const Matrix& m) {
    double a = m[0][0], b = m[0][1];
    double c = m[1][0], d = m[1][1];

    double det = a * d - b * c;
    double div = 1.0 / det;

    Matrix inv = {
        { d * div, -b * div },
        { -c * div, a * div }
    };

    return Result::success(inv);
};

auto print_matrix = [](const Matrix& m) {
    for (const auto& row : m) {
        for (const auto& val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }
};

int main() {
    // invertible:
    Matrix initMatrix{
        {1, 2},
        {3, 4}
    };

    // not invertible:
    // Matrix initMatrix{
    //     {2, 4},
    //     {1, 2}
    // };

    auto result = unit(initMatrix)
        .bind(is_invertable)
        .bind(invert_matrix);

    if (result.error.has_value()) {
        cout << result.error.value() << endl;
    } else {
        cout << "Inverted Matrix:\n";
        print_matrix(result.value.value());
    }

    return 0;
}