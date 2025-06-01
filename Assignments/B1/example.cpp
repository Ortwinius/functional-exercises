#include <iostream>
#include <functional>
#include <numeric>
#include <optional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

// split the class into pure functions

auto area = [](const auto width, const auto height) -> float
{
    return abs(width*height);
};
auto circumference = [](const auto width, const auto height) -> int 
{
    return abs(2*(width+height));
};
auto diagonal = [](const auto width, const auto height) -> float{
    return sqrt(pow(width,2)+pow(height,2));
};

auto initialize = [] (const auto width, const auto height) -> map<string, function<float()>>{
return {
	{"area", bind(area, width, height)},
	{"circumference", bind(circumference, width, height)},
	{"diagonal", bind(diagonal, width, height)}
	};
};

TEST_CASE ("Rectangle")
{
  auto rectangle = initialize(3, 4);
  CHECK_EQ(12, doctest::Approx(rectangle["area"]()));
  CHECK_EQ(14, doctest::Approx(rectangle["circumference"]()));
  CHECK_EQ(5, doctest::Approx(rectangle["diagonal"]()));
  
}