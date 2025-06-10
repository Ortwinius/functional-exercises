#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <algorithm>
#include <numeric>
#include <random>
#include <vector>
#include <functional>

using Token = char;
using Line  = std::vector<Token>;
using Board = std::vector<Line>;

using namespace std;
using namespace std::placeholders;

static auto range = [](int minV, int maxV){
    vector<int> r(maxV - minV + 1);
    iota(r.begin(), r.end(), minV);
    return r;
};

template<typename Dest>
static auto transformAll = [](auto const& src, auto fn){
    Dest out;
    out.resize(src.size());
    transform(src.begin(), src.end(), out.begin(), fn);
    return out;
};

static mt19937 rng(random_device{}());

// creates 6 rows via range
// then iterates over these rows via transform and for every r:
// creates a column (in total 7) and for every entry of the column
// return the index of the original vector and place it into 2D vector
static auto chunkTokens = [](vector<Token> const& tokens){
    auto rows = range(0,5);
    return transformAll<Board>(rows, [&](int r){
        auto cols = range(0,6);
        return transformAll<Line>(cols, [&](int c){
            return tokens[r*7 + c];
        });
    });
};

/*
SECTION: MY ORIGINAL FUNCTIONS
*/
static auto validBoardDimensions = [](auto const& board) -> bool {
    return board.size() == 6
        && all_of(board.begin(), board.end(), [](auto const& row){
               return row.size() == 7;
           });
};

static auto singleTokenIsValid = [](const Token& c) -> bool {
    return c == 'X' || c == 'O' || c == ' ';
};

static auto allTokensAreValid = [](auto const& board) -> bool {
    return all_of(board.begin(), board.end(), [&](auto const& row){
        return all_of(row.begin(), row.end(), [&](const Token& c){
            return singleTokenIsValid(c);
        });
    });
};

static auto accumulateAll = [](auto const& src, int init, auto fn){
    return accumulate(src.begin(), src.end(), init, fn);
};

static auto countToken = [](auto const& board, const Token& token) -> int {
    return accumulateAll(board, 0, [&](int sum, auto const& row) {
        return sum + (int)count(row.begin(), row.end(), token);
    });
};
static auto countTokenX = bind(countToken, _1, 'X');
static auto countTokenO = bind(countToken, _1, 'O');

static auto diffGreaterThanOne = [](int a, int b) -> bool {
    return abs(a - b) > 1;
};
static auto diffTokensGreaterThanOne = [](auto const& board) -> bool {
    return diffGreaterThanOne(countTokenX(board), countTokenO(board));
};







// creates entire board with correct values
static auto generateFilledCorrectBoard = []() {
    vector<Token> tokens;
    tokens.insert(tokens.end(), 21, 'X');
    tokens.insert(tokens.end(), 21, 'O');
    shuffle(tokens.begin(), tokens.end(), rng);
    return chunkTokens(tokens);
};

// fills entire board but one random char is wrong
static auto generateFilledErroneousBoard = []() {
    Board b = generateFilledCorrectBoard();

    uniform_int_distribution<int> rowDist(0, 5);
    uniform_int_distribution<int> colDist(0, 6);
    int rr = rowDist(rng);
    int cc = colDist(rng);

    b[rr][cc] = 'Z';

    return b;
};

// only fills part of board but correctly (with correct chars)
// how many elems are filled is chosen randomly 
static auto generatePartialCorrectBoard = []() {
    uniform_int_distribution<int> dist(0, 42);
    int n = dist(rng);

    int xCount = (n + 1) / 2;  
    int oCount = n / 2;

    vector<Token> tokens;
    tokens.insert(tokens.end(), xCount, 'X');
    tokens.insert(tokens.end(), oCount, 'O');
    tokens.insert(tokens.end(), 42 - n, ' ');

    shuffle(tokens.begin(), tokens.end(), rng);

    return chunkTokens(tokens);
};

static auto generatePartialErroneousBoard = []() {
    Board b = generatePartialCorrectBoard();

    uniform_int_distribution<int> rowDist(0, 5);
    uniform_int_distribution<int> colDist(0, 6);
    int rr = rowDist(rng);
    int cc = colDist(rng); 

    b[rr][cc] = 'Z';
    
    return b;
};

// Tests combining generators with validators

//prop_checkIfFilledCorreclty


#include "doctest.h"

TEST_CASE("Filled correct board: Dimension + Tokens + |X-O|") {
    auto b = generateFilledCorrectBoard();
    // 6×7?
    CHECK_EQ(true, validBoardDimensions(b));
    // nur X/O, keine ungültigen Zeichen?
    CHECK_EQ(true, allTokensAreValid(b));
    // Unterschied X/O darf NICHT > 1 sein (hier sogar 0)
    CHECK_EQ(false, diffTokensGreaterThanOne(b));
}

TEST_CASE("Filled erroneous board: mindestens ein ungültiges Token") {
    auto b = generateFilledErroneousBoard();
    // Dimensions-Check
    CHECK_EQ(true, validBoardDimensions(b));
    // Jetzt ist mindestens ein ungültiges Zeichen vorhanden -> false
    CHECK_EQ(false, allTokensAreValid(b));
    // Trotzdem sollten X und O immer komplett gefüllt sein, sodass |X-O| == 21-20 = 1
    CHECK_LE(abs(countTokenX(b) - countTokenO(b)), 1);
}

TEST_CASE("Partial correct board: Dimension + Tokens + |X-O| ≤ 1") {
    auto b = generatePartialCorrectBoard();
    CHECK_EQ(true, validBoardDimensions(b));
    CHECK_EQ(true, allTokensAreValid(b));
    CHECK_EQ(false, diffTokensGreaterThanOne(b));
}

TEST_CASE("Partial erroneous board: Dimension + zumindest ein ungültiges Token") {
    auto b = generatePartialErroneousBoard();
    CHECK_EQ(true, validBoardDimensions(b));
    CHECK_EQ(false, allTokensAreValid(b)); 
}