#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct CubeProps {
  int volume = 0;
  int area = 0;
  double diagonal = 0;
  double ru = 0;
  double ri = 0;
};

const CubeProps wuerfel(const int &a) {
  CubeProps cube;
  cube.volume = pow(a, 3);
  cube.area = 6 * pow(a, 2);
  cube.diagonal = a * sqrt(3);
  cube.ru = (double)a / 2 * sqrt(3);
  cube.ri = (double)a / 2;
  return cube;
}

const string formatResultsPure(const CubeProps &result) {
  stringstream output;
  output << "Volumen: " << result.volume << "\n";
  output << "Oberfläche: " << result.area << "\n";
  output << "Diagonale: " << result.diagonal << "\n";
  output << "Inkreisradius: " << result.ri << "\n";
  output << "Umkreisradius: " << result.ru << "\n";
  return output.str();
}

void printPure(const string &text) { cout << text; }

int main(int argc, char *argv[]) {
  int a = 2;
  CubeProps result = wuerfel(a);
  printPure(formatResultsPure(result));

  return 0;
}
