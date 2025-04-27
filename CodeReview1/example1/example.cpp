// Example1: Functional version by Ortwin Baldauf
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

// Changes: Replaced global vars with local struct properties
struct CubeProps
{
    int volume = 0;
    int area = 0;
    double diagonal = 0;
};

// pure function which takes three constant parameters
// and returns a new CubeProps without changing the original vals
const CubeProps quader (const int a, const int b, const int c)
{
    CubeProps cube;
    cube.volume = a*b*c;
    cube.area = 2*(a*b+a*c+b*c);
    // potentially replace pow with a*a, b*b, c*c?
	cube.diagonal = sqrt(pow(a,2)+pow(b,2)+pow(c,2));

    return cube;
}

string formatResultsPure(const int* pValue)
{
    stringstream output;
    output << "Adress: " << pValue << endl;
    output << "Increment pointer adress and value pure: " << (pValue + 1) << " value: " << *pValue << endl;

    return output.str();
}

void printSomething(const string& text)
{
    cout << text;
}

int
main (int argc, char *argv[])
{
    int a = 2, b = 3, c = 4;

    // initialize new cube and calculate properties via quader
    CubeProps newCube = quader (a,b,c);
    
    // TODO this part is not pure because it relies on external I/O functions
    /*cout << "Volumen:" << newCube.volume << " Oberfläche:"<< newCube.area << " Diagonale:" << newCube.diagonal << endl;*/

    int* pValue = new int(10);
    printSomething(formatResultsPure(pValue));
    delete pValue;
    
    return 0;
}
