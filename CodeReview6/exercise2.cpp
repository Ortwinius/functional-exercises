// file: example1_letters.cpp
// compile with: g++ -std=c++23 -Wall example1_letters.cpp

#include <iostream>
#include <fstream>
#include <optional>
#include <vector>
#include <string>
#include <functional>
#include <cctype>  // isalpha

using namespace std;

// getting inverse matrix
// so that A*A^(-1) = Einheitsmatrix
// first check if its invertable (3x3 always is, not allowed)
// if yes -> invert it 
// if no -> return nullopt
struct CharMaybe {
    optional<vector<char>> value;

    CharMaybe bind(const function<CharMaybe(const vector<char>&)>& transform) const {
        if (!value.has_value())
            return { nullopt };               
        return transform(*value);            
    }
};

CharMaybe unit(const vector<char>& letters) {
    return CharMaybe{ make_optional(letters) };
}
