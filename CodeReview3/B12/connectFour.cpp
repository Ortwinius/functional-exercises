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
using namespace std::placeholders;

using Token = char;
using Line  = vector<char>;
using Board = vector<Line>;

// helper functions
const auto all_of_collection = [](auto const& coll, auto fn) {
    return all_of(coll.begin(), coll.end(), fn);
};

const auto accumulateAll = [](const auto source, auto init, auto fn) {
    return accumulate(source.begin(), source.end(), init, fn);
};

const auto diffGreaterThanOne = [](auto first, auto second) -> bool {
    return abs(first - second) > 1;
};

static mt19937 rng(random_device{}());

auto chunkTokens = [](vector<Token> const& tokens){
    // Zeilen-Indices 0…5
    auto rows = range(0,5);
    // Für jede Zeile erzeugen wir eine Line von 7 Token
    return transformAll<Board>(rows, [&](int r){
        // Spalten-Indices 0…6
        auto cols = range(0,6);
        // Diese Zeile r besteht aus tokens[r*7 + c]
        return transformAll<Line>(cols, [&](int c){
            return tokens[r*7 + c];
        });
    });
};

const auto validBoardDimensions = [](auto const& board) -> bool {
    return board.size() == 6
        && all_of_collection(board, [](auto const& row){
               return row.size() == 7;
           });
};

const auto singleTokenIsValid = [](const char& c) -> bool {
    return c == 'X' || c == 'O' || c == ' ';
};

const auto allTokensAreValid = [](auto const& board) -> bool {
    return all_of_collection(board, [](auto const& row){
        return all_of_collection(row, [](const char& c){
            return singleTokenIsValid(c);
        });
    });
};

const auto countToken = [](auto const& board, const char& token) -> int {
    return accumulateAll(board, 0, [token](int sum, const Line& row) {
        return sum + count(row.begin(), row.end(), token);
    });
};

auto countTokenX = bind(countToken, _1, 'X');
auto countTokenO = bind(countToken, _1, 'O');

// 6) Differenz der Token-Anzahl > 1 ?
const auto diffTokensGreaterThanOne = [](auto const& board) -> bool {
    return diffGreaterThanOne(countTokenX(board), countTokenO(board));
};

/***************
 *   TESTS
***************/

TEST_CASE("The difference of X and O tokens is greater than one") {
    Board b(6, Line(7, ' '));

    b[0][0]='X'; b[0][1]='X'; b[0][2]='X'; b[0][3]='X';
    b[1][0]='O'; b[1][1]='O';
    CHECK_EQ(true, diffTokensGreaterThanOne(b));
}


TEST_CASE("The difference of X and O tokens is greater than one") {
    Board b(6, Line(7, ' '));

    b[0][0]='X'; b[0][1]='X'; 
    b[1][0]='O'; b[1][1]='O';
    CHECK_EQ(false, diffTokensGreaterThanOne(b));
}

TEST_CASE("Tokens are valid") {
    Board b(6, Line(7, ' '));

    b[2][3] = 'X';
    b[4][5] = 'O';
    CHECK_EQ(true, allTokensAreValid(b));
}

TEST_CASE("Tokens are invalid") {
    Board b(6, Line(7, ' '));

    b[0][0] = 'X';
    b[0][1] = 'Z';
    CHECK_EQ(false, allTokensAreValid(b));
}

TEST_CASE("Board-dimension is wrong") {
    // rows should be 6, not 5
    Board b(5, Line(7, ' '));
    CHECK_EQ(false, validBoardDimensions(b));
}

TEST_CASE("Board-dimension is correct") {

    Board b(6, Line(7, ' '));
    CHECK_EQ(true, validBoardDimensions(b));
}
