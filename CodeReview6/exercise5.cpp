#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <functional>
#include <iterator>
#include <numeric>

using namespace std;
using namespace std::placeholders;

// declaring Maybe alias
using MaybeStr = std::optional<std::string>;

// declaring unit function which takes string as input and returns optional<string>(input)
MaybeStr unit(const string& s) {
    return MaybeStr{ make_optional(s) };
}

auto readFile = [](const string& path) -> MaybeStr {
    // opens file with name "path"
    // ios::binary makes sure data is read without translating \n or \r etc.
    ifstream in(path, ios::binary);

    // return nullopt if it cannot be opened / found
    if (!in) return { nullopt };

    // parse content into input streambuf
    string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

    // packs string into MaybeStr format
    return unit(content);
};

/*
heuristic function which checks if more than half of input file is EBCDIC 8-bit (0-256)
-> this works because ASCII is only 7 bit (0-128) and mainly prints between 32 and 126
-> by checking if more than half of it is outside the range chances are very high its EBCDIC
*/
auto isFileEBCDIC = [](const string& content) -> MaybeStr {
    size_t nonAscii = accumulate(
        content.begin(),
        content.end(),
        0,
        [](size_t acc, char c) {
            unsigned char uc = static_cast<unsigned char>(c);
            return (uc < 32 || uc > 126) ? acc + 1 : acc;
        });

    if (nonAscii > content.size() / 2)
        return unit(content);
    return { nullopt };
};

// uses built-in and_then function 
// -> takes optional<T> type and performs 
// operation (isFileEBCDIC) on it if its not nullopt
auto processFileContent = [](const string& filename) -> MaybeStr {
    return readFile(filename)
        .and_then(isFileEBCDIC);
};

// can be used with any output
auto displayToSource = [](const string& data, ostream& stream){
    stream << data;
};

auto displayToConsole = std::bind(displayToSource, _1, std::ref(cout));

int main() {
    const string filename = "ebcdic.ebc";
    // const string filename = "ascii.txt";
    MaybeStr result = processFileContent(filename);

    if (result.has_value()) {
        cout << "\nDatei ist im EBCDIC-Format.\n\n";
        displayToConsole(*result);
    } else {
        cout << "\nDatei ist nicht EBCDIC oder konnte nicht gelesen werden.\n";
    }
    return 0;
}
