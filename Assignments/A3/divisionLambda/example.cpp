#include <iostream>
#include <list>
#include <map>
#include <string>
#include <functional>
#include <numeric>

using namespace std;

int main() {
    auto value = 5;

    auto prodToValues = [&](auto divisor){
        return value / divisor;
    };

    cout << "prod to values: " << prodToValues(2) << endl;

    return 0;
}