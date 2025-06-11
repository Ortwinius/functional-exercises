#include <iostream>
#include <vector>
#include <cmath>
#include <optional>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;

/*
Quartic equation exercise -> solves biquadratic special case, 
returns nullopt if solution is complex, a = 0 or anyhting else
if not biquadratic -> fail bc general quartic equation scares me to death
*/ 

// holds all solutions of quartic equation (=4)
// minimal since assigment says use "simple struct"
// instead of holding optional<state>, solve_quartic etc wrap the QuarticSolution in an optional
// and_then is used instead of an own bind impl
struct QuarticSolution {
    vector<double> roots;
};

auto solve_quartic = [](
    const double &a, 
    const double &b, 
    const double &c, 
    const double &d, 
    const double &e
) -> optional<QuarticSolution> {

    // check if a ~ 0 => not quartic 
    const double epsilon = 1e-10;
    if (abs(a) < epsilon) return nullopt; // means -> not quartic

    // check if biquadratic -> ax^4 + e = 0 with b = c = d = 0
    if (b == 0 && c == 0 && d == 0) {
        // ax^4 + e = 0 => ax^4 = -e => x^4 = -e / a 
        double rhs = -e / a;
        if (rhs < 0.0) return nullopt; // imaginary result -> fail

        double root1 = sqrt(sqrt(rhs)); // BECAUSE : sqrt(sqrt(x^4)) = x
        double root2 = -root1; // because its +/- x

        return QuarticSolution{ { -root1, root2, root1, -root2  } };
    }

    // else fail 
    return nullopt;
};

// compatible with monad chaining since it returns optional type
auto print_solution = [](const QuarticSolution& sol) -> optional<QuarticSolution> {
    cout << "Lösungen:\n";
    for (double x : sol.roots) {
        cout << x << "\n";
    }
    return sol;
};

TEST_CASE("Biquadratic equation with 4 real roots") {
    auto result = solve_quartic(1, 0, 0, 0, -16).and_then(print_solution);
    REQUIRE(result.has_value());
    const auto& roots = result->roots;
    CHECK(roots.size() == 4);
    CHECK_EQ(abs(roots[0]), 2);
}

TEST_CASE("Biquadratic with complex roots returns nullopt") {
    auto result = solve_quartic(1, 0, 0, 0, 16);
    CHECK_FALSE(result.has_value());
}

TEST_CASE("Biquadratic with complex roots returns nullopt") {
    auto result = solve_quartic(2, 0, 0, 0, 16);
    CHECK_FALSE(result.has_value());
}

TEST_CASE("Non-quartic equation returns nullopt") {
    auto result = solve_quartic(0, 0, 0, 0, -16);
    CHECK_FALSE(result.has_value());
}