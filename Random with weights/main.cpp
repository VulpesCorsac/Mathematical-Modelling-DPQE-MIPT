#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <map>

using namespace std;

long long Random(const vector < long long > &x, const vector < long long > &p) {
    assert(x.size() == p.size() && "X and P have different sizes!");
    long long S = 0, s = 0, ans = 0;
    for (size_t i = 0; i < p.size(); i++)
        S += p[i];
    long long R = rand() % S;
    for (size_t i = 0; i < x.size(); i++) {
        if (s <= R)
            ans = x[i];
        s += p[i];
    }
    return ans;
}

int main() {
    srand(time(NULL));
    vector < long long > x, p;
    map < long long , long long > m;
    x.push_back(1);
    p.push_back(1);
    x.push_back(3);
    p.push_back(3);
    x.push_back(5);
    p.push_back(5);

//    for (int i = 0; i < x.size(); i++)
//        cout << x[i] << " - " << p[i] << endl;

    for (int i = 0; i < 10000; i++)
        m[Random(x, p)]++;

    for (int i = 0; i < x.size(); i++)
        cout << "X[" << i+1 << "] = " << x[i] << ", P[" << i+1 << "] = " << p[i] << ", M[" << x[i] << "] = " << m[x[i]] << endl;

    return 0;
}
