#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// TODO: rename to Wuerfel
class Result {
private:
  int a = 0;
  int V = 0;
  int A = 0;
  float d = 0;
  float ru = 0;
  float ri = 0;

  const int calcVolume(const int &a) { return pow(a, 3); }

  const int calcArea(const int &a) { return 6 * pow(a, 2); }

  const float calcDiagonal(const int &a) { return a * sqrt(3); }

  const float calcRU(const int &a) { return (float)a / 2 * sqrt(3); }

  const float calcRI(const int &a) { return (float)a / 2; }

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
