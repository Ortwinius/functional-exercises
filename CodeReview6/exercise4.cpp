#include <iostream>
#include <optional>
#include <vector>
#include <functional>
#include <algorithm>
#include <concepts>

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

auto has_wrong_dimensions = [](const Matrix& m) {
    return m.size() != 2 || m[0].size() != 2;
};

auto invert_matrix = [](const Matrix& m) -> optional<Matrix> {
    if (has_wrong_dimensions(m)) {
        cout << "Matrix is not 2x2, cant invert";
        return nullopt;
    }

    double a = m[0][0], b = m[0][1];
    double c = m[1][0], d = m[1][1];

    double det = a * d - b * c;

    // for floating point instead of checking == 0 using 1*10^-10 = 0,0000000001 instead
    if(abs(det) < 1e-10){
        cout << "Determinant: 0, cant invert";
        return nullopt;
    }

    double div = 1.0 / det;

    Matrix inv = {
        { d * div, -b * div },
        { -c * div, a * div }
    };

    return make_optional(inv);
};
/*
Takes to params:
m => invertible matrix
b => to be multiplied with invertible
m^(-1) * b = Resultmatrix A 
 */
auto divide_matrix = [](const Matrix& m, const Matrix& b) -> MatrixResult{
    auto invertedM = invert_matrix(m);

    if(!invertedM.has_value()){
        // dont continue
    }


    for(int i = 0; i < )
    // else multiply invertedM with b 



};

auto print_result = [](const Matrix& m){

};

int main(){

    // invertable
    Matrix M{
        {1, 2},
        {3, 4}
    };

    // A = M^(-1) * B  
    auto A = unit(M)
        .bind(invert_matrix)
        .bind(divide_matrix);
    
    if(A.value.has_value()){
        print_result(A.value.value());
    } else {
        cout << "Error while trying to divide matrices\n";
    }


    return 0;
}