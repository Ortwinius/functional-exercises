#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

class Dodekaeder {
private:
  int a;
  float V;
  float A;
  float ru;
  float ri;

  const float calcVolume(const int &a) {
    return pow(a, 3) * (15 + 7 * sqrt(5)) / 4.0;
  }

  const float calcArea(const int &a) {
    return 3 * pow(a, 2) * sqrt(5 * (5 + 2 * sqrt(5)));
  }

  const float calcRI(const int &a) {
    return a * sqrt(10 * (25 + 11 * sqrt(5))) / 20.0;
  }

  const float calcRU(const int &a) { return a * sqrt(3) * (1 + sqrt(5)) / 4.0; }

public:
  Dodekaeder(const int &a)
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
  Dodekaeder res(a);
  printText(res.formatResults());

  return 0;
}
