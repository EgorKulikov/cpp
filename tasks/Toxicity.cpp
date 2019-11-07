#include "../lib/io/input.h"
#include "../lib/io/output.h"

class Toxicity {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        auto a = in.readArray<ll>(n);

        int data[] = {2, 3, 5, 7, 13, 17, 19, 31};
        set<int> mersen(data, data + 8);

        int answer = 0;
        for (unsigned long long x : a) {
            if ((x & (x - 1)) != 0) {
                continue;
            }
            int exponent = __builtin_popcount(x - 1);
            answer += mersen.count(exponent);
        }
        out.printLine(answer);
	}
};
