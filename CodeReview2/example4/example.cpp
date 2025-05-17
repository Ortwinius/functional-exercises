#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>

using namespace std;

// Oktaeder

// 1) Volumen:
auto calcVolume = [](const int &a) {
    return pow(a, 3) * sqrt(2) / 3;
};

// 2) Oberfläche:
auto calcArea = [](const int &a) -> float {
    return 2 * pow(a, 2) * sqrt(3);
};

// 3) Umkreisradius:
auto calcRU = [](const int &a) {
    return a * sqrt(2) / 2;
};

// 4) Inkreisradius:
auto calcRI = [](const int &a) {
    return a * sqrt(6) / 6;
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
