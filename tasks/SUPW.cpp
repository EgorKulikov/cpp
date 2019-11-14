#include "../lib/io/input.h"
#include "../lib/io/output.h"

class SUPW {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        auto supw = in.readIntArray(n);
        vi answer(n + 1);
        for (int i = 1; i <= n; i++) {
            int res = MAX_INT;
            for (int j = i - 1; j >= i - 3 && j >= 0; j--) {
                minim(res, answer[j]);
            }
            answer[i] = res + supw[i - 1];
        }
        int res = MAX_INT;
        for (int i = n; i >= n - 2 && i >= 0; i--) {
            minim(res, answer[i]);
        }
        out.printLine(res);
	}
};
