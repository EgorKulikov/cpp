#include "../tasks/EPermutationCover.cpp"
#include "../lib/recursive_function.h"

int main() {
    EPermutationCover e;
    for (int n : range(1, 10)) {
        err.printLine("n =", n);
        arri a(n);
        arri b(n);
        for (int mn : range(1, 10)) {
            err.printLine("mn =", mn);
            RecursiveFunction rec = [&](const auto& self, int st) -> void {
                if (st == n) {
                    copy(all(a), b.begin());
                    e.solve(n, b);
                    return;
                }
                for (int j : range(mn, 2 * mn + 1)) {
                    a[st] = j;
                    self(st + 1);
                }
            };
            rec(0);
        }
    }
}
