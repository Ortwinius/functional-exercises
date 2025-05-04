// Example1: Functional version by Ortwin Baldauf
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

class Result {
private:
  int a = 0;
  int b = 0;
  int c = 0;
  int V = 0;
  int A = 0;
  float d = 0;

  const int calcVolume(const int &a, const int &b, const int &c) {
    return a * b * c;
  }

  const int calcArea(const int &a, const int &b, const int &c) {
    return 2 * (a * b + a * c + b * c);
  }

  const float calcDiagonal(const int &a, const int &b, const int &c) {
    return (float)sqrt(pow(a, 2) + pow(b, 2) + pow(c, 2));
  }

public:
  Result(const int &a, const int &b, const int &c)
      : a(a), b(b), c(c), V(calcVolume(a, b, c)), A(calcArea(a, b, c)),
        d(calcDiagonal(a, b, c)) {}

  // const at the end to specify that it doesnt alter any member variables
  const string formatResults() const {
    stringstream output;

    output << "Volumen: " << V << "\n";
    output << "Oberfläche: " << A << "\n";
    output << "Diagonale: " << d << "\n";
    return output.str();
  }
};

void printText(const string &text) { cout << text; }

int main(int argc, char *argv[]) {
  const int a = 2, b = 3, c = 4;
  Result res(a, b, c);
  printText(res.formatResults());

  return 0;
}
