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

TEST_CASE("charSwapInString ersetzt Zeichen") {
    string s = "Avada kedavra";
    auto res = replaceCharInString(s, 'a', 'i');
    CHECK(res == "Avidi kedivri");
    CHECK(s == "Avada kedavra");
}

TEST_CASE("mergeSets vereinigt zwei Sets") {
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

TEST_CASE("frontInsertVector fügt Element vorne an") {
    vector<string> fruits = {"apple", "banana"};
    string toInsert = "pear";
    auto result = frontInsertVector<string>(toInsert, fruits);
    vector<string> expected = {"pear", "apple", "banana"};
    CHECK(result == expected);
    CHECK(fruits == vector<string>({"apple", "banana"}));
}

TEST_CASE("frontInsertVector prepend vector to vector-of-vectors") {
    using Vec = vector<int>;
    vector<Vec> vv = { {1, 2}, {3, 4} };      
    Vec vfront = {9, 8, 7};                   

    auto result = frontInsertVector<Vec>(vfront, vv);
    vector<Vec> expected = { {9, 8, 7}, {1, 2}, {3, 4} };

    CHECK(result == expected);
    CHECK(vv == vector<Vec>({ {1, 2}, {3, 4} })); 
}

TEST_CASE("flippedVector dreht einen Vektor um") {
    vector<char> c = {'x', 'y', 'z'};
    auto flipped = flipVector<char>(c);
    vector<char> expected = {'z', 'y', 'x'};
    CHECK(flipped == expected);
    CHECK(c == vector<char>({'x', 'y', 'z'}));
}