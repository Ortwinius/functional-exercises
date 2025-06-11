#include <iostream>
#include <fstream>
#include <optional>
#include <vector>
#include <string>
#include <functional>
#include <cctype>  

using namespace std;

struct CharMaybe {
    optional<vector<char>> value;

    CharMaybe bind(const function<CharMaybe(const vector<char>&)>& transform) const {
        if (!value.has_value())
            return { nullopt };               
        return transform(*value); // *value = value.value()           
    }
};

// returns CharMaybe building block of std::optional type
const CharMaybe unit(const vector<char>& letters) {
    return CharMaybe{ make_optional(letters) };
}

const auto readAllValuesFromFile = [](const string& filename) -> CharMaybe {
    ifstream in(filename);
    if (!in) { // if file cannot be opened
        return { nullopt };
    }
    
    vector<char> allChars;
    char c;
    while (in.get(c)) {
        allChars.push_back(c);
    }
    return unit(allChars);
};

const CharMaybe filterLettersFromFile(const vector<char>& chars) {
    vector<char> letters;
    for (const char& c : chars) {
        if (isalpha(c)) {
            letters.push_back(c);
        }
    }
    return unit(letters);
}

const auto countLetters = [](const vector<char>& letters) -> size_t {
    return letters.size();
};

int main() {
    const auto filteredLetters =
        readAllValuesFromFile("ascii.txt")
            .bind(filterLettersFromFile);

    // check if result is nullopt
    if (!filteredLetters.value.has_value()) {
        cout << "Error: konnte Datei nicht lesen oder verarbeiten.\n";
        return 0;
    }

    const size_t letterCount = countLetters(*filteredLetters.value);

    cout << "Anzahl Buchstaben: " << letterCount << "\n";
    return 0;
}
