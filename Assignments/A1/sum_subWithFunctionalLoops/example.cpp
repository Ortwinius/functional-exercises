#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int sum_subWithFunctionalLoops(const vector<int>& numbers) {
    return accumulate(numbers.begin(), numbers.end(), 0, [](int total, int num) {
        return num % 2 == 0 ? total + num : total - num;
    });
}

int main() {
    
    vector<int> numbers = {2, 4, 6, 8};
    cout << "Total (even added, odd subtracted): " << sum_subWithFunctionalLoops(numbers) << endl;

    return 0;
}