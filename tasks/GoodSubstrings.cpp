#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class GoodSubstrings {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int k = in.readInt();
        int m = in.readInt();
        string s = in.readString();

        int qty = 0;
        int answer = 0;
        for (int i = 0; i < n; i++) {
            if (i >= k) {
                qty -= s[i - k] - '0';
            }
            qty += s[i] - '0';
            if (qty > m) {
                qty--;
                answer++;
                s[i] = '0';
            }
        }
        out.printLine(answer);
        out.printLine(s);
	}
};
