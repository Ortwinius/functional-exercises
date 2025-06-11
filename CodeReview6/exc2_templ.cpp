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
// TODO -> use template T of type numeric
template<typename T>
using Matrix = vector<vector<T>>;

template<typename T>
struct Result {
    optional<Matrix<T>> value;
    optional<string> error;

    Result bind(const auto& transform) const {
        if (!value.has_value())
            return *this; // an error already happened, not continuing operations              
        return transform(*value);            
    }

    static Result success(const Matrix<T>& m) {
        return Result{ make_optional(m), nullopt };
    }

    static Result failure(const string& msg){
        return Result{ nullopt, make_optional(msg) };
    }
};

template<typename T>
requires std::is_arithmetic_v<T>
Result<T> unit(const Matrix<T>& m) {
    return Result<T>{ make_optional(m), nullopt };
}

// -> dont like this bc 4 args but if i use Matrix as arg it relies on the fact
// that it would be 2x2, no bueno
// auto determinant = [](const int a, const int b, const int c, const int d){
//     return a*d-b*c;
// };

// determinant -> returns if matrix is invertable
template<typename T>
requires std::is_arithmetic_v<T>
auto is_invertable = [](const Matrix<T>& m) -> Result<T> {

    if(m.size() != 2 || m[0].size() != 2){
        return Result<T>::failure("Only 2x2 matrices are allowed");
    }

    // TODO -> put in separate pure function
    auto det = m[0][0]*m[1][1]-m[0][1]*m[1][0];

    if(det == 0)
        return Result<T>::failure("Matrix is not invertible (det = 0).");

    return Result<T>::success(m);

};

template <typename T>
requires std::is_arithmetic_v<T>
tuple<T, T, T, T> extract_vals_from_matrix(const Matrix<T>& m) {
    return { m[0][0], m[0][1], m[1][0], m[1][1] };
}

// tries to invert matrix, returns inverted make_optional<Matrix> or nullopt if error occurs
template<typename T>
requires std::is_arithmetic_v<T>
auto invert_matrix = [](const Matrix<T>& m) -> Result<T> {

    // 1/(ad-bc)*{{d,-b},{-c,a}}
    // = 1/determinante*
    auto [a,b,c,d] = extract_vals_from_matrix(m);
    // auto a = m[0][0], b = m[0][1], c = m[1][0], d = m[1][1];

    // TODO -> put in separate pure function
    auto det = a*d-b*c;
    
    auto div = 1 / det;

    Matrix<T> inv = {
        {d,-b},
        {-c,a}
    };

    for(auto& row : inv){
        for(auto& val : row){
            val *= div;
        }
    }

    return Result<T>::success(inv);
};

template<typename T>
auto print_matrix = [](const Matrix<T>& m){
    static_assert(std::is_arithmetic_v<T>, "Matrix<T>: T must be a numeric type.");

    for(const auto& row: m){
        for (const auto& val: row){
            cout << to_string(val) << " ";
        }
        cout << "\n";
    }
};


int main(){
    // invertible:
    Matrix<float> initMatrix{
        {1,2},
        {3,4}
    };

    // not invertible:
    // Matrix<float> initMatrix{
    //     {2,4},
    //     {1,2}
    // };

    auto result = unit(initMatrix)
        .bind(is_invertable<float>)
        .bind(invert_matrix<float>);
    
    if (result.error != nullopt) {
        cout << result.error.value() << endl;
    } else {
        cout << "Inverted Matrix:" << endl;
        for (const auto& row : result.value.value()) {
            for (const auto& elem : row) {
                cout << elem << " ";
            }
            cout << endl;
        }
    }

    return 0;
}