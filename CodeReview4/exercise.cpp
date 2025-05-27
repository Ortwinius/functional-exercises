#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>

using namespace std;

auto replaceCharInString = [](const string& str, char oldChar, char newChar) -> string {
    return accumulate(str.begin(), str.end(), string{}, [=](string res, char c) {
        res += (c == oldChar ? newChar : c);
        return res;
    });
};

template <typename T>
auto mergeSets = [](const set<T>& a, const set<T>& b) -> set<T> {
    set<T> result(a);
    result.insert(b.begin(), b.end());
    return result;
};

// adds elem of type T at beginning of vector while not altering the original vector
template<typename T>
auto frontInsertVector = [](const T& elem, const vector<T>& v) -> vector<T> {
    vector<T> res;
    res.reserve(v.size() + 1);
    res.push_back(elem);
    res.insert(res.end(), v.begin(), v.end());
    return res;
};

template<typename T>
auto flipVector = [](const vector<T>& in) -> vector<T> {
    vector<T> res(in.size());
    reverse_copy(in.begin(), in.end(), res.begin()); // copies reversed order of input vec into res  
    return res;
};

TEST_CASE("charSwapInString ersetzt Zeichen funktional") {
    string s = "banana boat";
    auto res = replaceCharInString(s, 'a', 'x');
    CHECK(res == "bxnxnx boxt");
    CHECK(s == "banana boat");
}

TEST_CASE("unionizeSets vereinigt zwei Sets funktional") {
    set<int> a = {10, 20, 30};
    set<int> b = {20, 40};
    auto res = mergeSets<int>(a, b);
    set<int> expected = {10, 20, 30, 40};
    CHECK(res == expected);
    CHECK(a == set<int>({10, 20, 30}));
    CHECK(b == set<int>({20, 40}));
}

TEST_CASE("mergeSets vereinigt zwei ComplexSets korrekt") {
    using IntSet = set<int>;
    using ComplexSet = set<IntSet>;

    ComplexSet a = { { {1, 2}, {3, 4} } };   
    ComplexSet b = { { {5, 6} } };           
    auto merged = mergeSets<IntSet>(a, b);
    ComplexSet expected = { {1, 2}, {3, 4}, {5, 6} };
    CHECK(merged == expected);
    CHECK(a == ComplexSet{ {1, 2}, {3, 4} });
    CHECK(b == ComplexSet{ {5, 6} });
}

TEST_CASE("frontInsertVector fügt Element vorne an funktional") {
    vector<string> fruits = {"apple", "banana"};
    string toInsert = "pear";
    auto result = frontInsertVector<string>(toInsert, fruits);
    vector<string> expected = {"pear", "apple", "banana"};
    CHECK(result == expected);
    CHECK(fruits == vector<string>({"apple", "banana"}));
}

TEST_CASE("flippedVector dreht einen Vektor um funktional") {
    vector<char> c = {'x', 'y', 'z'};
    auto flipped = flipVector<char>(c);
    vector<char> expected = {'z', 'y', 'x'};
    CHECK(flipped == expected);
    CHECK(c == vector<char>({'x', 'y', 'z'}));
}