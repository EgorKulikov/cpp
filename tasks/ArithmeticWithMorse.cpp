#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

class ArithmeticWithMorse {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        auto s = in.readArray<string>(2 * n + 1);

        unordered_map<char, int> value = {
                {'.', 1},
                {':', 2},
                {'-', 5},
                {'=', 10}
        };
        
        vi val(n + 1);
        vector<char> op(n);
        for (int i : Range(n + 1)) {
            for (char c : s[2 * i]) {
                val[i] += value[c];
            }
        }
        for (int i : Range(n)) {
            op[i] = s[2 * i + 1][0];
        }
        int res = 0;
        int next = val[0];
        for (int i : Range(1, n + 1)) {
            if (op[i - 1] == '+') {
                res += next;
                next = val[i];
            } else {
                next *= val[i];
            }
        }
        res += next;
        out.printLine(res);
	}
};
