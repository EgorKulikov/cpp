#include "../tasks/GGCDExpress.cpp"

int main() {
    for (int i : range(1, 100000)) {
        int w = i;
        GGCDExpress g;
        int res = g.solve(1, i);
        int exp = 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                exp *= 2;
                do {
                    i /= j;
                } while (i % j == 0);
            }
        }
        if (i != 1) {
            exp *= 2;
        }
        if (res != exp) {
            throw "Jopa";
        }
    }
}
