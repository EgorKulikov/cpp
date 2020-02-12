#include "../lib/general.h"
#include "../lib/collections/arr.h"
#include "../lib/io/output.h"
#include "../lib/numbers/modulo.h"
#include "../tasks/ExpectedChange.cpp"

int main() {
    ExpectedChange ec;
    for (int n : range(1, 20)) {
        for (int j : range(1 << n)) {
            modint expected = 0;
            string s;
            for (int i : range(n)) {
                if ((j >> i & 1) == 0) {
                    s += ')';
                } else {
                    s += '(';
                }
            }
            for (int i : range(n)) {
                int no = 0;
                int nc = 0;
                int cur = 0;
                for (int j : range(i, n)) {
                    if (s[j] == '(') {
                        no++;
                    } else {
                        nc++;
                    }
                    if (no < nc) {
                        no++;
                        nc--;
                        cur++;
                    }
                    expected += cur;
                }
            }
            expected *= 2;
            expected *= modint(n).inverse();
            expected *= modint(n + 1).inverse();
            modint actual = ec.solve(n, s);
            if (expected != actual) {
                cerr << s << endl;
            }
        }
    }
}