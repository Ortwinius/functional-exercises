#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <iterator>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

struct WeatherRecord {
    const string date;
    const string city;
    const double temperature;
    const double humidity;
    const double windSpeed;
};

using Weathers = optional<vector<WeatherRecord>>;

Weathers unit(const vector<WeatherRecord>& ws) {
    return make_optional(ws);
}

auto temperatureAbove20DegreesC = [](const WeatherRecord& w){
    return w.temperature > 20;
};

// auto readFromCsvFile = [](const string& path) -> Weathers{
//     ifstream in(path, ios::binary);

//     // return nullopt if it cannot be opened / found
//     if (!in) return { nullopt };

//     // parse content into input streambuf
//     string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

//     //TODO: parse words into WeatherRecords 

//     // return unit(allRecords);
//     return { nullopt };
// };

auto filterByFormula = [](const Weathers& ws, const auto& formula){
    auto filtered = ws | ranges::views::filter(formula);
    return filtered;
};

TEST_CASE(""){
    // one point
    vector<WeatherRecord> records = {
        {"2020-05-20", "Vienna", 20, 3, 200},
        {"2021-05-20", "Luxembourgh", 21, 3, 200}
    };
    // auto res = records | ranges::views::filter(temperatureAbove20DegreesC);
    auto res = unit(records).and_then(filterByFormula(records,temperatureAbove20DegreesC));
    CHECK(!res.empty());

}


