#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ranges>
#include <numeric>
#include <optional>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
namespace views = std::views;

struct WeatherRecord {
    string date;
    string city;
    double temperatureC;
    double humidity;
    double windSpeed;
};

//TODO: extract ifstream as interface
// Einfache CSV-Parserfunktion
vector<WeatherRecord> readCsv(const string& path) {
    ifstream in(path);
    vector<WeatherRecord> data;
    string line;
    getline(in, line); // Header ignorieren

    while (getline(in, line)) {
        istringstream iss(line);
        string date, city, tempStr, humStr, windStr;

        getline(iss, date, ',');
        getline(iss, city, ',');
        getline(iss, tempStr, ',');
        getline(iss, humStr, ',');
        getline(iss, windStr, ',');

        data.push_back(WeatherRecord{
            date,
            city,
            stod(tempStr),
            stod(humStr),
            stod(windStr)
        });
    }
    return data;
}