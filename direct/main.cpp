#include "../tasks/CumulativePalindromeCount.cpp"

int main() {
    CumulativePalindromeCount solver;

    string s;
    for (int i = 0; i < 5; i++) {
        s += string(1 << i, 'a');
        s += string(1 << i, 'b');
    }
    modint current = 0;
    modint str = 0;
    for (int i : range(s.size())) {
        for (int j : range(i + 1)) {
            bool good = true;
            for (int k = j, l = i; k < l; k++, l--) {
                if (s[k] != s[l]) {
                    good = false;
                    break;
                }
            }
            if (good) {
                str += 1;
            }
        }
        current += str;
        if (solver.doSolve(i + 1) != current) {
            throw "WA";
        }
    }
}