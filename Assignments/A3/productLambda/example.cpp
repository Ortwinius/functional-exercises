#include <iostream>
#include <list>
#include <map>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

using namespace std;

int main() {
    const int first = 5, second = 10;

    auto prodToValues = [=](const int &multiplier){
        return (first * second) * multiplier;
    };

    cout << "prod to values" << prodToValues(2) << endl;

    return 0;
}