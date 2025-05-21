#include <iostream>
#include <functional>
#include <numeric>
#include <optional>
#include <algorithm>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

using Line = vector<char>;
using Board = vector<Line>;


// basic Wrapper functions

auto accumulateAll = [](const auto source, auto fn){
    return accumulate(source.begin(), source.end(), typename decltype(source)::value_type(), fn);
};

auto all_of_collection = [](const auto& collection, auto fn){
    return all_of(collection.begin(), collection.end(), fn);
};

auto concatenate = [](const auto& first, const auto& second){
    auto result{first};
    result.insert(result.end(), make_move_iterator(second.begin()), make_move_iterator(second.end()));
    return result;
};

auto validBoardDimension = [](const auto& board){
    return all_of_collection(board, [](const auto& line){ return line.size() == 7; }) && board.size() == 6;
};

auto getAllTokens = [](const auto& board){
    return accumulateAll(board, [](auto current, auto line){ return concatenate(current, line); });
};

auto countCharInTokens = [](const auto& tokens, const auto& tokenToCount){
    return count_if(tokens.begin(), tokens.end(), [tokenToCount](const auto& token){ return token == tokenToCount; });
};

auto countXInTokens = bind(countCharInTokens, _1, 'X');
auto countOInTokens = bind(countCharInTokens, _1, 'O');
auto countEmptyInTokens = bind(countCharInTokens, _1, ' ');

auto validNumberOfTokens = [](const auto& board){
    return abs(countXInTokens(getAllTokens(board)) - countOInTokens(getAllTokens(board))) <= 1;
};

auto noInvalidTokens = [](const auto& board){
    const auto tokens = getAllTokens(board);
    auto validTokens = countXInTokens(tokens) + countOInTokens(tokens) + countEmptyInTokens(tokens);
    return static_cast<size_t>(validTokens) == tokens.size();
};

TEST_CASE("Valid connect 4 board dimensions"){
    Board board{
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    CHECK(validBoardDimension(board));
}

TEST_CASE("invalid connect 4 board dimensions - 8 columns"){
    Board board{
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    CHECK(!validBoardDimension(board));
}

TEST_CASE("invalid connect 4 board dimensions -  7 rows"){
    Board board{
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    CHECK(!validBoardDimension(board));
}

TEST_CASE("difference number of tokens = 1"){
    Board board{
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'X', 'X', 'X', 'X', 'O', 'O', 'O'}
    };

    CHECK(validNumberOfTokens(board));
}

TEST_CASE("difference number of tokens = 2"){
    Board board{
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', 'X', ' ', ' ', ' ', ' ', ' '},
        {'X', 'X', 'X', 'X', 'O', 'O', 'O'}
    };

    CHECK(!validNumberOfTokens(board));
}

TEST_CASE("no invalid tokens"){
    Board board{
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', 'X', ' ', ' ', ' ', ' ', ' '},
        {'X', 'X', 'X', 'X', 'O', 'O', 'O'}
    };

    CHECK(noInvalidTokens(board));
}

TEST_CASE("invalid token Y"){
    Board board{
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', 'Y', ' ', ' ', ' ', ' ', ' '},
        {' ', 'X', ' ', ' ', ' ', ' ', ' '},
        {'X', 'X', 'X', 'X', 'O', 'O', 'O'}
    };

    CHECK(!noInvalidTokens(board));
}

TEST_CASE("invalid token R"){
    Board board{
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'R', ' ', ' ', ' '},
        {' ', 'X', ' ', ' ', ' ', ' ', ' '},
        {'X', 'X', 'X', 'X', 'O', 'O', 'O'}
    };

    CHECK(!noInvalidTokens(board));
}