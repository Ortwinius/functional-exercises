// Example1: Functional version by Ortwin Baldauf
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

// Changes: Replaced global vars with local struct properties
struct CubeProps {
  int volume = 0;
  int area = 0;
  double diagonal = 0;
};

// pure function which takes three constant parameters
// and returns a new CubeProps without changing the original vals
const CubeProps quader(const int a, const int b, const int c) {
  CubeProps cube;
  cube.volume = a * b * c;
  cube.area = 2 * (a * b + a * c + b * c);
  cube.diagonal = sqrt(pow(a, 2) + pow(b, 2) + pow(c, 2));

  return cube;
}

const string formatResults(const CubeProps &cube) {
  stringstream output;
  output << "Volumen: " << cube.volume << "\n";
  output << "Oberfläche: " << cube.area << "\n";
  output << "Diagonale: " << cube.diagonal << "\n";
  return output.str();
}

void printText(const string &text) { cout << text; }

int main(int argc, char *argv[]) {
  int a = 2, b = 3, c = 4;

  CubeProps newCube = quader(a, b, c);

  printText(formatResults(newCube));

  return 0;
}
