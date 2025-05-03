#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

// TODO rename ikosaeder
class Result {
private:
  int a = 0;
  float V = 0;
  float A = 0;
  float ru = 0;
  float ri = 0;

  const float calcVolume(const int &a) {
    return 5 * pow(a, 3) * (3 + sqrt(5)) / 12;
  }

  const float calcArea(const int &a) { return 5 * pow(a, 2) * sqrt(3); }

  const float calcRU(const int &a) { return a / 4.0 * sqrt(2 * (5 + sqrt(5))); }

  const float calcRI(const int &a) { return a * sqrt(3) * (3 + sqrt(5)) / 12; }

public:
  Result(const int &a)
      : a(a), V(calcVolume(a)), A(calcArea(a)), ri(calcRI(a)), ru(calcRU(a)) {}

  // const at the end to specify that it doesnt alter any member variables
  const string formatResults() const {
    stringstream output;

    output << "Volumen: " << V << "\n";
    output << "Oberfläche: " << A << "\n";
    output << "Inkreisradius: " << ri << "\n";
    output << "Umkreisradius: " << ru << "\n";

    return output.str();
  }
};

void printText(const string &text) { cout << text; }

int main(int argc, char *argv[]) {

  const int a = 2;
  Result res(a);
  printText(res.formatResults());

  return 0;
}
