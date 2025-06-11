#include <iostream>
#include <fstream>
#include <optional>
#include <vector>
#include <string>
#include <functional>
#include <cctype>  

using namespace std;

// returns Maybe building block of std::optional type
using MaybeChars = optional<vector<char>>;

const MaybeChars unit(const vector<char>& letters) {
    return make_optional(letters);
}

const auto readAllValuesFromFile = [](const string& filename) -> MaybeChars {
    ifstream in(filename);
    if (!in) { // if file cannot be opened
        return nullopt;
    }

    vector<char> allChars;
    char c;
    while (in.get(c)) {
        allChars.push_back(c);
    }
    return unit(allChars);
};

const auto filterLettersFromFile = [](const vector<char>& chars) -> MaybeChars {
    vector<char> letters;
    for (const char& c : chars) {
        if (isalpha(static_cast<unsigned char>(c))) {
            letters.push_back(c);
        }
    }
    return unit(letters);
};

const auto countLetters = [](const vector<char>& letters) -> size_t {
    return letters.size();
};

int main() {
    const auto filteredLetters =
        readAllValuesFromFile("ascii.txt")
            .and_then(filterLettersFromFile);

    // check if result is nullopt
    if (!filteredLetters.has_value()) {
        cout << "Error: konnte Datei nicht lesen oder verarbeiten.\n";
        return 0;
    }

    const size_t letterCount = countLetters(*filteredLetters);

    cout << "Anzahl Buchstaben: " << letterCount << "\n";
    return 0;
}
