#include "../lib/general.h"
#include "../lib/range/range.h"
#include "../lib/io/output.h"
#include "../tasks/j.cpp"

int main() {
    j sol;
    for (ll n = 1; n <= 10000; n++) {
        auto res = sol.go(n);
        vec<ll> exp(1, 1);
        for (ll j = 2; j <= n; j++) {
            if (n / exp.back() != n / j / j) {
                exp.push_back(j * j);
            }
        }
        if (res != exp) {
            throw "Jopa";
        }
    }
}