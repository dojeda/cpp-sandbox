#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>
#include <iostream>
#include <random>

using namespace std;

void simple_test() {
    vector<int> v = {10,20,30,40,50,60,70,80,90,100};
    
    auto res = lower_bound(v.begin(), v.end(), 45);
    if (res != v.end()) {
        cout << "The first element >= 45 is " << *res << endl;
    }
    
    res = lower_bound(v.begin(), v.end(), 120);
    if (res == v.end())
        cout << "An element over 120 was not found" << endl;
}

vector<pair<double,double>> generate_data() {
    vector<pair<double,double>> data;
    double t = 0;
    const double freq = 1;
    const double dt = 1e-3;
    mt19937 rgen(0); // random number generator
    uniform_real_distribution<> runif(0,0.01);
    for (size_t i = 0; i < 100000; ++i) {
        const double rnoise = runif(rgen);
        data.emplace_back(make_pair(t, sin(2*M_PI*freq*t)));
        t += dt + rnoise;
    }
    return data;
}


int main(int argc, char *argv[]) {

    //simple_test();
    auto data = generate_data();
    for (size_t i = 0; i < 10; ++i) {
        cout << data[i].first << '\t' << data[i].second << endl;
    }
    
    const double epsilon = 1e-4;
    auto res = lower_bound(data.begin(), data.end(),
                           make_pair(10.0, numeric_limits<double>::min()),
    // option 1: no custom comparator, uses pair<T,U>::operator<
    // option 2: custom comparator with lambda expression
                           //[](auto a, auto b) {return (a.first <= b.first);} );
    // option 3: custom comparator with epsilon, that needs to pass by value
                           [=](auto a, auto b) {return b.first - a.first >= epsilon;} );
    if (res != data.end())
        cout << "First entry greater or equal than time=10 was found at index "
             << res-data.begin() << " with value (" << res->first << ", " << res->second << ")" << endl;
    
    return 0;
}
