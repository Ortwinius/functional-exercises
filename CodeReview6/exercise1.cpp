#include <iostream>
#include <fstream>
#include <optional>
#include <vector>
#include <string>
#include <functional>
#include <cctype>  
#include <algorithm>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


using namespace std;
/**
 * Program to count LETTERS file input file stream (file)
 * 
 * Exercise Description: 
 * "reads letters from a file and counts the WORDS accordingly. "
 * VS
 * "Lastly create a lambda function to count the LETTERS file the file"
 */
struct CharMaybe {
    optional<vector<char>> value;

    CharMaybe bind(const auto& transform) const {
        if (!value.has_value())
            return { nullopt };               
        return transform(*value); // *value = value.value()           
    }
};

// returns CharMaybe building block of std::optional type
CharMaybe unit(const vector<char>& letters) {
    return CharMaybe{ make_optional(letters) };
}

auto readAllValuesFromFile = [](const string& filename) -> CharMaybe {
    ifstream file(filename);
    if (!file) { // if file cannot be opened
        return { nullopt };
    }
    
    vector<char> allChars((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    return unit(allChars);
};

auto filterLettersFromFile = [](const vector<char>& chars) -> CharMaybe {
    vector<char> letters;
    letters.reserve(chars.size()); // reserves memory but doesnt change the size of the vector

    copy_if(chars.begin(), chars.end(), back_inserter(letters), [](char c){
        return isalpha(static_cast<unsigned char>(c)); 
    });

    return unit(letters);
};

const auto countLetters = [](const vector<char>& letters) -> size_t {
    return letters.size();
};

TEST_CASE("Reading a valid ASCII file returns content") {
    auto result = readAllValuesFromFile("ascii.txt");
    CHECK(result.value.has_value());
}

TEST_CASE("Filtering extracts only alphabetic letters") {
    vector<char> mixed = {'H', 'e', 'l', 'l', 'o', '1', '!', ' ', 'W', 'o', 'r', 'l', 'd'};
    auto filtered = filterLettersFromFile(mixed);
    REQUIRE(filtered.value.has_value());
    CHECK_EQ(filtered.value->size(), 10);  // "HelloWorld"
}

TEST_CASE("Letter count is correct") {
    vector<char> letters = {'a', 'b', 'c'};
    size_t count = countLetters(letters);
    CHECK_EQ(count, 3);
}

TEST_CASE("Failing to read non-existent file returns nullopt") {
    auto result = readAllValuesFromFile("nonexistent.txt");
    CHECK(!result.value.has_value());
}

TEST_CASE("Reading, filtering and counting ASCII values") {
    auto result = readAllValuesFromFile("ascii.txt")
        .bind(filterLettersFromFile);
    
    size_t count = countLetters(result.value.value());
    CHECK_EQ(count, 47);
}

// int main() {
//     const auto filteredLetters =
//         readAllValuesFromFile("ascii.txt")
//             .bind(filterLettersFromFile);

//     // check if result is nullopt
//     if (!filteredLetters.value.has_value()) {
//         cout << "Error: konnte Datei nicht lesen oder verarbeiten.\n";
//         return 0;
//     }

//     const size_t letterCount = countLetters(*filteredLetters.value);

//     cout << "Anzahl Buchstaben: " << letterCount << "\n";
//     return 0;
// }