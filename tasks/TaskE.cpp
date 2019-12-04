#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class TaskE {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        auto a = in.readIntArray(n);

        int pos = find(all(a), -1) - a.begin();
        fill(a.begin(), a.begin() + (pos + 1), 0);
        ll answer = 0;
        reverse(all(a));
        int rem = n;
        while (rem > 1) {
            pos = min_element(a.begin(), a.begin() + (n - rem + 1)) - a.begin();
            answer += a[pos];
            a[pos] = numeric_limits<int>::max();
            rem /= 2;
        }
        out.printLine(answer);
	}
};
