#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;

using Line  = vector<char>;
using Board = vector<Line>;

// Hilfs-Lambdas für funktionale Tests auf Collections
const auto all_of_collection = [](auto const& coll, auto fn) {
    return all_of(coll.begin(), coll.end(), fn);
};

auto accumulateAll = [](const auto source, auto init, auto fn){
    return accumulate(source.begin(), source.end(), init, fn);
};

// 1) Board-Dimension prüfen: genau 6×7?
const auto correctDimension = [](auto const& board) {
    return board.size() == 6
        && all_of_collection(board, [](auto const& row){
               return row.size() == 7;
           });
};

// 2) Negation
const auto wrongDimension = [](auto const& board){
    return !correctDimension(board);
};

// 3) Nur erlaubte Tokens?
const auto validTokens = [](auto const& board){
    return all_of_collection(board, [](auto const& row){
        return all_of_collection(row, [](const char& c){
            return c == 'X' || c == 'O' || c == ' ';
        });
    });
};

// 4) Negation
const auto wrongTokens = [](auto const& board){
    return !validTokens(board);
};

// 5) Zähle, wie oft ein Token vorkommt
const auto countToken = [](auto const& board, char token) {
    return accumulateAll(board, 0, [token](int sum, const Line& row) {
        return sum + count(row.begin(), row.end(), token);
    });
};

// 6) Differenz der Token-Anzahl > 1 ?
const auto diffTokensGreaterThanOne = [](auto const& board){
    int xCount = countToken(board, 'X');
    int oCount = countToken(board, 'O');
    return abs(xCount - oCount) > 1;
};

/***************
 *   TESTS
 ***************/

TEST_CASE("The difference in the number of tokens for the two players >1") {
    Board b(6, Line(7, ' '));
    // Platziere 4×'X' vs. 2×'O' → Differenz = 2
    b[0][0]='X'; b[0][1]='X'; b[0][2]='X'; b[0][3]='X';
    b[1][0]='O'; b[1][1]='O';
    CHECK_EQ(true, diffTokensGreaterThanOne(b));
}

TEST_CASE("Check for correct tokens") {
    Board b(6, Line(7, ' '));
    // Nur X, O und Leerfeld
    b[2][3] = 'X';
    b[4][5] = 'O';
    CHECK_EQ(true, validTokens(b));
}

TEST_CASE("Check for wrong tokens") {
    Board b(6, Line(7, ' '));
    // 'Z' ist kein erlaubtes Token
    b[0][0] = 'X';
    b[0][1] = 'Z';
    CHECK_EQ(true, wrongTokens(b));
}

TEST_CASE("Board-dimension is wrong") {
    // Falsche Anzahl Reihen
    Board b(5, Line(7, ' '));
    CHECK_EQ(true, wrongDimension(b));
}

TEST_CASE("Board-dimension is correct") {
    // Genau 6×7
    Board b(6, Line(7, ' '));
    CHECK_EQ(true, correctDimension(b));
}
