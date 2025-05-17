#include <cmath>
#include <iostream>
#include <sstream>
#include <functional>

using namespace std;

// Quader

// 1) Volumen: a, b, c => V = a * b * c
auto calcVolume = [](const int &a) {
    return [=](const int &b) {
        return [=](const int &c) -> int {
            return a * b * c;
        };
    };
};

// 2) Oberfläche: a, b, c => A = 2 * (a*b + a*c + b*c)©
auto calcArea = [](const int &a) {
    return [=](const int &b) {
        return [=](const int &c) -> int {
            return 2 * (a * b + a * c + b * c);
        };
    };
};

// 3) Raumdiagonale: a, b, c => d = sqrt(a^2 + b^2 + c^2)
auto calcDiagonal = [](const int &a) {
    return [=](const int &b) {
        return [=](const int &c) -> float {
            return sqrt(
                pow(a, 2) +
                pow(b, 2) + 
                pow(c, 2)
            );
        };
    };
};

// 4) Formatter: V, A, d => string
auto formatResults = [](const int &V) {
    return [=](const int &A) {
        return [=](const float &d) {
            stringstream ss;
            ss << "Volumen: "    << V << "\n"
               << "Oberfläche: " << A << "\n"
               << "Diagonale: "   << d << "\n";
            return ss.str();
        };
    };
};

// 5) remains unchanged
void printText(const string &text) {
    cout << text;
}

int main() {
    const int a = 2, b = 3, c = 4;

    // providing every parameter independently (currying)
    int V = calcVolume(a)(b)(c);
    int A = calcArea(a)(b)(c);
    float d = calcDiagonal(a)(b)(c);

    printText(formatResults(V)(A)(d));

    return 0;
}
