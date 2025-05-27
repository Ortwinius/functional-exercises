#include <iostream>
#include <optional>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;

auto replaceCharacterInString = [](const string& input, const char from, const char to) -> string {
    return accumulate(input.begin(), input.end(), string{}, [=](string result, char c){
        result += (c == from ? to : c);
        return result;
    });
};



TEST_CASE("Immutable String Replace") {
    string str = "Avada kedavra!";

    auto result = replaceCharacterInString(str, 'a', 'i');
    
    CHECK(result == "Avidi kedivri!");
    CHECK(str == "Avada kedavra!");
}