#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/range/rev_range.h"

//#pragma comment(linker, "/STACK:200000000")

class TaskB1 {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int p = in.readInt();
        int k = in.readInt();
        auto a = in.readIntArray(n);

        sort(all(a));
        arri cost(n + 1);
        cost[0] = 0;
        for (int i : range(k - 1)) {
            cost[i + 1] = cost[i] + a[i];
        }
        for (int i : range(k - 1, n)) {
            cost[i + 1] = min(cost[i + 1 - k], cost[i]) + a[i];
        }
        int answer;
        for (int i : RevRange(n + 1)) {
            if (cost[i] <= p) {
                answer = i;
                break;
            }
        }
        out.printLine(answer);
	}
};
