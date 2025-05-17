#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>

using namespace std;

// Ikosaeder

// 1) Volumen:
auto calcVolume = [](const int &a) -> float {
    return 5 * pow(a, 3) * (3 + sqrt(5)) / 12;
};

// 2) Oberfläche:
auto calcArea = [](const int &a) -> float {
    return 5 * pow(a, 2) * sqrt(3);
};

// 3) Umkreisradius:
auto calcRU = [](const int &a) -> float {
    return (a / 4.0f) * sqrt(2 * (5 + sqrt(5)));
};

// 4) Inkreisradius:
auto calcRI = [](const int &a) -> float {
    return a * sqrt(3) * (3 + sqrt(5)) / 12;
};

// 5) curried because of multiple input arguments
auto formatResults = [](const float &V) {
    return [=](const float &A) {
        return [=](const float &ri) {
            return [=](const float &ru) {
                stringstream ss;
                ss << "Volumen: "       << V  << "\n"
                   << "Oberfläche: "    << A  << "\n"
                   << "Inkreisradius: " << ri << "\n"
                   << "Umkreisradius: " << ru << "\n";
                return ss.str();
            };
        };
    };
};

// 6) printText (like in first review)
void printText(const string &text) {
    cout << text;
}

int main() {
    const int a = 2;

    const float V  = calcVolume(a);
    const float A  = calcArea(a);
    const float ri = calcRI(a);
    const float ru = calcRU(a);

    printText(formatResults(V)(A)(ri)(ru));

    return 0;
}
