#include <iostream>
#include <vector>
#include <cmath>
#include <optional>
#include <functional>

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

auto print_solution = [](const QuarticSolution& sol) {
    cout << "Lösungen:\n";
    for (double x : sol.roots) {
        cout << x << "\n";
    }
};

int main() {
    // x^4 - 16 = 0 -> should return 4 solutions: x = 2,2,-2,-2 
    const auto result = solve_quartic(1, 0, 0, 0, -16);  

    if (result.has_value()) {
        print_solution(*result);
    } else {
        cout << "Keine reelle Lösung oder kein gültiger quartischer Term.\n";
    }

    // x^4 + 16 = 0 -> x^4 = -16 -> x = 4th sqrt of (-16) => complex! should return nullopt! 
    // const auto result = solve_quartic(1, 0, 0, 0, 16);  

    // if (result.has_value()) {
    //     print_solution(*result);
    // } else {
    //     cout << "Keine reelle Lösung oder kein gültiger quartischer Term.\n";
    // }


    return 0;
}
