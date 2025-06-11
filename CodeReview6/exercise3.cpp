#include <iostream>
#include <vector>
#include <cmath>
#include <optional>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;

/*
Quartic equation exercise -> solves biquadratic special case, returns nullopt if solution is complex, a = 0 or anyhting else
if not biquadratic -> fail bc general quartic equation scares me to death
*/ 

// holds all solutions of quartic equation (=4)
struct QuarticSolution {
    vector<double> roots;
};

auto solve_quartic = [](const double a, const double b, const double c, const double d, const double e) -> optional<QuarticSolution> {
    const double epsilon = 1e-10;
    if (abs(a) < epsilon) return nullopt; // means -> not quartic

    // check if biquadratic, if not fail
    if (b == 0 && c == 0 && d == 0) {
        double rhs = -e / a;
        if (rhs < 0.0) return nullopt; // imaginary result -> fail

        double root1 = sqrt(sqrt(rhs)); // BECAUSE : sqrt(sqrt(x^4)) = x
        double root2 = -root1; // because its +/- x

        // basically redundant because -root1 = root2 and root1 = -root2
        // but exercise is about getting ALL solutions (dont have to be unique?)
        return QuarticSolution{ { -root1, root2, root1, -root2  } };
    }

    return nullopt;
};

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

TEST_CASE("Non-quartic equation returns nullopt") {
    auto result = solve_quartic(0, 0, 0, 0, -16);
    CHECK_FALSE(result.has_value());
}