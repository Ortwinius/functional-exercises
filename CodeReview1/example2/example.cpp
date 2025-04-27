#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

struct CubeProps
{
    int volume = 0;
    int area = 0;
    double diagonal = 0;
    double ru = 0;
    double ri = 0;
};

const CubeProps wuerfel (const int& a)
{
    CubeProps cube;
	cube.volume = pow(a,3);
	cube.area = 6*pow(a,2);
	cube.diagonal =a*sqrt(3);
	cube.ru = (double)a/2*sqrt(3);
	cube.ri = (double)a/2;
    return cube;
}

string formatResults(const CubeProps& result)
{
    stringstream output;
    output << "Volumen: " << result.volume << "\n";
    output << "Oberfläche: " << result.area << "\n";
    output << "Diagonale: " << result.diagonal << "\n";
    output << "Inkreisradius: " << result.ri << "\n";
    output << "Umkreisradius: " << result.ru << "\n";
    return output.str();
}
int
main (int argc, char *argv[])
{
  int a = 2;
  CubeProps result = wuerfel (a);
  cout << "Volumen:" << result.volume << " Oberfläche" 
        << result.area << " Diagonale:" << result.diagonal 
        << " Inkreisradius:" << result.ri << "Umkreisradius:" << result.ru << endl;
  /*cout << "Volumen:" << V << " Oberfläche:"<<A << " Diagonale:" << d << " Inkreisradius:" << ri << " Umkreisradius:" <<ru << endl;*/
  return 0;
}
