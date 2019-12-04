#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/collections/interval_tree.h"

//#pragma comment(linker, "/STACK:200000000")

class DMOPC19Contest3P3Majority {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        auto v = in.readIntArray(n);
        
        auto sum = [](int a, int b) -> int { return a + b;};
        auto accum = [](int a, int b, int, int) -> int { return a + b;};
        IntervalTree<int, int> tree(2 * n + 1, sum, sum, accum);
        int balance = 0;
        tree.update(n, n + 1, 1);
        ll answer = 0;
        for (int i : v) {
            if (i == 1) {
                balance++;
            } else {
                balance--;
            }
            answer += tree.query(0, n + balance);
            tree.update(n + balance, n + balance + 1, 1);
        }
        out.printLine(answer);
	}
};
