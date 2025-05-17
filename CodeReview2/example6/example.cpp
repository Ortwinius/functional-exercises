#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>

using namespace std;

// Dodekaeder

// 1) Volumen:
auto calcVolume = [](const int &a) -> float {
    return pow(a, 3) * (15 + 7 * sqrt(5)) / 4.0;
};

// 2) Oberfläche:
auto calcArea = [](const int &a) -> float {
    return 3 * pow(a, 2) * sqrt(5 * (5 + 2 * sqrt(5)));
};

// 3) Inkreisradius:
auto calcRI = [](const int &a) -> float {
    return a * sqrt(10 * (25 + 11 * sqrt(5))) / 20.0;
};

// 4) Umkreisradius:
auto calcRU = [](const int &a) -> float {
    return a * sqrt(3) * (1 + sqrt(5)) / 4.0;
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
