#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>

using namespace std;

// Cube

// 1) Volumen: 
auto calcVolume = [](const int &a) -> int {
    return pow(a, 3);
};

// 2) Oberfläche:
auto calcArea = [](const int &a) -> int {
    return 6 * pow(a, 2);
};

// 4) Umkreisradius: 
auto calcRU = [](const int &a) -> float {
    return (a / 2.0f) * sqrt(3);
};

// 5) Inkreisradius: 
auto calcRI = [](const int &a) -> float {
    return a / 2.0f;
};

// 3) Raumdiagonale: 
// auto calcDiagonal = [](const int &a) -> float {
//     return a * sqrt(3);
// };

// 6) curried because of multiple input arguments
auto formatResults = [](const int &V) {
    return [=](const int &A) {
        return [=](const float &ri) {
            return [=](const float &ru) {
                stringstream ss;
                ss << "Volumen: "      << V  << "\n"
                   << "Oberfläche: "   << A  << "\n"
                   << "Inkreisradius: " << ri << "\n"
                   << "Umkreisradius: " << ru << "\n";
                return ss.str();
            };
        };
    };
};

// 7) printText (like in first review)
void printText(const string &text) {
    cout << text;
}

int main() {
    const int a = 2;

    const int V = calcVolume(a);
    const int A = calcArea(a);
    const float ri = calcRI(a);
    const float ru = calcRU(a);

    printText(formatResults(V)(A)(ri)(ru));

    return 0;
}
